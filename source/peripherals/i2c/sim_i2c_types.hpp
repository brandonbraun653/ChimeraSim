/******************************************************************************
 *  File Name:
 *    sim_i2c_types.hpp
 *
 *  Description:
 *    Specifies configuration characteristics of the sim driver
 *
 *  2022 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_I2C_DETAIL_HPP
#define CHIMERA_SIM_I2C_DETAIL_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/i2c>
#include <cstddef>

namespace Chimera::I2C::Sim
{
  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  /**
   *  Basic I2C implementation that mimics a working driver with no fancy add-ons
   */
  class BasicI2C : public Chimera::I2C::II2C
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

  /*---------------------------------------------------------------------------
  Constants
  ---------------------------------------------------------------------------*/
  static constexpr size_t NUM_DRIVERS = 4;

}    // namespace Chimera::I2C::Sim

#endif /* !CHIMERA_SIM_I2C_DETAIL_HPP */
