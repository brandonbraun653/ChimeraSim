/********************************************************************************
 *  File Name:
 *    sim_chimera_clock.cpp
 *
 *  Description:
 *    Simulator Clock Driver
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/clock>


namespace Chimera::Clock::Backend
{
  Chimera::Status_t registerDriver( Chimera::Clock::Backend::DriverConfig &registry )
  {
    registry.disableClock  = nullptr;
    registry.enableClock   = nullptr;
    registry.getFrequency  = nullptr;
    registry.initialize    = nullptr;
    registry.isEnabled     = nullptr;
    registry.isSupported   = false;
    registry.periphDisable = nullptr;
    registry.periphEnable  = nullptr;
    registry.setFrequency  = nullptr;

    return Chimera::Status::NOT_SUPPORTED;
  }

}  // namespace Chimera::Clock::Backend
