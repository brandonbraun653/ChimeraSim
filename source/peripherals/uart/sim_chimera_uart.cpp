/********************************************************************************
 *  File Name:
 *    sim_chimera_uart.cpp
 *
 *  Description:
 *    UART Simulator Driver
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/uart>

namespace Chimera::UART
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
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::begin( const Chimera::Hardware::PeripheralMode txMode,
                                   const Chimera::Hardware::PeripheralMode rxMode )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::end()
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::configure( const Chimera::Serial::Config &config )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::setBaud( const uint32_t baud )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::setMode( const Chimera::Hardware::SubPeripheral periph,
                                     const Chimera::Hardware::PeripheralMode mode )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::write( const void *const buffer, const size_t length )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::read( void *const buffer, const size_t length )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::flush( const Chimera::Hardware::SubPeripheral periph )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::toggleAsyncListening( const bool state )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::readAsync( uint8_t *const buffer, const size_t len )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::enableBuffering( const Chimera::Hardware::SubPeripheral periph,
                                             Chimera::Serial::CircularBuffer &userBuffer, uint8_t *const hwBuffer,
                                             const size_t hwBufferSize )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }

  Chimera::Status_t Driver::disableBuffering( const Chimera::Hardware::SubPeripheral periph )
  {
    return Chimera::Status::NOT_SUPPORTED;
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
      return Chimera::Status::NOT_SUPPORTED;
    }


    Chimera::Status_t reset()
    {
      return Chimera::Status::NOT_SUPPORTED;
    }


    bool isChannelUART( const Chimera::Serial::Channel channel )
    {
      return false;
    }


    Driver_rPtr getDriver( const Chimera::Serial::Channel channel )
    {
      return nullptr;
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
