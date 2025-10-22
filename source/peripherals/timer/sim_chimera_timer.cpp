/********************************************************************************
 *  File Name:
 *    sim_chimera.cpp
 *
 *  Description:
 *    Simulator variant of the core chimera functionality.
 *
 *  2019-2025 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Aurora/logging>

/*-----------------------------------------------------------------------------
Test stubs (only for unit tests)
-----------------------------------------------------------------------------*/
#ifdef CPPUTEST_MEM_LEAK_DETECTION_DISABLED
#include "../../test/test_stubs.hpp"
#endif
#include <Chimera/common>
#include <Chimera/system>
#include <Chimera/timer>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <limits>
#include <mutex>
#include <thread>

namespace Chimera::Timer::Sim
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static std::chrono::steady_clock::time_point s_start_time;
  static std::atomic<bool> s_use_external_time{ false };
  static std::atomic<int64_t> s_external_time_baseline_us{
    0
  }; /**< Internal baseline time captured when external time enabled (microseconds) */
  static std::atomic<size_t> s_last_external_offset_us{ 0 }; /**< Last accepted external time offset (microseconds) */
  static std::mutex s_time_mutex;
  static std::condition_variable s_time_cv;

  namespace
  {
    constexpr size_t SIZE_MAX_VALUE       = std::numeric_limits<size_t>::max();
    constexpr int64_t CHRONO_MICROS_MAX   = std::chrono::microseconds::max().count();
    constexpr size_t CHRONO_MICROS_MAX_SZ = static_cast<size_t>( CHRONO_MICROS_MAX < 0 ? 0 : CHRONO_MICROS_MAX );

    size_t saturatingAdd( const size_t base, const size_t increment )
    {
      if( SIZE_MAX_VALUE - base < increment )
      {
        return SIZE_MAX_VALUE;
      }

      return base + increment;
    }


    size_t saturatingMultiply( const size_t value, const size_t multiplier )
    {
      if( ( value == 0U ) || ( multiplier == 0U ) )
      {
        return 0U;
      }

      if( value > ( SIZE_MAX_VALUE / multiplier ) )
      {
        return SIZE_MAX_VALUE;
      }

      return value * multiplier;
    }


    std::chrono::microseconds clampToChronoMicros( const size_t value )
    {
      const size_t clamped = value > CHRONO_MICROS_MAX_SZ ? CHRONO_MICROS_MAX_SZ : value;
      const int64_t casted = static_cast<int64_t>( clamped );
      return std::chrono::microseconds( casted );
    }


    size_t currentExternalMicros()
    {
      // Return baseline + last external offset to maintain monotonic time
      const int64_t baseline = s_external_time_baseline_us.load( std::memory_order_seq_cst );
      const size_t offset    = s_last_external_offset_us.load( std::memory_order_seq_cst );
      return static_cast<size_t>( baseline + static_cast<int64_t>( offset ) );
    }
  }    // namespace

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/

  Chimera::Status_t initialize()
  {
    s_start_time = std::chrono::steady_clock::now();
    s_use_external_time.store( false, std::memory_order_release );
    s_external_time_baseline_us.store( 0, std::memory_order_release );
    s_last_external_offset_us.store( 0, std::memory_order_release );
    s_time_cv.notify_all();
    return Chimera::Status::OK;
  }


  Chimera::Status_t reset()
  {
    return initialize();
  }


  size_t micros()
  {
    const auto now = std::chrono::steady_clock::now();

    if( s_use_external_time.load( std::memory_order_seq_cst ) )
    {
      return currentExternalMicros();
    }
    else
    {
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>( now - s_start_time );
      return static_cast<size_t>( duration.count() );
    }
  }


  size_t millis()
  {
    return micros() / 1000U;
  }


  void delayMicroseconds( const size_t val )
  {
    if( val == 0U )
    {
      return;
    }

    if( s_use_external_time.load( std::memory_order_acquire ) )
    {
      const size_t start = currentExternalMicros();
      const size_t goal  = saturatingAdd( start, val );

      std::unique_lock<std::mutex> lock( s_time_mutex );
      while( s_use_external_time.load( std::memory_order_acquire ) )
      {
        const size_t now = currentExternalMicros();
        if( now >= goal )
        {
          break;
        }

        const size_t remaining = goal - now;
        s_time_cv.wait_for( lock, clampToChronoMicros( remaining ) );
      }
    }
    else
    {
      const auto sleep_duration = clampToChronoMicros( val );
      std::this_thread::sleep_for( sleep_duration );
    }
  }


  void delayMilliseconds( const size_t val )
  {
    const size_t micros_val = saturatingMultiply( val, 1000U );
    delayMicroseconds( micros_val );
  }


  void enableExternalTimeSource( size_t sim_time_us )
  {
    std::scoped_lock lock( s_time_mutex );

    // Get current internal time before switching - this becomes our baseline
    const size_t current_internal_time = micros();

    // Store the baseline (internal time at enable) and initial external offset
    s_external_time_baseline_us.store( static_cast<int64_t>( current_internal_time ), std::memory_order_seq_cst );
    s_last_external_offset_us.store( sim_time_us, std::memory_order_seq_cst );
    s_use_external_time.store( true, std::memory_order_seq_cst );
    s_time_cv.notify_all();
  }


  void updateExternalTime( size_t sim_time_us )
  {
    std::scoped_lock lock( s_time_mutex );

    if( !s_use_external_time.load( std::memory_order_acquire ) )
    {
      return;
    }

    const size_t last_offset = s_last_external_offset_us.load( std::memory_order_relaxed );
    if( sim_time_us < last_offset )
    {
      LOG_WARN( "Ignoring out-of-order external time offset update (%zu < %zu)", sim_time_us, last_offset );
      return;
    }

    if( sim_time_us == last_offset )
    {
      return;
    }

    s_last_external_offset_us.store( sim_time_us, std::memory_order_release );
    s_time_cv.notify_all();
  }


  void disableExternalTimeSource()
  {
    std::scoped_lock lock( s_time_mutex );

    auto now = std::chrono::steady_clock::now();

    const int64_t baseline   = s_external_time_baseline_us.load( std::memory_order_acquire );
    const size_t last_offset = s_last_external_offset_us.load( std::memory_order_acquire );

    int64_t combined_time = baseline + static_cast<int64_t>( last_offset );
    if( combined_time < 0 )
    {
      combined_time = 0;
    }

    const auto adjusted_start = now - std::chrono::microseconds( combined_time );
    s_start_time              = adjusted_start;
    s_use_external_time.store( false, std::memory_order_release );
    s_external_time_baseline_us.store( 0, std::memory_order_release );
    s_last_external_offset_us.store( 0, std::memory_order_release );
    s_time_cv.notify_all();
  }


  bool isExternalTimeSourceActive()
  {
    return s_use_external_time.load( std::memory_order_acquire );
  }
}    // namespace Chimera::Timer::Sim

namespace Chimera::Timer::Backend
{
  Chimera::Status_t registerDriver( Chimera::Timer::Backend::DriverConfig &registry )
  {
    registry.isSupported       = true;
    registry.initialize        = ::Chimera::Timer::Sim::initialize;
    registry.reset             = ::Chimera::Timer::Sim::reset;
    registry.delayMicroseconds = ::Chimera::Timer::Sim::delayMicroseconds;
    registry.delayMilliseconds = ::Chimera::Timer::Sim::delayMilliseconds;
    registry.millis            = ::Chimera::Timer::Sim::millis;
    registry.micros            = ::Chimera::Timer::Sim::micros;
    return Chimera::Status::OK;
  }
}    // namespace Chimera::Timer::Backend

#if defined( CHIMERA_STANDALONE )
int main()
{
  // Provide an entry point for the VS project standalone compilation target
  return 0;
}
#endif

#endif /* _WIN32 || _WIN64 */
