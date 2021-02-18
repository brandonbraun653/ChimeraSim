/********************************************************************************
 *  File Name:
 *    ctrl_intf.cpp
 *
 *  Description:
 *    Control interface implementation
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <ChimeraSim/control>
#include <ChimeraSim/gpio>
#include <ChimeraSim/spi>

namespace Chimera::SIM
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  Chimera::Status_t setDriverType( const Chimera::Peripheral::Type periph, const Driver_t driver )
  {
    AdjustDriverFunc_t callable = nullptr;
    size_t numDrivers           = 0;

    /*-------------------------------------------------
    Redirect to the proper handler for the requested
    peripheral type.
    -------------------------------------------------*/
    switch ( periph )
    {
      case Peripheral::Type::PERIPH_SPI:
        callable   = Chimera::SPI::SIM::setDriverType;
        numDrivers = Chimera::SPI::SIM::NUM_DRIVERS;
        break;

      default:
        return Chimera::Status::FAIL;
        break;
    };

    /*-------------------------------------------------
    Invoke the redirect
    -------------------------------------------------*/
    Chimera::Status_t result = Chimera::Status::OK;
    for ( size_t x = 0; x < numDrivers; x++ )
    {
      result |= callable( driver, x );
    }

    return result;
  }

}    // namespace Chimera::SIM
