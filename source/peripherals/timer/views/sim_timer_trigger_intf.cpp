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

}    // namespace Chimera::Timer::Trigger
