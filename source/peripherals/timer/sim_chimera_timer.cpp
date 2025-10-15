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

namespace ChimeraSim::Timer
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static std::chrono::steady_clock::time_point s_start_time;
  static std::atomic<bool> s_use_external_time{ false };
  static std::atomic<int64_t> s_external_time_offset_us{ 0 }; /**< Offset from realtime microseconds */
  static std::atomic<size_t> s_last_external_time_us{ 0 };    /**< Last accepted external timestamp */
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
      const int64_t offset = s_external_time_offset_us.load( std::memory_order_acquire );
      const size_t last    = s_last_external_time_us.load( std::memory_order_acquire );

      int64_t combined = offset + static_cast<int64_t>( last );
      if( combined < 0 )
      {
        combined = 0;
      }

      const int64_t max_size = static_cast<int64_t>( SIZE_MAX_VALUE );
      if( combined > max_size )
      {
        combined = max_size;
      }

      return static_cast<size_t>( combined );
    }
  }    // namespace

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/

  Chimera::Status_t initialize()
  {
    s_start_time = std::chrono::steady_clock::now();
    s_use_external_time.store( false, std::memory_order_release );
    s_external_time_offset_us.store( 0, std::memory_order_release );
    s_last_external_time_us.store( 0, std::memory_order_release );
    s_time_cv.notify_all();
    return Chimera::Status::OK;
  }


  Chimera::Status_t reset()
  {
    return initialize();
  }


  size_t millis()
  {
    return micros() / 1000U;
  }


  size_t micros()
  {
    const auto now = std::chrono::steady_clock::now();

    if( s_use_external_time.load( std::memory_order_acquire ) )
    {
      return currentExternalMicros();
    }
    else
    {
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>( now - s_start_time );
      return static_cast<size_t>( duration.count() );
    }
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

    auto now          = std::chrono::steady_clock::now();
    auto real_elapsed = std::chrono::duration_cast<std::chrono::microseconds>( now - s_start_time );

    const int64_t new_offset = static_cast<int64_t>( real_elapsed.count() ) - static_cast<int64_t>( sim_time_us );

    s_last_external_time_us.store( sim_time_us, std::memory_order_release );
    s_external_time_offset_us.store( new_offset, std::memory_order_release );
    s_use_external_time.store( true, std::memory_order_release );
    s_time_cv.notify_all();
  }


  void updateExternalTime( size_t sim_time_us )
  {
    std::scoped_lock lock( s_time_mutex );

    if( !s_use_external_time.load( std::memory_order_acquire ) )
    {
      return;
    }

    const size_t last_time = s_last_external_time_us.load( std::memory_order_relaxed );
    if( sim_time_us < last_time )
    {
      LOG_WARN( "Timer: Ignoring out-of-order Matlab sim time update (%zu < %zu)", sim_time_us, last_time );
      return;
    }

    if( sim_time_us == last_time )
    {
      LOG_DEBUG( "Timer: Ignoring duplicate Matlab sim time update (%zu)", sim_time_us );
      return;
    }

    s_last_external_time_us.store( sim_time_us, std::memory_order_release );
    s_time_cv.notify_all();
  }


  void disableExternalTimeSource()
  {
    std::scoped_lock lock( s_time_mutex );

    auto now = std::chrono::steady_clock::now();

    const size_t final_external = s_last_external_time_us.load( std::memory_order_acquire );
    const int64_t offset        = s_external_time_offset_us.load( std::memory_order_acquire );

    int64_t combined_time = offset + static_cast<int64_t>( final_external );
    if( combined_time < 0 )
    {
      combined_time = 0;
    }

    const auto adjusted_start = now - std::chrono::microseconds( combined_time );
    s_start_time              = adjusted_start;
    s_use_external_time.store( false, std::memory_order_release );
    s_external_time_offset_us.store( 0, std::memory_order_release );
    s_last_external_time_us.store( 0, std::memory_order_release );
    s_time_cv.notify_all();
  }


  bool isExternalTimeSourceActive()
  {
    return s_use_external_time.load( std::memory_order_acquire );
  }
}    // namespace ChimeraSim::Timer

namespace Chimera::Timer::Backend
{
  Chimera::Status_t registerDriver( Chimera::Timer::Backend::DriverConfig &registry )
  {
    registry.isSupported       = true;
    registry.initialize        = ::ChimeraSim::Timer::initialize;
    registry.reset             = ::ChimeraSim::Timer::reset;
    registry.delayMicroseconds = ::ChimeraSim::Timer::delayMicroseconds;
    registry.delayMilliseconds = ::ChimeraSim::Timer::delayMilliseconds;
    registry.millis            = ::ChimeraSim::Timer::millis;
    registry.micros            = ::ChimeraSim::Timer::micros;
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
