/********************************************************************************
 *  File Name:
 *    sim_chimera_adc.cpp
 *
 *  Description:
 *    adc Simulator
 *
 *  2020-2022 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Aurora/utility>
#include <Chimera/common>
#include <Chimera/adc>
#include <Chimera/peripheral>

namespace Chimera::ADC
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static DeviceManager<Driver, Peripheral, EnumValue( Peripheral::NUM_OPTIONS )> s_raw_driver;

  /*---------------------------------------------------------------------------
  Static Functions
  ---------------------------------------------------------------------------*/
  static Chimera::Status_t impl_initialize()
  {
    return Chimera::Status::OK;
  }


  static Chimera::Status_t impl_reset()
  {
    return Chimera::Status::OK;
  }


  static Driver_rPtr impl_getDriver( const Chimera::ADC::Peripheral periph )
  {
    return s_raw_driver.getOrCreate( periph );
  }


  static bool impl_featureSupported( const Chimera::ADC::Peripheral periph, const Chimera::ADC::Feature feature )
  {
    return true;
  }


  namespace Backend
  {
    Chimera::Status_t registerDriver( Chimera::ADC::Backend::DriverConfig &registry )
    {
      registry.isSupported      = true;
      registry.getDriver        = ::Chimera::ADC::impl_getDriver;
      registry.initialize       = ::Chimera::ADC::impl_initialize;
      registry.reset            = ::Chimera::ADC::impl_reset;
      registry.featureSupported = ::Chimera::ADC::impl_featureSupported;
      return Chimera::Status::OK;
    }
  }    // namespace Backend


  /*---------------------------------------------------------------------------
  Driver Implementation
  ---------------------------------------------------------------------------*/
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


  size_t Driver::getSampleCycle( const Chimera::ADC::Channel ch )
  {
    return 0;
  }


  size_t Driver::totalMeasureTime( const size_t cycles )
  {
    return 0;
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


  bool Driver::nextSeqSample( const Channel ch, Sample &sample )
  {
    return true;
  }


  size_t Driver::multiSeqSample( const Channel *ch_arr, Sample *sample_arr, const size_t size )
  {
    return 0;
  }


  void Driver::onInterrupt( const Chimera::ADC::Interrupt bmSignal, Chimera::ADC::ISRCallback cb )
  {
  }


  float Driver::toVoltage( const Chimera::ADC::Sample &sample )
  {
    return 0.0f;
  }


  Chimera::Status_t Driver::monitorChannel( const WatchdogConfig &cfg )
  {
    return Chimera::Status::OK;
  }


  float Driver::analogReference() const
  {
    return 0.0f;
  }
}    // namespace Chimera::ADC

#endif /* CHIMERA_SIMULATOR */
