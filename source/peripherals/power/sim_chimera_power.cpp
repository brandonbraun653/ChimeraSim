/********************************************************************************
 *  File Name:
 *    sim_chimera_power.cpp
 *
 *  Description:
 *    Simulator POWER driver
 *
 *  2025 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/power>

namespace Chimera::Power::Backend
{
  Chimera::Status_t initialize()
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t reset()
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t periphEnable( [[maybe_unused]] const Chimera::Peripheral::Type periph )
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t periphDisable( [[maybe_unused]] const Chimera::Peripheral::Type periph )
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t setPowerState( [[maybe_unused]] const Chimera::Power::State state )
  {
    return Chimera::Status::OK;
  }

  Chimera::Power::State getPowerState( [[maybe_unused]] const Chimera::Peripheral::Type periph )
  {
    return Chimera::Power::State::ON;
  }

  Chimera::Status_t registerDriver( Chimera::Power::Backend::DriverConfig &registry )
  {
    registry.isSupported = true;
    registry.initialize = initialize;
    registry.reset = reset;
    registry.periphEnable = periphEnable;
    registry.periphDisable = periphDisable;
    registry.setPowerState = setPowerState;
    registry.getPowerState = getPowerState;
    return Chimera::Status::OK;
  }
}  // namespace Chimera::Power::Backend
