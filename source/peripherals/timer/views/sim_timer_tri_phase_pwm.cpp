/******************************************************************************
 *  File Name:
 *    sim_timer_tri_phase_pwm.cpp
 *
 *  Description:
 *    ChimeraSim Stubs
 *
 *  2022 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/timer>

namespace Chimera::Timer::Inverter
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


  Chimera::Status_t Driver::setCarrierFrequency( const float freq )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setPhaseDutyCycle( const float a, const float b, const float c )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setForwardCommState( const uint8_t phase )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::emergencyBreak()
  {
    return Chimera::Status::OK;
  }

}    // namespace Chimera::Timer::Inverter
