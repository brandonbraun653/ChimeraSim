/********************************************************************************
 *  File Name:
 *    sim_chimera_adc.cpp
 *
 *  Description:
 *    adc Simulator
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/adc>

namespace Chimera::ADC::Backend
{
  Chimera::Status_t registerDriver( Chimera::ADC::Backend::DriverConfig &registry )
  {
    registry.isSupported = false;
    registry.getDriver   = nullptr;
    registry.initialize  = nullptr;
    registry.reset       = nullptr;
    return Chimera::Status::NOT_SUPPORTED;
  }
}  // namespace Chimera::ADC::Backend

#endif /* CHIMERA_SIMULATOR */