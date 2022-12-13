/********************************************************************************
 *  File Name:
 *    sim_chimera_usart.cpp
 *
 *  Description:
 *    USART Simulator Driver
 *
 *  2020-2022 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/common>
#include <Chimera/peripheral>
#include <Chimera/usart>
#include <iostream>
#include <string>

namespace Chimera::USART
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static DeviceManager<Driver, Chimera::Serial::Channel, EnumValue( Chimera::Serial::Channel::NUM_OPTIONS )> s_raw_driver;

  /*---------------------------------------------------------------------------
  Driver Implementation
  ---------------------------------------------------------------------------*/
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
    this->initAIO();
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
    std::string raw_data( reinterpret_cast<const char *>( buffer ), length );

    std::cout << raw_data << std::flush;
    signalAIO( Chimera::Event::Trigger::TRIGGER_WRITE_COMPLETE );
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::read( void *const buffer, const size_t length )
  {
    signalAIO( Chimera::Event::Trigger::TRIGGER_READ_COMPLETE );
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


    bool isChannelUSART( const Chimera::Serial::Channel channel )
    {
      return true;
    }


    Driver_rPtr getDriver( const Chimera::Serial::Channel channel )
    {
      return s_raw_driver.getOrCreate( channel );
    }

    Chimera::Status_t registerDriver( struct Chimera::USART::Backend::DriverConfig &cfg )
    {
      cfg.isSupported    = true;
      cfg.getDriver      = getDriver;
      cfg.initialize     = initialize;
      cfg.isChannelUSART = isChannelUSART;
      cfg.reset          = reset;

      return Chimera::Status::OK;
    }
  }    // namespace Backend

}    // namespace Chimera::USART

#endif /* CHIMERA_SIMULATOR */
