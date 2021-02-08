/********************************************************************************
 *  File Name:
 *    sim_chimera_gpio.cpp
 *
 *  Description:
 *    Interrupt Simulator
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/interrupt>

namespace Chimera::Interrupt::Backend
{
  Chimera::Status_t registerDriver( Chimera::Interrupt::Backend::DriverConfig &registry )
  {
    registry.isSupported        = false;
    registry.initialize         = nullptr;
    registry.reset              = nullptr;
    registry.registerISRHandler = nullptr;
    return Chimera::Status::NOT_SUPPORTED;
  }
}  // namespace Chimera::Interrupt::Backend

#endif /* CHIMERA_SIMULATOR */