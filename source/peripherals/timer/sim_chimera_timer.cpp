/********************************************************************************
 *  File Name:
 *    sim_chimera.cpp
 *
 *  Description:
 *    Simulator variant of the core chimera functionality.
 *
 *  2019-2024 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/common>
#include <Chimera/system>
#include <Chimera/timer>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <thread>
#include <memory>

namespace ChimeraSim::Timer
{
  /*---------------------------------------------------------------------------
  Constants
  ---------------------------------------------------------------------------*/

  /**
   * @brief Maps the number of microseconds per virtual system tick millisecond
   *
   */
  static constexpr std::chrono::microseconds SYS_TICK_PERIOD_REALTIME{ 1'000 };

  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static size_t s_system_tick;
  static std::unique_ptr<std::thread> s_tick_thread;

  /*---------------------------------------------------------------------------
  Static Functions
  ---------------------------------------------------------------------------*/

  /**
   * @brief Simulate a timer interrupt thread.
   *
   * This is a simple thread that will run in the background and simulate
   * a timer interrupt to generate a system tick reference.
   *
   */
  static void timer_thread()
  {
    while ( true )
    {
      std::this_thread::sleep_for( SYS_TICK_PERIOD_REALTIME );
      s_system_tick += 1;
    }
  }

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/

  Chimera::Status_t initialize()
  {
    s_system_tick = 0;
    s_tick_thread = std::make_unique<std::thread>( timer_thread );

    return Chimera::Status::OK;
  }


  Chimera::Status_t reset()
  {
    return Chimera::Status::OK;
  }


  size_t millis()
  {
    return s_system_tick;
  }


  size_t micros()
  {
    // TODO: Get fancy with this later.
    return millis() * 1000;
  }


  void delayMicroseconds( const size_t val )
  {
    /*-------------------------------------------------------------------------
    Do most of the wait in a blocking state
    -------------------------------------------------------------------------*/
    const size_t currentTick = micros();
    const size_t targetTick  = currentTick + val;
    const auto bulkDelayTime = std::chrono::microseconds( ( targetTick - currentTick - 1 ) );

    if( bulkDelayTime > SYS_TICK_PERIOD_REALTIME )
    {
      auto actual_sleep_time = bulkDelayTime - SYS_TICK_PERIOD_REALTIME;
      std::this_thread::sleep_for( bulkDelayTime );
    }

    /*-------------------------------------------------------------------------
    Do the rest of the wait in a busy loop, which should be very short
    -------------------------------------------------------------------------*/
    while ( micros() < targetTick )
    {
      continue;
    }
  }


  void delayMilliseconds( const size_t val )
  {
    delayMicroseconds( val * 1000 );
  }
}

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
}

#if defined( CHIMERA_STANDALONE )
int main()
{
  // Provide an entry point for the VS project standalone compilation target
  return 0;
}
#endif


#endif /* _WIN32 || _WIN64 */
