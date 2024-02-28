/********************************************************************************
 *  File Name:
 *    sim_chimera_serial.cpp
 *
 *  Description:
 *    Serial Simulator Driver
 *
 *  2024 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Aurora/utility>
#include <Chimera/common>
#include <Chimera/peripheral>
#include <Chimera/serial>
#include <iostream>
#include <string>

namespace Chimera::Serial
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


  Chimera::Status_t Driver::open( const Chimera::Serial::Config &config )
  {
    this->initAIO();
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::close()
  {
    return Chimera::Status::OK;
  }


  int Driver::write( const void *const buffer, const size_t length, const size_t timeout )
  {
    std::string raw_data( reinterpret_cast<const char *>( buffer ), length );

    std::cout << raw_data << std::flush;
    signalAIO( Chimera::Event::Trigger::TRIGGER_WRITE_COMPLETE );
    return length;
  }


  int Driver::read( void *const buffer, const size_t length, const size_t timeout )
  {
    signalAIO( Chimera::Event::Trigger::TRIGGER_READ_COMPLETE );
    return length;
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


    Chimera::Status_t registerDriver( struct Chimera::Serial::Backend::DriverConfig &cfg )
    {
      cfg.isSupported   = true;
      cfg.getDriver     = getDriver;
      cfg.initialize    = initialize;
      cfg.reset         = reset;

      return Chimera::Status::OK;
    }
  }    // namespace Backend

  namespace SIM
  {
  }

}    // namespace Chimera::UART

#endif /* CHIMERA_SIMULATOR */
