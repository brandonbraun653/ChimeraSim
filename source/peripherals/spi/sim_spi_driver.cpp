/********************************************************************************
 *  File Name:
 *    sim_chimera_spi.cpp
 *
 *  Description:
 *    SPI Simulator
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* STL Includes */
#include <mutex>

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/spi>

/* Simulator Includes */
#include <ChimeraSim/spi>
#include <ChimeraSim/source/shared/common_types.hpp>

namespace Chimera::SPI
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static std::array<SIM::SPIDevice, SIM::NUM_DRIVERS> s_devices;

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
  Chimera::Status_t Driver::init( const Chimera::SPI::DriverConfig &setupStruct )
  {
    /*-------------------------------------------------
    Input protection
    -------------------------------------------------*/
    size_t idx = SIM::getResourceIndex( setupStruct.HWInit.hwChannel );
    if ( idx == Chimera::SIM::INVALID_RESOURCE_INDEX )
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
    return s_devices[ idx ].virtualDriver->init( setupStruct );
  }


  Chimera::SPI::HardwareInit Driver::getInit()
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::SPIDevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->getInit();
  }


  Chimera::Status_t Driver::deInit()
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::SPIDevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->deInit();
  }


  Chimera::Status_t Driver::assignChipSelect( const Chimera::GPIO::Driver_rPtr cs )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::SPIDevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->assignChipSelect( cs );
  }


  Chimera::Status_t Driver::setChipSelect( const Chimera::GPIO::State value )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::SPIDevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->setChipSelect( value );
  }


  Chimera::Status_t Driver::setChipSelectControlMode( const Chimera::SPI::CSMode mode )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::SPIDevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->setChipSelectControlMode( mode );
  }


  Chimera::Status_t Driver::writeBytes( const void *const txBuffer, const size_t length )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::SPIDevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->writeBytes( txBuffer, length );
  }


  Chimera::Status_t Driver::readBytes( void *const rxBuffer, const size_t length )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::SPIDevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->readBytes( rxBuffer, length );
  }


  Chimera::Status_t Driver::readWriteBytes( const void *const txBuffer, void *const rxBuffer, const size_t length )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::SPIDevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->readWriteBytes( txBuffer, rxBuffer, length );
  }


  Chimera::Status_t Driver::setPeripheralMode( const Chimera::Hardware::PeripheralMode mode )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::SPIDevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->setPeripheralMode( mode );
  }


  Chimera::Status_t Driver::setClockFrequency( const size_t freq, const size_t tolerance )
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::SPIDevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->setClockFrequency( freq, tolerance );
  }


  size_t Driver::getClockFrequency()
  {
    RT_HARD_ASSERT( SIM::validateDriver( mImpl ) );
    auto driver = reinterpret_cast<SIM::SPIDevice *>( mImpl );

    std::lock_guard<std::recursive_mutex> lk( driver->lock );
    return driver->virtualDriver->getClockFrequency();
  }


  /*-------------------------------------------------------------------------------
  Backend Driver Registry
  -------------------------------------------------------------------------------*/
  namespace Backend
  {
    Chimera::Status_t initialize()
    {
      /*-------------------------------------------------
      Create the runtime driver instances
      -------------------------------------------------*/
      for ( auto &dev : s_devices )
      {
        if ( dev.initialized )
        {
          continue;
        }

        std::lock_guard<std::recursive_mutex> lk( dev.lock );
        dev.realDriver      = new Chimera::SPI::Driver();
        dev.virtualDriver   = new ::testing::NiceMock<Chimera::SPI::SIM::MockSPI>();
        dev.defaultDriver   = new Chimera::SPI::SIM::BasicSPI();
        dev.networkedDriver = new Chimera::SPI::SIM::NetworkedSPI();
        dev.initialized     = true;

        dev.virtualDriver->DelegateToFake( dev.defaultDriver );
      }

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
      size_t idx = SIM::getResourceIndex( channel );
      if ( idx == Chimera::SIM::INVALID_RESOURCE_INDEX )
      {
        return nullptr;
      }

      /*-------------------------------------------------
      Get the latest assigned driver instance
      -------------------------------------------------*/
      std::lock_guard<std::recursive_mutex> lk( s_devices[ idx ].lock );
      return s_devices[ idx ].realDriver;
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


  /*-------------------------------------------------------------------------------
  Simulator
  -------------------------------------------------------------------------------*/
  namespace SIM
  {
    /*-------------------------------------------------------------------------------
    Public Functions
    -------------------------------------------------------------------------------*/
    Chimera::Status_t setDriverType( const Chimera::SIM::Driver_t type, const size_t idx )
    {
      using namespace Chimera::SIM;

      /*-------------------------------------------------
      Input Protection
      -------------------------------------------------*/
      if ( !( type < Driver_t::NUM_OPTIONS ) || !( idx < NUM_DRIVERS ) )
      {
        return Chimera::Status::INVAL_FUNC_PARAM;
      }
      else if ( !s_devices[ idx ].initialized )
      {
        return Chimera::Status::NOT_READY;
      }

      /*-------------------------------------------------
      Invoke the re-registration
      -------------------------------------------------*/
      std::lock_guard<std::recursive_mutex> lk( s_devices[ idx ].lock );
      switch ( type )
      {
        case Driver_t::BASIC_STUB:
          s_devices[ idx ].virtualDriver->DelegateToFake( s_devices[ idx ].defaultDriver );
          break;

        case Driver_t::NETWORKED_CONTROL:
          s_devices[ idx ].virtualDriver->DelegateToFake( s_devices[ idx ].networkedDriver );
          break;

        default:
          return Chimera::Status::NOT_SUPPORTED;
          break;
      };

      return Chimera::Status::OK;
    }

    /*-------------------------------------------------------------------------------
    Mock Driver
    -------------------------------------------------------------------------------*/
    void MockSPI::DelegateToFake( ISPI *const fake )
    {
      using ::testing::_;
      using ::testing::Matcher;

      RT_HARD_ASSERT( fake );
      mFake = fake;

      ON_CALL( *this, init ).WillByDefault( [ this ]( const Chimera::SPI::DriverConfig &a ) {
        RT_HARD_ASSERT( mFake );
        return mFake->init( a );
      } );

      ON_CALL( *this, deInit ).WillByDefault( [ this ]() {
        RT_HARD_ASSERT( mFake );
        return mFake->deInit();
      } );

      ON_CALL( *this, setChipSelect ).WillByDefault( [ this ]( const Chimera::GPIO::State a ) {
        RT_HARD_ASSERT( mFake );
        return mFake->setChipSelect( a );
      } );

      ON_CALL( *this, setChipSelectControlMode ).WillByDefault( [ this ]( const Chimera::SPI::CSMode a ) {
        RT_HARD_ASSERT( mFake );
        return mFake->setChipSelectControlMode( a );
      } );

      ON_CALL( *this, writeBytes ).WillByDefault( [ this ]( const void *const a, const size_t b ) {
        RT_HARD_ASSERT( mFake );
        return mFake->writeBytes( a, b );
      } );

      ON_CALL( *this, readBytes ).WillByDefault( [ this ]( void *const a, const size_t b ) {
        RT_HARD_ASSERT( mFake );
        return mFake->readBytes( a, b );
      } );

      ON_CALL( *this, readWriteBytes ).WillByDefault( [ this ]( const void *const a, void *const b, const size_t c ) {
        RT_HARD_ASSERT( mFake );
        return mFake->readWriteBytes( a, b, c );
      } );

      ON_CALL( *this, setPeripheralMode ).WillByDefault( [ this ]( const Chimera::Hardware::PeripheralMode a ) {
        RT_HARD_ASSERT( mFake );
        return mFake->setPeripheralMode( a );
      } );

      ON_CALL( *this, setClockFrequency ).WillByDefault( [ this ]( const size_t a, const size_t b ) {
        RT_HARD_ASSERT( mFake );
        return mFake->setClockFrequency( a, b );
      } );

      ON_CALL( *this, await( _, _ ) ).WillByDefault( [ this ]( const Chimera::Event::Trigger a, const size_t b ) {
        RT_HARD_ASSERT( mFake );
        return mFake->await( a, b );
      } );

      ON_CALL( *this, await( _, _, _ ) )
          .WillByDefault( [ this ]( const Chimera::Event::Trigger a, Chimera::Thread::BinarySemaphore &b, const size_t c ) {
            RT_HARD_ASSERT( mFake );
            return mFake->await( a, b, c );
          } );

      ON_CALL( *this, getInit ).WillByDefault( [ this ]() {
        RT_HARD_ASSERT( mFake );
        return mFake->getInit();
      } );

      ON_CALL( *this, getClockFrequency ).WillByDefault( [ this ]() {
        RT_HARD_ASSERT( mFake );
        return mFake->getClockFrequency();
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

      if ( !isStoredDriver )
      {
        return false;
      }

      /*-------------------------------------------------
      Next validate that the driver has been initialized
      and can have methods invoked on mock/fake classes.
      -------------------------------------------------*/
      std::lock_guard<std::recursive_mutex> lk( s_devices[ idx ].lock );

      return ( s_devices[ idx ].realDriver && s_devices[ idx ].virtualDriver &&
               ( s_devices[ idx ].resourceIndex < SIM::NUM_DRIVERS ) );
    }


    bool isSupported( const Chimera::SPI::Channel channel )
    {
      return ( static_cast<size_t>( channel ) < NUM_DRIVERS );
    }


    size_t getResourceIndex( const Chimera::SPI::Channel channel )
    {
      auto retVal = Chimera::SIM::INVALID_RESOURCE_INDEX;

      /*-------------------------------------------------
      Boundary check against the project's description
      -------------------------------------------------*/
      if ( !isSupported( channel ) )
      {
        return retVal;
      }

      /*-------------------------------------------------
      Sim should support every possible SPI channel
      -------------------------------------------------*/
      static_assert( NUM_DRIVERS == static_cast<size_t>( Chimera::SPI::Channel::NUM_OPTIONS ) );
      return static_cast<size_t>( channel );
    }
  }    // namespace SIM
}    // namespace Chimera::SPI

#endif /* CHIMERA_SIMULATOR */
