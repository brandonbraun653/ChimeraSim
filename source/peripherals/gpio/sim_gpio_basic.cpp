/********************************************************************************
 *  File Name:
 *    sim_gpio_basic.cpp
 *
 *  Description:
 *    Virtual GPIO implementations
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/gpio>

/* Simulator Includes */
#include <ChimeraSim/gpio>
#include <ChimeraSim/source/peripherals/gpio/sim_gpio_virtual.hpp>

namespace Chimera::GPIO::SIM
{
  /*-------------------------------------------------------------------------------
  Basic GPIO Implementation
  -------------------------------------------------------------------------------*/
  Chimera::Status_t BasicGPIO::init( const Chimera::GPIO::PinInit &pinInit )
  {
    mHWState.config = pinInit;
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicGPIO::init( const Chimera::GPIO::Port port, const uint8_t pin )
  {
    mHWState.config.port = port;
    mHWState.config.pin  = pin;
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicGPIO::setMode( const Chimera::GPIO::Drive drive, const Chimera::GPIO::Pull pull )
  {
    mHWState.config.drive = drive;
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicGPIO::setState( const Chimera::GPIO::State state )
  {
    /*-------------------------------------------------
    Device must be an output if a state is to be set
    -------------------------------------------------*/
    if ( ( mHWState.config.drive < Drive::NUM_OPTIONS ) && ( mHWState.config.drive != Drive::HIZ ) &&
         ( mHWState.config.drive != Drive::INPUT ) )
    {
      mHWState.logicState = state;
      mHWState.voltage    = ( state == State::HIGH ) ? 3.3f : 0.0f;
      return Chimera::Status::OK;
    }
    else
    {
      return Chimera::Status::FAIL;
    }
  }

  Chimera::Status_t BasicGPIO::getState( Chimera::GPIO::State &state )
  {
    state = mHWState.logicState;
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicGPIO::toggle()
  {
    mHWState.logicState = ( mHWState.logicState == State::HIGH ) ? State::LOW : State::HIGH;
    return Chimera::Status::OK;
  }

  Chimera::Status_t BasicGPIO::attachInterrupt( Chimera::Function::vGeneric &func, const Chimera::EXTI::EdgeTrigger trigger )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }

  void BasicGPIO::detachInterrupt()
  {
  }

  Chimera::EXTI::EventLine_t BasicGPIO::getInterruptLine()
  {
    return 0;
  }

  void BasicGPIO::lock()
  {
    mHWState.mtx.lock();
  }

  void BasicGPIO::lockFromISR()
  {
    mHWState.mtx.lock();
  }

  bool BasicGPIO::try_lock_for( const size_t timeout )
  {
    return mHWState.mtx.try_lock_for( std::chrono::milliseconds( timeout ) );
  }

  void BasicGPIO::unlock()
  {
    mHWState.mtx.unlock();
  }

  void BasicGPIO::unlockFromISR()
  {
    mHWState.mtx.unlock();
  }

}    // namespace Chimera::GPIO::SIM
