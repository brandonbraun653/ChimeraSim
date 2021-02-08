/********************************************************************************
 *  File Name:
 *    sim_chimera_gpio.cpp
 *
 *  Description:
 *    GPIO Simulator
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/gpio>


namespace Chimera::GPIO
{
  /*-------------------------------------------------------------------------------
  Driver Implementation
  -------------------------------------------------------------------------------*/
  Driver::Driver() : mDriver( nullptr )
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
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::init( const Chimera::GPIO::Port port, const uint8_t pin )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::setMode( const Chimera::GPIO::Drive drive, const Chimera::GPIO::Pull pull )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::setState( const Chimera::GPIO::State state )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::getState( Chimera::GPIO::State &state )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::toggle()
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Chimera::Status_t Driver::attachInterrupt( Chimera::Function::vGeneric &func, const Chimera::EXTI::EdgeTrigger trigger )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  void Driver::detachInterrupt()
  {
  }


  Chimera::EXTI::EventLine_t Driver::getInterruptLine()
  {
    return 0;
  }

  /*-------------------------------------------------
  Interface: Lockable
  -------------------------------------------------*/
  void Driver::lock()
  {
  }


  void Driver::lockFromISR()
  {
  }


  bool Driver::try_lock_for( const size_t timeout )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  void Driver::unlock()
  {
  }


  void Driver::unlockFromISR()
  {
  }

  /*-------------------------------------------------------------------------------
  Backend Driver Registry
  -------------------------------------------------------------------------------*/
  namespace Backend
  {
    Chimera::Status_t initialize()
    {
      return Chimera::Status::NOT_SUPPORTED;
    }


    Chimera::Status_t reset()
    {
      return Chimera::Status::NOT_SUPPORTED;
    }


    Chimera::GPIO::Driver_rPtr getDriver( const Port port, const Pin pin )
    {
      return nullptr;
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

  /*-------------------------------------------------------------------------------
  Simulator Implementation Details
  -------------------------------------------------------------------------------*/
  namespace Sim
  {
  }
}    // namespace Chimera::GPIO


#endif /* CHIMERA_SIMULATOR */
