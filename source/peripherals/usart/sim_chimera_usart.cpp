/********************************************************************************
 *  File Name:
 *    sim_chimera_usart.cpp
 *
 *  Description:
 *    USART Simulator Driver
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/usart>

namespace Chimera::USART
{
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
                                             Chimera::Serial::CircularBuffer & userBuffer, uint8_t *const hwBuffer,
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
      /*-------------------------------------------------
      By default select true. Until we have a mapping for
      USART/UART channels, either driver works fine.
      -------------------------------------------------*/
      return true;
    }


    Driver_rPtr getDriver( const Chimera::Serial::Channel channel )
    {
      return nullptr;
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

  namespace SIM
  {
  }
}    // namespace Chimera::USART

#endif  /* CHIMERA_SIMULATOR */
