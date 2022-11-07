/******************************************************************************
 *  File Name:
 *    sim_timer_pwm_intf.cpp
 *
 *  Description:
 *    ChimeraStubs
 *
 *  2022 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/timer>

namespace Chimera::Timer::PWM
{
  Driver::Driver()
  {
  }


  Driver::~Driver()
  {
  }


  Chimera::Status_t Driver::init( const DriverConfig &cfg )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::enableOutput()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::disableOutput()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setFrequency( const float freq )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setDutyCycle( const float dutyCycle )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setPolarity( const Chimera::Timer::PWM::Polarity polarity )
  {
    return Chimera::Status::OK;
  }

}    // namespace Chimera::Timer::PWM
