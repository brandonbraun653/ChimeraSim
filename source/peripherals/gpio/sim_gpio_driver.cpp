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

/* STL Includes */
#include <mutex>

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/gpio>

/* Simulator Includes */
#include <ChimeraSim/gpio>
#include <ChimeraSim/source/shared/common_types.hpp>

namespace Chimera::GPIO
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static std::array<SIM::GPIODevice, SIM::NUM_DRIVERS> s_devices;

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
    size_t idx = SIM::getPinResourceIndex( pinInit.port, pinInit.pin );
    if( idx == Chimera::SIM::INVALID_RESOURCE_INDEX )
    {
      return Chimera::Status::NOT_SUPPORTED;
    }

    /*-------------------------------------------------
    Store reference to this device driver
    -------------------------------------------------*/
    mImpl = reinterpret_cast<void *>( &s_devices[ idx ] );

    /*-------------------------------------------------
    Update the driver's notion of it's resource index
    -------------------------------------------------*/
    std::lock_guard<std::recursive_mutex> lk( s_devices[ idx ].lock );
    s_devices[ idx ].resourceIndex = idx;

    /*-------------------------------------------------
    Validate and invoke the fake/mock
    -------------------------------------------------*/
    RT_HARD_ASSERT( SIM::validateDriver( &s_devices[ idx ] ) );
    return s_devices[ idx ].virtualDriver->init( pinInit );
  }


  Chimera::Status_t Driver::init( const Chimera::GPIO::Port port, const uint8_t pin )
  {
    /*-------------------------------------------------
    Input protection
    -------------------------------------------------*/
    size_t idx = SIM::getPinResourceIndex( port, pin );
    if( idx == Chimera::SIM::INVALID_RESOURCE_INDEX )
    {
      return Chimera::Status::NOT_SUPPORTED;
    }

    /*-------------------------------------------------
    Store reference to this device driver
    -------------------------------------------------*/
    mImpl = reinterpret_cast<void *>( &s_devices[ idx ] );

    /*-------------------------------------------------
    Update the driver's notion of it's resource index
    -------------------------------------------------*/
    std::lock_guard<std::recursive_mutex> lk( s_devices[ idx ].lock );
    s_devices[ idx ].resourceIndex = idx;

    /*-------------------------------------------------
    Validate and invoke the fake/mock
    -------------------------------------------------*/
    RT_HARD_ASSERT( SIM::validateDriver( &s_devices[ idx ] ) );
    return s_devices[ idx ].virtualDriver->init( port, pin );
  }


  Chimera::Status_t Driver::setMode( const Chimera::GPIO::Drive drive, const Chimera::GPIO::Pull pull )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::GPIODevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->setMode( drive, pull );
  }


  Chimera::Status_t Driver::setState( const Chimera::GPIO::State state )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::GPIODevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->setState( state );
  }


  Chimera::Status_t Driver::getState( Chimera::GPIO::State &state )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::GPIODevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->getState( state );
  }


  Chimera::Status_t Driver::toggle()
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::GPIODevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->toggle();
  }


  Chimera::Status_t Driver::attachInterrupt( Chimera::Function::vGeneric &func, const Chimera::EXTI::EdgeTrigger trigger )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::GPIODevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->attachInterrupt( func, trigger );
  }


  void Driver::detachInterrupt()
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::GPIODevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    driver->virtualDriver->detachInterrupt();
  }


  Chimera::EXTI::EventLine_t Driver::getInterruptLine()
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::GPIODevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->getInterruptLine();
  }


  /*---------------------------------------------------------------------------
  Backend Driver Registry
  ---------------------------------------------------------------------------*/
  namespace Backend
  {
    Chimera::Status_t initialize()
    {
      /*-------------------------------------------------
      Create the runtime driver instances
      -------------------------------------------------*/
      for( auto &dev : s_devices )
      {
        if( dev.initialized )
        {
          continue;
        }

        std::lock_guard<std::recursive_mutex> lk( dev.lock );
        dev.realDriver    = new Chimera::GPIO::Driver();
        dev.virtualDriver = new ::testing::NiceMock<Chimera::GPIO::SIM::MockGPIO>();
        dev.defaultDriver = new Chimera::GPIO::SIM::BasicGPIO();
        dev.initialized   = true;

        dev.virtualDriver->DelegateToFake( dev.defaultDriver );
      }

      return Chimera::Status::OK;
    }


    Chimera::Status_t reset()
    {
      // Replace all drivers with default mocks but do not invalidate pointers

      return Chimera::Status::NOT_SUPPORTED;
    }


    Chimera::GPIO::Driver_rPtr getDriver( const Port port, const Pin pin )
    {
      /*-------------------------------------------------
      Input Protection
      -------------------------------------------------*/
      size_t idx = SIM::getPinResourceIndex( port, pin );
      if( idx == Chimera::SIM::INVALID_RESOURCE_INDEX )
      {
        return nullptr;
      }

      /*-------------------------------------------------
      Get the latest assigned driver instance
      -------------------------------------------------*/
      std::lock_guard<std::recursive_mutex> lk( s_devices[ idx ].lock );
      return s_devices[ idx ].realDriver;
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
  namespace SIM
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


    void MockGPIO::DelegateToFake( IGPIO *const fake )
    {
      using ::testing::_;
      using ::testing::Matcher;

      RT_HARD_ASSERT( fake );
      mFake = fake;

      ON_CALL( *this, init( _ ) ).WillByDefault( [ this ]( const Chimera::GPIO::PinInit &a ) {
        RT_HARD_ASSERT( mFake );
        return mFake->init( a );
      } );

      ON_CALL( *this, init( _, _ ) ).WillByDefault( [ this ]( const Chimera::GPIO::Port a, const uint8_t b ) {
        RT_HARD_ASSERT( mFake );
        return mFake->init( a, b );
      } );

      ON_CALL( *this, setMode ).WillByDefault( [ this ]( const Chimera::GPIO::Drive a, const Chimera::GPIO::Pull b ) {
        RT_HARD_ASSERT( mFake );
        return mFake->setMode( a, b );
      } );

      ON_CALL( *this, attachInterrupt )
          .WillByDefault( [ this ]( Chimera::Function::vGeneric &a, const Chimera::EXTI::EdgeTrigger b ) {
            RT_HARD_ASSERT( mFake );
            return mFake->attachInterrupt( a, b );
          } );

      ON_CALL( *this, setState ).WillByDefault( [ this ]( const Chimera::GPIO::State a ) {
        RT_HARD_ASSERT( mFake );
        return mFake->setState( a );
      } );

      ON_CALL( *this, getState ).WillByDefault( [ this ]( Chimera::GPIO::State &a ) {
        RT_HARD_ASSERT( mFake );
        return mFake->getState( a );
      } );

      ON_CALL( *this, toggle ).WillByDefault( [ this ]() {
        RT_HARD_ASSERT( mFake );
        return mFake->toggle();
      } );

      ON_CALL( *this, detachInterrupt ).WillByDefault( [ this ]() {
        RT_HARD_ASSERT( mFake );
        mFake->detachInterrupt();
      } );

      ON_CALL( *this, getInterruptLine ).WillByDefault( [ this ]() {
        RT_HARD_ASSERT( mFake );
        return mFake->getInterruptLine();
      } );

      ON_CALL( *this, lock ).WillByDefault( [ this ]() {
        RT_HARD_ASSERT( mFake );
        mFake->lock();
      } );

      ON_CALL( *this, lockFromISR ).WillByDefault( [ this ]() {
        RT_HARD_ASSERT( mFake );
        mFake->lockFromISR();
      } );

      ON_CALL( *this, try_lock_for ).WillByDefault( [ this ]( const size_t a ) {
        RT_HARD_ASSERT( mFake );
        return mFake->try_lock_for( a );
      } );

      ON_CALL( *this, unlock ).WillByDefault( [ this ]() {
        RT_HARD_ASSERT( mFake );
        mFake->unlock();
      } );

      ON_CALL( *this, unlockFromISR ).WillByDefault( [ this ]() {
        RT_HARD_ASSERT( mFake );
        mFake->unlockFromISR();
      } );
    }


    bool validateDriver( void *const driver )
    {
      /*-------------------------------------------------
      First, make sure the driver is actually an instance
      of the stored GPIO device drivers.
      -------------------------------------------------*/
      bool isStoredDriver         = false;
      size_t idx                  = 0;
      std::uintptr_t inputAddress = reinterpret_cast<std::uintptr_t>( driver );

      for ( size_t x = 0; x < s_devices.size(); x++ )
      {
        if ( inputAddress == reinterpret_cast<std::uintptr_t>( &s_devices[ x ] ) )
        {
          idx            = x;
          isStoredDriver = true;
          break;
        }
      }

      if( !isStoredDriver )
      {
        return false;
      }

      /*-------------------------------------------------
      Next validate that the driver has been initialized
      and can have methods invoked on mock/fake classes.
      -------------------------------------------------*/
      std::lock_guard<std::recursive_mutex> lk( s_devices[ idx ].lock );

      /* clang-format off */
      return ( s_devices[ idx ].realDriver &&
               s_devices[ idx ].virtualDriver &&
               ( s_devices[ idx ].resourceIndex < SIM::NUM_DRIVERS ) );
      /* clang-format on */
    }


    bool isSupported( const Chimera::GPIO::Port port, const Chimera::GPIO::Pin pin )
    {
      return ( static_cast<size_t>( port ) < NUM_PERIPHS ) && ( static_cast<size_t>( pin ) < NUM_PINS_PER_PERIPH );
    }


    size_t getPinResourceIndex( const Chimera::GPIO::Port port, const Chimera::GPIO::Pin pin )
    {
      auto retVal = Chimera::SIM::INVALID_RESOURCE_INDEX;

      /*-------------------------------------------------
      Boundary check against the project's description
      -------------------------------------------------*/
      if ( !isSupported( port, pin ) )
      {
        return retVal;
      }

      /*-------------------------------------------------
      Compute the index, assuming every pin exists
      -------------------------------------------------*/
      const size_t offset = pinOffset[ static_cast<uint8_t>( port ) ];
      retVal = offset + pin;

      return retVal;
    }
  }    // namespace SIM
}    // namespace Chimera::GPIO


#endif /* CHIMERA_SIMULATOR */
