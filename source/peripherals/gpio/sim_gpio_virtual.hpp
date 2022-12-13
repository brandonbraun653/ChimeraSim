/********************************************************************************
 *  File Name:
 *    sim_gpio_virtual.hpp
 *
 *  Description:
 *    Mocks the GPIO interface and creates a virtual device
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_GPIO_MOCK_HPP
#define CHIMERA_SIM_GPIO_MOCK_HPP

/* STL Includes */
#include <mutex>

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/gpio>

/* Google Includes */
#include <gmock/gmock.h>

/* Simulator Includes */
#include <ChimeraSim/source/peripherals/gpio/sim_gpio_types.hpp>


namespace Chimera::GPIO::SIM
{
  /*---------------------------------------------------------------------------
  Core object used to virtualize the GPIO driver for sim and test environments
  ---------------------------------------------------------------------------*/
  class MockGPIO : public IGPIO
  {
  public:
    MOCK_METHOD( Chimera::Status_t, init, ( const Chimera::GPIO::PinInit & ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, init, ( const Chimera::GPIO::Port, const uint8_t ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, setMode, ( const Chimera::GPIO::Drive, const Chimera::GPIO::Pull ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, setState, ( const Chimera::GPIO::State ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, getState, ( Chimera::GPIO::State & ), ( override ) );
    MOCK_METHOD( Chimera::Status_t, toggle, (), ( override ) );
    MOCK_METHOD( Chimera::Status_t, attachInterrupt, ( Chimera::Function::vGeneric &, const Chimera::EXTI::EdgeTrigger ),
                 ( override ) );
    MOCK_METHOD( void, detachInterrupt, (), ( override ) );
    MOCK_METHOD( Chimera::EXTI::EventLine_t, getInterruptLine, (), ( override ) );
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
    void DelegateToFake( IGPIO *const fake );

  private:
    IGPIO *mFake;
  };


  /*---------------------------------------------------------------------------
  Default GPIO delegate that mimics a working driver with no fancy add-ons
  ---------------------------------------------------------------------------*/
  class BasicGPIO : public IGPIO
  {
  public:
    virtual Chimera::Status_t init( const Chimera::GPIO::PinInit &pinInit ) override;
    virtual Chimera::Status_t init( const Chimera::GPIO::Port port, const uint8_t pin ) override;
    virtual Chimera::Status_t setMode( const Chimera::GPIO::Drive drive, const Chimera::GPIO::Pull pull ) override;
    virtual Chimera::Status_t setState( const Chimera::GPIO::State state ) override;
    virtual Chimera::Status_t getState( Chimera::GPIO::State &state ) override;
    virtual Chimera::Status_t toggle();
    virtual Chimera::Status_t attachInterrupt( Chimera::Function::vGeneric &func,
                                               const Chimera::EXTI::EdgeTrigger trigger ) override;
    virtual void detachInterrupt() override;
    virtual Chimera::EXTI::EventLine_t getInterruptLine() override;
    virtual void lock() override;
    virtual void lockFromISR() override;
    virtual bool try_lock_for( const size_t timeout ) override;
    virtual void unlock() override;
    virtual void unlockFromISR() override;

  protected:
    VirtualState mHWState;
  };

  /*---------------------------------------------------------------------------
  Alternate GPIO delegate capable of remote control and fault injection
  ---------------------------------------------------------------------------*/
  class ControlledGPIO : virtual public BasicGPIO
  {
  public:
  };

}    // namespace Chimera::GPIO::SIM

#endif /* !CHIMERA_SIM_GPIO_MOCK_HPP */
