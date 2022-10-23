/******************************************************************************
 *  File Name:
 *    sim_i2c_basic.cpp
 *
 *  Description:
 *    Virtual I2C implementations
 *
 *  2022 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/assert>
#include <Chimera/i2c>
#include <ChimeraSim/i2c>

namespace Chimera::I2C::SIM
{
  Chimera::Status_t BasicI2C::open( const DriverConfig &cfg )
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicI2C::close()
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicI2C::stop()
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicI2C::start()
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicI2C::read( const uint16_t address, void *const data, const size_t length )
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicI2C::write( const uint16_t address, const void *const data, const size_t length )
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicI2C::transfer( const uint16_t address, const void *const tx_data, void *const rx_data,
                                        const size_t length )
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicI2C::await( const Chimera::Event::Trigger event, const size_t timeout )
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicI2C::await( const Chimera::Event::Trigger event, Chimera::Thread::BinarySemaphore &notifier,
                                     const size_t timeout )
  {
    return Chimera::Status::OK;
  }

  void BasicI2C::lock()
  {
  }

  void BasicI2C::lockFromISR()
  {
  }

  bool BasicI2C::try_lock_for( const size_t timeout )
  {
    return true;
  }

  void BasicI2C::unlock()
  {
  }

  void BasicI2C::unlockFromISR()
  {
  }

}    // namespace Chimera::I2C::SIM
