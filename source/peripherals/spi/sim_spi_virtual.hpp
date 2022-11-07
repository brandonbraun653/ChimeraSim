/********************************************************************************
 *  File Name:
 *    sim_spi_virtual.hpp
 *
 *  Description:
 *    Mocks the SPI interface and creates a virtual device
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_SPI_MOCK_HPP
#define CHIMERA_SIM_SPI_MOCK_HPP

/* STL Includes */
#include <mutex>

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/spi>

/* Google Includes */
#include <gmock/gmock.h>

/* Simulator Includes */
#include <ChimeraSim/source/controller/ctrl_types.hpp>
#include <ChimeraSim/source/peripherals/spi/sim_spi_types.hpp>
#include <ChimeraSim/source/transport/master_slave.hpp>

namespace Chimera::SPI::SIM
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Sets the backend driver style in use for the given peripheral index
   *
   *  @param[in]  type      Driver type to register
   *  @param[in]  idx       Resource index for the peripheral to set
   *  @return Chimera::Status_t
   */
  Chimera::Status_t setDriverType( const Chimera::SIM::Driver_t type, const size_t idx );

  /*-------------------------------------------------------------------------------
  Core object used to virtualize the driver for sim and test environments
  -------------------------------------------------------------------------------*/
  class MockSPI : public ISPI
  {
  public:
    MOCK_METHOD( Chimera::Status_t, init, ( const Chimera::SPI::DriverConfig & ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, deInit, (), ( override ) );
    MOCK_METHOD( Chimera::Status_t, assignChipSelect, ( const Chimera::GPIO::Driver_rPtr ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, setChipSelect, ( const Chimera::GPIO::State ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, setChipSelectControlMode, ( const Chimera::SPI::CSMode ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, writeBytes, ( const void *const, const size_t ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, readBytes, ( void *const, const size_t ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, readWriteBytes, ( const void *const, void *const, const size_t ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, setPeripheralMode, ( const Chimera::Hardware::PeripheralMode ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, setClockFrequency, ( const size_t, const size_t ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, await, ( const Chimera::Event::Trigger, const size_t ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, await, ( const Chimera::Event::Trigger, Chimera::Thread::BinarySemaphore &, const size_t ), ( override ) );
    MOCK_METHOD( Chimera::SPI::HardwareInit, getInit, (), ( override ) );
    MOCK_METHOD( size_t, getClockFrequency, (), ( override ) );
    MOCK_METHOD( void, lock, (), ( override ) );
    MOCK_METHOD( void, lockFromISR, (), ( override ) );
    MOCK_METHOD( bool, try_lock_for, ( const size_t ), ( override ) );
    MOCK_METHOD( void, unlock, (), ( override ) );
    MOCK_METHOD( void, unlockFromISR, (), ( override ) );

    /**
     *  Instructs the mock object to delegate mocked calls into a fake implementation
     *  provided by the user. This will serve as the default behavior if no other
     *  ON_CALL statements are applied to the mock.
     *
     *  @param[in]  fake      The fake driver to inject
     *  @return void
     */
    void DelegateToFake( ISPI *const fake );

  private:
    ISPI *mFake;
  };

  /*-------------------------------------------------------------------------------
  Default delegate that mimics a working driver with no fancy add-ons
  -------------------------------------------------------------------------------*/
  class BasicSPI : public ISPI
  {
  public:
    virtual Chimera::Status_t init( const Chimera::SPI::DriverConfig &setupStruct ) override;
    virtual Chimera::Status_t deInit() override;
    virtual Chimera::Status_t assignChipSelect( const Chimera::GPIO::Driver_rPtr cs ) override;
    virtual Chimera::Status_t setChipSelect( const Chimera::GPIO::State value ) override;
    virtual Chimera::Status_t setChipSelectControlMode( const Chimera::SPI::CSMode mode ) override;
    virtual Chimera::Status_t writeBytes( const void *const txBuffer, const size_t length ) override;
    virtual Chimera::Status_t readBytes( void *const rxBuffer, const size_t length ) override;
    virtual Chimera::Status_t readWriteBytes( const void *const txBuffer, void *const rxBuffer, const size_t length ) override;
    virtual Chimera::Status_t setPeripheralMode( const Chimera::Hardware::PeripheralMode mode ) override;
    virtual Chimera::Status_t setClockFrequency( const size_t freq, const size_t tolerance ) override;
    virtual Chimera::SPI::HardwareInit getInit() override;
    virtual size_t getClockFrequency() override;
    virtual Chimera::Status_t await( const Chimera::Event::Trigger event, const size_t timeout ) override;
    virtual Chimera::Status_t await( const Chimera::Event::Trigger event, Chimera::Thread::BinarySemaphore &notifier,
                             const size_t timeout ) override;
    virtual void lock() override;
    virtual void lockFromISR() override;
    virtual bool try_lock_for( const size_t timeout ) override;
    virtual void unlock() override;
    virtual void unlockFromISR() override;

  protected:
    VirtualState mHWState;
  };

  /*-------------------------------------------------------------------------------
  Delegate that exposes a network connection to for communication
  -------------------------------------------------------------------------------*/
  class NetworkedSPI : public BasicSPI, public Chimera::SIM::Transport::SynchMasterSlave
  {
  public:
    Chimera::Status_t init( const Chimera::SPI::DriverConfig &setupStruct ) final override;
    Chimera::Status_t readWriteBytes( const void *const txBuffer, void *const rxBuffer, const size_t length ) final override;
  };
}  // namespace Chimera::SPI::SIM

#endif  /* !CHIMERA_SIM_SPI_MOCK_HPP */
