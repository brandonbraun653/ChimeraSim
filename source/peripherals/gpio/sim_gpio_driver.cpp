/********************************************************************************
 *  File Name:
 *    sim_gpio_driver.cpp
 *
 *  Description:
 *    GPIO Simulator
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/gpio>
#include <ChimeraSim/gpio>
#include <Thor/lld/common/types.hpp>

namespace Chimera::GPIO
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static std::array<Sim::BasicGPIO, Sim::NUM_DRIVERS> s_devices;

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
  Chimera::Status_t Driver::init( const Chimera::GPIO::PinInit &pinInit )
  {
    /*-------------------------------------------------
    Input protection
    -------------------------------------------------*/
    size_t idx = Sim::getPinResourceIndex( pinInit.port, pinInit.pin );
    if( idx == Thor::LLD::INVALID_RESOURCE_INDEX )
    {
      return Chimera::Status::NOT_SUPPORTED;
    }

    /*-------------------------------------------------
    Store reference to this device driver
    -------------------------------------------------*/
    mImpl = reinterpret_cast<void *>( &s_devices[ idx ] );

    /*-------------------------------------------------
    Invoke the basic GPIO implementation directly
    -------------------------------------------------*/
    return s_devices[ idx ].init( pinInit );
  }


  Chimera::Status_t Driver::init( const Chimera::GPIO::Port port, const uint8_t pin )
  {
    /*-------------------------------------------------
    Input protection
    -------------------------------------------------*/
    size_t idx = Sim::getPinResourceIndex( port, pin );
    if( idx == Thor::LLD::INVALID_RESOURCE_INDEX )
    {
      return Chimera::Status::NOT_SUPPORTED;
    }

    /*-------------------------------------------------
    Store reference to this device driver
    -------------------------------------------------*/
    mImpl = reinterpret_cast<void *>( &s_devices[ idx ] );

    /*-------------------------------------------------
    Invoke the basic GPIO implementation directly
    -------------------------------------------------*/
    return s_devices[ idx ].init( port, pin );
  }


  Chimera::Status_t Driver::setMode( const Chimera::GPIO::Drive drive, const Chimera::GPIO::Pull pull )
  {
    auto driver = reinterpret_cast<Sim::BasicGPIO *>( mImpl );
    return driver->setMode( drive, pull );
  }


  Chimera::Status_t Driver::setState( const Chimera::GPIO::State state )
  {
    auto driver = reinterpret_cast<Sim::BasicGPIO *>( mImpl );
    return driver->setState( state );
  }


  Chimera::Status_t Driver::getState( Chimera::GPIO::State &state )
  {
    auto driver = reinterpret_cast<Sim::BasicGPIO *>( mImpl );
    return driver->getState( state );
  }


  Chimera::Status_t Driver::toggle()
  {
    auto driver = reinterpret_cast<Sim::BasicGPIO *>( mImpl );
    return driver->toggle();
  }


  Chimera::Status_t Driver::attachInterrupt( Chimera::Function::vGeneric &func, const Chimera::EXTI::EdgeTrigger trigger )
  {
    auto driver = reinterpret_cast<Sim::BasicGPIO *>( mImpl );
    return driver->attachInterrupt( func, trigger );
  }


  void Driver::detachInterrupt()
  {
    auto driver = reinterpret_cast<Sim::BasicGPIO *>( mImpl );
    driver->detachInterrupt();
  }


  Chimera::EXTI::EventLine_t Driver::getInterruptLine()
  {
    auto driver = reinterpret_cast<Sim::BasicGPIO *>( mImpl );
    return driver->getInterruptLine();
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


    Chimera::GPIO::Driver_rPtr getDriver( const Port port, const Pin pin )
    {
      /*-------------------------------------------------
      Input Protection
      -------------------------------------------------*/
      size_t idx = Sim::getPinResourceIndex( port, pin );
      if( idx == Thor::LLD::INVALID_RESOURCE_INDEX )
      {
        return nullptr;
      }

      /*-------------------------------------------------
      Return a new driver instance for each request
      -------------------------------------------------*/
      return new Chimera::GPIO::Driver();
    }


    Chimera::Status_t registerDriver( Chimera::GPIO::Backend::DriverConfig &registry )
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
    static const std::array<uint8_t, NUM_PERIPHS> portIndex = {
      GPIOA_RESOURCE_INDEX, GPIOB_RESOURCE_INDEX, GPIOC_RESOURCE_INDEX, GPIOD_RESOURCE_INDEX,
      GPIOE_RESOURCE_INDEX, GPIOF_RESOURCE_INDEX, GPIOG_RESOURCE_INDEX, GPIOH_RESOURCE_INDEX,
      GPIOI_RESOURCE_INDEX, GPIOJ_RESOURCE_INDEX, GPIOK_RESOURCE_INDEX, GPIOL_RESOURCE_INDEX,
      GPIOM_RESOURCE_INDEX, GPION_RESOURCE_INDEX, GPIOO_RESOURCE_INDEX, GPIOP_RESOURCE_INDEX
    };

    static const std::array<uint8_t, NUM_PERIPHS> pinOffset = {
      GPIOA_PIN_RINDEX_OFFSET, GPIOB_PIN_RINDEX_OFFSET, GPIOC_PIN_RINDEX_OFFSET, GPIOD_PIN_RINDEX_OFFSET,
      GPIOE_PIN_RINDEX_OFFSET, GPIOF_PIN_RINDEX_OFFSET, GPIOG_PIN_RINDEX_OFFSET, GPIOH_PIN_RINDEX_OFFSET,
      GPIOI_PIN_RINDEX_OFFSET, GPIOJ_PIN_RINDEX_OFFSET, GPIOK_PIN_RINDEX_OFFSET, GPIOL_PIN_RINDEX_OFFSET,
      GPIOM_PIN_RINDEX_OFFSET, GPION_PIN_RINDEX_OFFSET, GPIOO_PIN_RINDEX_OFFSET, GPIOP_PIN_RINDEX_OFFSET
    };


    bool isSupported( const Chimera::GPIO::Port port, const Chimera::GPIO::Pin pin )
    {
      return ( static_cast<size_t>( port ) < NUM_PERIPHS ) && ( static_cast<size_t>( pin ) < NUM_PINS_PER_PERIPH );
    }


    size_t getPinResourceIndex( const Chimera::GPIO::Port port, const Chimera::GPIO::Pin pin )
    {
      auto retVal = Thor::LLD::INVALID_RESOURCE_INDEX;

      /*-------------------------------------------------
      Boundary check against the project's description
      -------------------------------------------------*/
      if( !isSupported( port, pin ) )
      {
        return retVal;
      }

      /*-------------------------------------------------
      Compute the index, assuming every pin exists
      -------------------------------------------------*/
      const size_t offset = pinOffset[ static_cast<uint8_t>( port ) ];
      retVal              = offset + pin;

      return retVal;
    }
  }    // namespace Sim
}    // namespace Chimera::GPIO


#endif /* CHIMERA_SIMULATOR */
