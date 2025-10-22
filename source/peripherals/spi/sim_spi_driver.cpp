/********************************************************************************
 *  File Name:
 *    sim_chimera_spi.cpp
 *
 *  Description:
 *    SPI Simulator
 *
 *  2020-2022 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/spi>
#include <ChimeraSim/spi>
#include <Thor/lld/common/types.hpp>

namespace Chimera::SPI
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static std::array<Driver, Sim::NUM_DRIVERS> s_devices;

  /*---------------------------------------------------------------------------
  Driver Implementation
  ---------------------------------------------------------------------------*/
  Driver::Driver() : mImpl( nullptr )
  {
  }

  Driver::~Driver()
  {
  }


  /*-------------------------------------------------
  Interface: Hardware
  -------------------------------------------------*/
  Chimera::Status_t Driver::init( const Chimera::SPI::DriverConfig &setupStruct )
  {
    return Chimera::Status::OK;
  }


  Chimera::SPI::HardwareInit Driver::getInit()
  {
    return Chimera::SPI::HardwareInit();
  }


  Chimera::Status_t Driver::deInit()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::assignChipSelect( const Chimera::GPIO::Driver_rPtr cs )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setChipSelect( const Chimera::GPIO::State value )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setChipSelectControlMode( const Chimera::SPI::CSMode mode )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::writeBytes( const void *const txBuffer, const size_t length )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::readBytes( void *const rxBuffer, const size_t length )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::readWriteBytes( const void *const txBuffer, void *const rxBuffer, const size_t length )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setPeripheralMode( const Chimera::Hardware::PeripheralMode mode )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setClockFrequency( const size_t freq, const size_t tolerance )
  {
    return Chimera::Status::OK;
  }


  size_t Driver::getClockFrequency()
  {
    return 0;
  }


  /*---------------------------------------------------------------------------
  Backend Driver Registry
  ---------------------------------------------------------------------------*/
  namespace Backend
  {
    Chimera::Status_t initialize()
    {
      return Chimera::Status::OK;
    }


    Chimera::Status_t reset()
    {
      return Chimera::Status::NOT_SUPPORTED;
    }


    Driver_rPtr getDriver( const Channel channel )
    {
      size_t idx = Sim::getResourceIndex( channel );
      RT_HARD_ASSERT( idx < s_devices.size() );

      return &s_devices[ idx ];
    }


    Chimera::Status_t registerDriver( Chimera::SPI::Backend::DriverConfig &registry )
    {
      registry.isSupported = true;
      registry.getDriver   = getDriver;
      registry.initialize  = initialize;
      registry.reset       = reset;
      return Chimera::Status::OK;
    }
  }    // namespace Backend


  /*---------------------------------------------------------------------------
  Simulator Implementation Details
  ---------------------------------------------------------------------------*/
  namespace Sim
  {
    bool isSupported( const Chimera::SPI::Channel channel )
    {
      return ( static_cast<size_t>( channel ) < NUM_DRIVERS );
    }


    size_t getResourceIndex( const Chimera::SPI::Channel channel )
    {
      auto retVal = Thor::LLD::INVALID_RESOURCE_INDEX;

      if( !isSupported( channel ) )
      {
        return retVal;
      }

      static_assert( NUM_DRIVERS == static_cast<size_t>( Chimera::SPI::Channel::NUM_OPTIONS ) );
      return static_cast<size_t>( channel );
    }
  }    // namespace Sim
}    // namespace Chimera::SPI

#endif /* CHIMERA_SIMULATOR */
