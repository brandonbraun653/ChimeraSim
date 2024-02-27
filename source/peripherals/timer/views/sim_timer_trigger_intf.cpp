/******************************************************************************
 *  File Name:
 *    sim_timer_trigger_intf.cpp
 *
 *  Description:
 *    ChimeraSim Stubs
 *
 *  2022-2024 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/timer>

namespace Chimera::Timer::Trigger
{
  /*---------------------------------------------------------------------------
  ITimerTrigger Interface
  ---------------------------------------------------------------------------*/
  ITimerTrigger::ITimerTrigger() : mTimerImpl( nullptr )
  {
  }


  ITimerTrigger::~ITimerTrigger()
  {
  }


  Chimera::Status_t ITimerTrigger::enable()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t ITimerTrigger::disable()
  {
    return Chimera::Status::OK;
  }


  void ITimerTrigger::detachISR()
  {
  }


  void ITimerTrigger::ackISR()
  {
  }


  /*---------------------------------------------------------------------------
  Master Implementation
  ---------------------------------------------------------------------------*/
  Master::Master()
  {
  }


  Master::~Master()
  {
  }


  Chimera::Status_t Master::init( const MasterConfig &cfg )
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t Master::attachISR( Chimera::Function::Opaque func )
  {
    return Chimera::Status::OK;
  }


  /*---------------------------------------------------------------------------
  Slave Implementation
  ---------------------------------------------------------------------------*/
  Slave::Slave()
  {
  }


  Slave::~Slave()
  {
  }


  Chimera::Status_t Slave::init( const SlaveConfig &cfg )
  {
    return Chimera::Status::OK;
  }


  uint32_t Slave::getTickPeriod() const
  {
    return 0;
  }


  void Slave::setEventOffset( const uint32_t tickOffset )
  {
  }


  Chimera::Status_t Slave::attachISR( Chimera::Function::Opaque func )
  {
    return Chimera::Status::OK;
  }
}    // namespace Chimera::Timer::Trigger
