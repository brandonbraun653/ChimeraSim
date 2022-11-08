/********************************************************************************
 *  File Name:
 *    sim_chimera_uart.cpp
 *
 *  Description:
 *    UART Simulator Driver
 *
 *  2020-2022 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/common>
#include <Chimera/peripheral>
#include <Chimera/uart>

namespace Chimera::UART
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static DeviceManager<Driver, Chimera::Serial::Channel, EnumValue( Chimera::Serial::Channel::NUM_OPTIONS )> s_raw_driver;

  /*-------------------------------------------------------------------------------
  Driver Implementation
  -------------------------------------------------------------------------------*/
  Driver::Driver()
  {
  }

  Driver::~Driver()
  {
  }

  /*-------------------------------------------------
  Interface: Hardware
  -------------------------------------------------*/
  Chimera::Status_t Driver::assignHW( const Chimera::Serial::Channel channel, const Chimera::Serial::IOPins &pins )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::begin( const Chimera::Hardware::PeripheralMode txMode,
                                   const Chimera::Hardware::PeripheralMode rxMode )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::end()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::configure( const Chimera::Serial::Config &config )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setBaud( const uint32_t baud )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setMode( const Chimera::Hardware::SubPeripheral periph,
                                     const Chimera::Hardware::PeripheralMode mode )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::write( const void *const buffer, const size_t length )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::read( void *const buffer, const size_t length )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::flush( const Chimera::Hardware::SubPeripheral periph )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::toggleAsyncListening( const bool state )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::readAsync( uint8_t *const buffer, const size_t len )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::enableBuffering( const Chimera::Hardware::SubPeripheral periph,
                                             Chimera::Serial::CircularBuffer &userBuffer, uint8_t *const hwBuffer,
                                             const size_t hwBufferSize )
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t Driver::disableBuffering( const Chimera::Hardware::SubPeripheral periph )
  {
    return Chimera::Status::OK;
  }


  bool Driver::available( size_t *const bytes )
  {
    return false;
  }


  void Driver::postISRProcessing()
  {
  }


  namespace Backend
  {
    Chimera::Status_t initialize()
    {
      return Chimera::Status::OK;
    }


    Chimera::Status_t reset()
    {
      return Chimera::Status::OK;
    }


    bool isChannelUART( const Chimera::Serial::Channel channel )
    {
      return true;
    }


    Driver_rPtr getDriver( const Chimera::Serial::Channel channel )
    {
      return s_raw_driver.getOrCreate( channel );
    }

    Chimera::Status_t registerDriver( struct Chimera::UART::Backend::DriverConfig &cfg )
    {
      cfg.isSupported   = true;
      cfg.getDriver     = getDriver;
      cfg.initialize    = initialize;
      cfg.isChannelUART = isChannelUART;
      cfg.reset         = reset;

      return Chimera::Status::OK;
    }
  }    // namespace Backend

  namespace SIM
  {
  }

}    // namespace Chimera::UART

#endif /* CHIMERA_SIMULATOR */
