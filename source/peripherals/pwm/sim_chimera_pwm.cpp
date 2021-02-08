/********************************************************************************
 *  File Name:
 *    sim_chimera_pwm.cpp
 *
 *  Description:
 *    Simulator PWM driver
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/pwm>

namespace Chimera::PWM::Backend
{
  Chimera::Status_t registerDriver( DriverRegistration &registry )
  {
    registry.getDriver            = nullptr;
    registry.initialize           = nullptr;
    registry.isSupported          = false;
    registry.numSupportedChannels = nullptr;
    registry.reset                = nullptr;

    return Chimera::Status::NOT_SUPPORTED;
  }
}  // namespace Chimera::PWM::Backend
