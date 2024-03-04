/********************************************************************************
 *  File Name:
 *    sim_chimera.cpp
 *
 *  Description:
 *    Simulator variant of the core chimera functionality.
 *
 *  2019-2021 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* STL Includes */
#include <atomic>
#include <cstdint>
#include <chrono>
#include <thread>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/timer>
#include <Chimera/system>

namespace ChimeraSim::Timer
{
  static size_t s_system_start;

  static size_t ms_time_since_epoch()
  {
    using namespace std::chrono;

    auto duration = system_clock::now().time_since_epoch();
    return duration_cast<milliseconds>( duration ).count();
  }

  Chimera::Status_t initialize()
  {
    s_system_start = ms_time_since_epoch();
    return Chimera::Status::OK;
  }

  Chimera::Status_t reset()
  {
    return Chimera::Status::OK;
  }

  size_t millis()
  {
    return ms_time_since_epoch() - s_system_start;
  }

  size_t micros()
  {
    return millis() * 1000;
  }

  void delayMilliseconds( const size_t val )
  {
    /* OS dependent on whether or not this sleep is accurate */
    std::this_thread::sleep_for( std::chrono::milliseconds( val ) );
  }

  void delayMicroseconds( const size_t val )
  {
    /* OS dependent on whether or not this sleep is accurate */
    std::this_thread::sleep_for( std::chrono::microseconds( val ) );
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
