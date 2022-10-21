/********************************************************************************
 *  File Name:
 *    sim_chimera_adc.cpp
 *
 *  Description:
 *    adc Simulator
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/adc>

namespace Chimera::ADC
{
  /*-------------------------------------------------------------------------------
  Driver Implementation
  -------------------------------------------------------------------------------*/
  Driver::Driver()
  {
  }


  Driver::~Driver()
  {
  }


  Chimera::Status_t Driver::open( const Chimera::ADC::DriverConfig &cfg )
  {
    return Chimera::Status::OK;
  }


  void Driver::close()
  {
  }


  Chimera::Status_t Driver::setSampleTime( const Chimera::ADC::Channel ch, const size_t cycles )
  {
    return Chimera::Status::OK;
  }


  Chimera::ADC::Sample Driver::sampleChannel( const Chimera::ADC::Channel ch )
  {
    return {};
  }


  Chimera::Status_t Driver::configSequence( const Chimera::ADC::SequenceInit &cfg )
  {
    return Chimera::Status::OK;
  }


  void Driver::startSequence()
  {
  }


  void Driver::stopSequence()
  {
  }


  void Driver::onInterrupt( const Chimera::ADC::Interrupt bmSignal, Chimera::ADC::ISRCallback cb )
  {
  }

  float Driver::toVoltage( const Chimera::ADC::Sample &sample )
  {
    return 0.0f;
  }
}    // namespace Chimera::ADC

#endif /* CHIMERA_SIMULATOR */
