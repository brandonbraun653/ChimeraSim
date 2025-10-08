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
#include <Chimera/common>
#include <Chimera/system>
#include <Chimera/timer>
#include <chrono>
#include <thread>

namespace ChimeraSim::Timer
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static std::chrono::steady_clock::time_point s_start_time;

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/

  Chimera::Status_t initialize()
  {
    s_start_time = std::chrono::steady_clock::now();
    return Chimera::Status::OK;
  }


  Chimera::Status_t reset()
  {
    return Chimera::Status::OK;
  }


  size_t millis()
  {
    auto now      = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( now - s_start_time );
    return static_cast<size_t>( duration.count() );
  }


  size_t micros()
  {
    auto now      = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( now - s_start_time );
    return static_cast<size_t>( duration.count() );
  }


  void delayMicroseconds( const size_t val )
  {
    std::this_thread::sleep_for( std::chrono::microseconds( val ) );
  }


  void delayMilliseconds( const size_t val )
  {
    std::this_thread::sleep_for( std::chrono::milliseconds( val ) );
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
