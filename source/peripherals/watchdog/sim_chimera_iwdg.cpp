/********************************************************************************
 *  File Name:
 *    sim_chimera_iwdg.cpp
 *
 *  Description:
 *    Independent watchdog simulator definition
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/watchdog>

namespace Chimera::Watchdog
{
  /*---------------------------------------------------------------------------
  Independent Driver Implementation
  ---------------------------------------------------------------------------*/
  IndependentDriver::IndependentDriver() : mDriver( nullptr )
  {
  }


  IndependentDriver::~IndependentDriver()
  {
  }


  /*-------------------------------------------------
  Interface: Hardware
  -------------------------------------------------*/
  Chimera::Status_t IndependentDriver::initialize( const IChannel ch, const uint32_t timeout_mS )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Status_t IndependentDriver::start()
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Status_t IndependentDriver::stop()
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Status_t IndependentDriver::kick()
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  Status_t IndependentDriver::pauseOnDebugHalt( const bool enable )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }

  size_t IndependentDriver::getTimeout()
  {
    return 0;
  }


  size_t IndependentDriver::maxTimeout()
  {
    return 0;
  }


  size_t IndependentDriver::minTimeout()
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  /*-------------------------------------------------
  Interface: Lockable
  -------------------------------------------------*/
  void IndependentDriver::lock()
  {
  }


  void IndependentDriver::lockFromISR()
  {
  }


  bool IndependentDriver::try_lock_for( const size_t timeout )
  {
    return Chimera::Status::NOT_SUPPORTED;
  }


  void IndependentDriver::unlock()
  {
  }


  void IndependentDriver::unlockFromISR()
  {
  }

}    // namespace Chimera::Watchdog

#endif /* CHIMERA_SIMULATOR */
