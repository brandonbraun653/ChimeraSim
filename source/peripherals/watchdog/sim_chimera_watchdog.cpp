/********************************************************************************
 *  File Name:
 *    sim_chimera_watchdog.cpp
 *
 *  Description:
 *    Watchdog Simulator
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/watchdog>

namespace Chimera::Watchdog
{
  namespace Backend
  {
    Chimera::Status_t initialize()
    {
      return Chimera::Status::NOT_SUPPORTED;
    }


    Chimera::Status_t reset()
    {
      return Chimera::Status::NOT_SUPPORTED;
    }


    Chimera::Watchdog::Independent_rPtr getDriver( const IChannel channel )
    {
      return nullptr;
    }


    Chimera::Watchdog::Window_rPtr getDriver( const WChannel channel )
    {
      return nullptr;
    }


    Chimera::Status_t registerDriver( Chimera::Watchdog::Backend::DriverConfig &registry )
    {
      registry.isSupported          = true;
      registry.getIndependentDriver = getDriver;
      registry.getWindowDriver      = getDriver;
      registry.initialize           = initialize;
      registry.reset                = reset;
      return Chimera::Status::OK;
    }
  }    // namespace Backend
}    // namespace Chimera::Watchdog

#endif /* CHIMERA_SIMULATOR */