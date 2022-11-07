/******************************************************************************
 *  File Name:
 *    sim_timer_base_intf.cpp
 *
 *  Description:
 *    Stubs for ChimeraSim
 *
 *  2022 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/timer>

namespace Chimera::Timer
{
  Chimera::Status_t Core::initCore( const CoreConfig &cfg )
  {
    return Chimera::Status::OK;
  }


  void Core::startCounter()
  {
  }


  void Core::stopCounter()
  {
  }

}    // namespace Chimera::Timer
