/******************************************************************************
 *  File Name:
 *    sim_i2c_virtual.hpp
 *
 *  Description:
 *    Mocks the I2C interface and creates a virtual device
 *
 *  2022 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_I2C_MOCK_HPP
#define CHIMERA_SIM_I2C_MOCK_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/assert>
#include <Chimera/gpio>
#include <Chimera/thread>
#include <ChimeraSim/source/peripherals/i2c/sim_i2c_types.hpp>
#include <gmock/gmock.h>
#include <mutex>


namespace Chimera::I2C::SIM
{
  /*---------------------------------------------------------------------------
  Core object used to virtualize the I2C driver for sim and test environments
  ---------------------------------------------------------------------------*/
  class MockI2C : public II2C
  {
  public:
    MOCK_METHOD( Chimera::Status_t, open, ( const DriverConfig & ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, close, (), ( override ) );
    MOCK_METHOD( Chimera::Status_t, read, ( const uint16_t, void *const, const size_t ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, write, ( const uint16_t, const void *const, const size_t ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, transfer, ( const uint16_t, const void *const, void *const, const size_t ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, stop, (), ( override ) );
    MOCK_METHOD( Chimera::Status_t, start, (), ( override ) );
    MOCK_METHOD( Chimera::Status_t, await, ( const Chimera::Event::Trigger, const size_t ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, await, ( const Chimera::Event::Trigger, Chimera::Thread::BinarySemaphore &, const size_t ),
                 ( override ) );
    MOCK_METHOD( void, lock, (), ( override ) );
    MOCK_METHOD( void, lockFromISR, (), ( override ) );
    MOCK_METHOD( bool, try_lock_for, ( const size_t ), ( override ) );
    MOCK_METHOD( void, unlock, (), ( override ) );
    MOCK_METHOD( void, unlockFromISR, (), ( override ) );

  private:
    II2C *mFake;
  };

  /*-------------------------------------------------------------------------------
  Default delegate that mimics a working driver with no fancy add-ons
  -------------------------------------------------------------------------------*/
  class BasicI2C : public II2C
  {
  public:
    virtual Chimera::Status_t open( const DriverConfig &cfg ) override;
    virtual Chimera::Status_t close() override;
    virtual Chimera::Status_t stop() override;
    virtual Chimera::Status_t start() override;
    virtual Chimera::Status_t read( const uint16_t address, void *const data, const size_t length ) override;
    virtual Chimera::Status_t write( const uint16_t address, const void *const data, const size_t length ) override;
    virtual Chimera::Status_t transfer( const uint16_t address, const void *const tx_data, void *const rx_data,
                                        const size_t length ) override;
    virtual Chimera::Status_t await( const Chimera::Event::Trigger event, const size_t timeout ) override;
    virtual Chimera::Status_t await( const Chimera::Event::Trigger event, Chimera::Thread::BinarySemaphore &notifier,
                                     const size_t timeout ) override;
    virtual void lock() override;
    virtual void lockFromISR() override;
    virtual bool try_lock_for( const size_t timeout ) override;
    virtual void unlock() override;
    virtual void unlockFromISR() override;
  };
}    // namespace Chimera::I2C::SIM

#endif /* !CHIMERA_SIM_I2C_MOCK_HPP */
