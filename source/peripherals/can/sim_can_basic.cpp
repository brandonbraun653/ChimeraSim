/********************************************************************************
 *  File Name:
 *    sim_chimera_can.cpp
 *
 *  Description:
 *    CAN Simulator
 *
 *  2020-2022 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/common>
#include <Chimera/can>
#include <Chimera/peripheral>

namespace Chimera::CAN
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


  static Driver_rPtr impl_getDriver( const Chimera::CAN::Channel channel )
  {
    return s_raw_driver.getOrCreate( channel );
  }

  namespace Backend
  {
    Chimera::Status_t registerDriver( Chimera::CAN::Backend::DriverConfig &registry )
    {
      registry.isSupported = true;
      registry.getDriver   = ::Chimera::CAN::impl_getDriver;
      registry.initialize  = ::Chimera::CAN::impl_initialize;
      registry.reset       = ::Chimera::CAN::impl_reset;
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
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::close()
  {
    return Chimera::Status::OK;
  }


  CANStatus Driver::getStatus()
  {
    return {};
  }


  Chimera::Status_t Driver::send( const BasicFrame &frame )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::receive( BasicFrame &frame )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::filter( const Filter *const list, const size_t size )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::flush( BufferType buffer )
  {
    return Chimera::Status::OK;
  }


  size_t Driver::available()
  {
    return 0;
  }

}    // namespace Chimera::CAN

#endif /* CHIMERA_SIMULATOR */