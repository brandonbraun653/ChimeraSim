/********************************************************************************
 *  File Name:
 *    sim_chimera_usb.cpp
 *
 *  Description:
 *    USB Simulator Driver
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/usb>

namespace Chimera::USB::Backend
{
  Chimera::Status_t registerDriver( Chimera::USB::Backend::DriverConfig &registry )
  {
    registry.isSupported = false;
    registry.getDriver   = nullptr;
    registry.initialize  = nullptr;
    registry.reset       = nullptr;

    return Chimera::Status::NOT_SUPPORTED;
  }
}  // namespace Chimera::USB::Backend
