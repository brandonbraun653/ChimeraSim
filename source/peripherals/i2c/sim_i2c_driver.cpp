/******************************************************************************
 *  File Name:
 *    sim_i2c_driver.cpp
 *
 *  Description:
 *    I2C Simulator
 *
 *  2022 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/i2c>
#include <Chimera/assert>
#include <Chimera/peripheral>
#include <ChimeraSim/i2c>
#include <ChimeraSim/source/shared/common_types.hpp>

namespace Chimera::I2C
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static DeviceManager<Driver, Channel, EnumValue( Channel::NUM_OPTIONS )> s_raw_driver;

  /*---------------------------------------------------------------------------
  Static Functions
  ---------------------------------------------------------------------------*/
  static Chimera::Status_t impl_initialize()
  {
    return Chimera::Status::OK;
  }


  static Chimera::Status_t impl_reset()
  {
    return Chimera::Status::OK;
  }


  static Driver_rPtr impl_getDriver( const Chimera::I2C::Channel channel )
  {
    return s_raw_driver.getOrCreate( channel );
  }

  namespace Backend
  {
    Chimera::Status_t registerDriver( Chimera::I2C::Backend::DriverConfig &registry )
    {
      registry.isSupported = true;
      registry.getDriver   = ::Chimera::I2C::impl_getDriver;
      registry.initialize  = ::Chimera::I2C::impl_initialize;
      registry.reset       = ::Chimera::I2C::impl_reset;
      return Chimera::Status::OK;
    }
  }    // namespace Backend


  /*---------------------------------------------------------------------------
  Driver Implementation
  ---------------------------------------------------------------------------*/
  Driver::Driver()
  {
  }


  Driver::~Driver()
  {
  }


  Chimera::Status_t Driver::open( const DriverConfig &cfg )
  {
    /*-------------------------------------------------------------------------
    Ensure the AsyncIO driver is ready
    -------------------------------------------------------------------------*/
    this->initAIO();

    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::close()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::read( const uint16_t address, void *const data, const size_t length )
  {
    return transfer( address, nullptr, data, length );
  }


  Chimera::Status_t Driver::write( const uint16_t address, const void *const data, const size_t length )
  {
    return transfer( address, data, nullptr, length );
  }


  Chimera::Status_t Driver::transfer( const uint16_t address, const void *const tx_data, void *const rx_data,
                                      const size_t length )
  {
    this->signalAIO( Chimera::Event::Trigger::TRIGGER_TRANSFER_COMPLETE );
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::stop()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::start()
  {
    return Chimera::Status::OK;
  }

}    // namespace Chimera::I2C
