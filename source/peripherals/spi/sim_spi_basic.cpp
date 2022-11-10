/********************************************************************************
 *  File Name:
 *    sim_spi_basic.cpp
 *
 *  Description:
 *    Virtual SPI implementations
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/spi>

/* Simulator Includes */
#include <ChimeraSim/spi>
#include <ChimeraSim/source/peripherals/spi/sim_spi_virtual.hpp>

namespace Chimera::SPI::SIM
{
  /*-------------------------------------------------------------------------------
  Basic SPI Implementation
  -------------------------------------------------------------------------------*/
  Chimera::Status_t BasicSPI::init( const Chimera::SPI::DriverConfig &setupStruct )
  {
    this->initAIO();
    mHWState.config = setupStruct;
    return Chimera::Status::OK;
  }


  Chimera::Status_t BasicSPI::deInit()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t BasicSPI::assignChipSelect( const Chimera::GPIO::Driver_rPtr cs )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t BasicSPI::setChipSelect( const Chimera::GPIO::State value )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t BasicSPI::setChipSelectControlMode( const Chimera::SPI::CSMode mode )
  {
    mHWState.config.HWInit.csMode = mode;
    return Chimera::Status::OK;
  }


  Chimera::Status_t BasicSPI::writeBytes( const void *const txBuffer, const size_t length )
  {
    return readWriteBytes( txBuffer, nullptr, length );
  }


  Chimera::Status_t BasicSPI::readBytes( void *const rxBuffer, const size_t length )
  {
    return readWriteBytes( nullptr, rxBuffer, length );
  }


  Chimera::Status_t BasicSPI::readWriteBytes( const void *const txBuffer, void *const rxBuffer, const size_t length )
  {
    this->signalAIO( Chimera::Event::Trigger::TRIGGER_TRANSFER_COMPLETE );
    return Chimera::Status::OK;
  }


  Chimera::Status_t BasicSPI::setPeripheralMode( const Chimera::Hardware::PeripheralMode mode )
  {
    mHWState.periphMode = mode;
    return Chimera::Status::OK;
  }


  Chimera::Status_t BasicSPI::setClockFrequency( const size_t freq, const size_t tolerance )
  {
    mHWState.clockFrequency = freq;
    return Chimera::Status::OK;
  }


  Chimera::SPI::HardwareInit BasicSPI::getInit()
  {
    return mHWState.config.HWInit;
  }


  size_t BasicSPI::getClockFrequency()
  {
    return mHWState.clockFrequency;
  }

}    // namespace Chimera::SPI::SIM
