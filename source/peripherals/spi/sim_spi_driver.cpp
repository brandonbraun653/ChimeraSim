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
#include <mutex>

namespace Chimera::SPI
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static std::array<Sim::BasicSPI, Sim::NUM_DRIVERS> s_devices;

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
  Chimera::Status_t Driver::init( const Chimera::SPI::DriverConfig &setupStruct )
  {
    /*-------------------------------------------------
    Input protection
    -------------------------------------------------*/
    size_t idx = Sim::getResourceIndex( setupStruct.HWInit.hwChannel );
    if( idx == Thor::LLD::INVALID_RESOURCE_INDEX )
    {
      return Chimera::Status::NOT_SUPPORTED;
    }

    /*-------------------------------------------------
    Store reference to this device driver
    -------------------------------------------------*/
    mImpl = reinterpret_cast<void *>( &s_devices[ idx ] );

    /*-------------------------------------------------------------------------
    Ensure this driver's instance of AsyncIO is initialized
    -------------------------------------------------------------------------*/
    this->initAIO();

    /*-------------------------------------------------
    Invoke the basic SPI implementation directly
    -------------------------------------------------*/
    return s_devices[ idx ].init( setupStruct );
  }


  Chimera::SPI::HardwareInit Driver::getInit()
  {
    auto driver = reinterpret_cast<Sim::BasicSPI *>( mImpl );
    return driver->getInit();
  }


  Chimera::Status_t Driver::deInit()
  {
    auto driver = reinterpret_cast<Sim::BasicSPI *>( mImpl );
    return driver->deInit();
  }


  Chimera::Status_t Driver::assignChipSelect( const Chimera::GPIO::Driver_rPtr cs )
  {
    auto driver = reinterpret_cast<Sim::BasicSPI *>( mImpl );
    return driver->assignChipSelect( cs );
  }


  Chimera::Status_t Driver::setChipSelect( const Chimera::GPIO::State value )
  {
    auto driver = reinterpret_cast<Sim::BasicSPI *>( mImpl );
    return driver->setChipSelect( value );
  }


  Chimera::Status_t Driver::setChipSelectControlMode( const Chimera::SPI::CSMode mode )
  {
    auto driver = reinterpret_cast<Sim::BasicSPI *>( mImpl );
    return driver->setChipSelectControlMode( mode );
  }


  Chimera::Status_t Driver::writeBytes( const void *const txBuffer, const size_t length )
  {
    auto driver = reinterpret_cast<Sim::BasicSPI *>( mImpl );
    auto result = driver->writeBytes( txBuffer, length );
    this->signalAIO( Chimera::Event::Trigger::TRIGGER_TRANSFER_COMPLETE );
    return result;
  }


  Chimera::Status_t Driver::readBytes( void *const rxBuffer, const size_t length )
  {
    auto driver = reinterpret_cast<Sim::BasicSPI *>( mImpl );
    auto result = driver->readBytes( rxBuffer, length );
    this->signalAIO( Chimera::Event::Trigger::TRIGGER_TRANSFER_COMPLETE );
    return result;
  }


  Chimera::Status_t Driver::readWriteBytes( const void *const txBuffer, void *const rxBuffer, const size_t length )
  {
    auto driver = reinterpret_cast<Sim::BasicSPI *>( mImpl );
    auto result = driver->readWriteBytes( txBuffer, rxBuffer, length );
    this->signalAIO( Chimera::Event::Trigger::TRIGGER_TRANSFER_COMPLETE );
    return result;
  }


  Chimera::Status_t Driver::setPeripheralMode( const Chimera::Hardware::PeripheralMode mode )
  {
    auto driver = reinterpret_cast<Sim::BasicSPI *>( mImpl );
    return driver->setPeripheralMode( mode );
  }


  Chimera::Status_t Driver::setClockFrequency( const size_t freq, const size_t tolerance )
  {
    auto driver = reinterpret_cast<Sim::BasicSPI *>( mImpl );
    return driver->setClockFrequency( freq, tolerance );
  }


  size_t Driver::getClockFrequency()
  {
    auto driver = reinterpret_cast<Sim::BasicSPI *>( mImpl );
    return driver->getClockFrequency();
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
      /*-------------------------------------------------
      Input Protection
      -------------------------------------------------*/
      size_t idx = Sim::getResourceIndex( channel );
      if( idx == Thor::LLD::INVALID_RESOURCE_INDEX )
      {
        return nullptr;
      }

      /*-------------------------------------------------
      Return a new driver instance for each request
      -------------------------------------------------*/
      return new Chimera::SPI::Driver();
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

      /*-------------------------------------------------
      Boundary check against the project's description
      -------------------------------------------------*/
      if( !isSupported( channel ) )
      {
        return retVal;
      }

      /*-------------------------------------------------
      Sim should support every possible SPI channel
      -------------------------------------------------*/
      static_assert( NUM_DRIVERS == static_cast<size_t>( Chimera::SPI::Channel::NUM_OPTIONS ) );
      return static_cast<size_t>( channel );
    }
  }    // namespace Sim
}    // namespace Chimera::SPI

#endif /* CHIMERA_SIMULATOR */
