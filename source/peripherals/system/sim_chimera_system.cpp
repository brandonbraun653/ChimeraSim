/********************************************************************************
 *  File Name:
 *    sim_chimera_system.cpp
 *
 *  Description:
 *    Simulates Chimera system functionality
 *
 *  2019 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* STL Includes */
#include <atomic>
#include <cstdint>
#include <chrono>
#include <thread>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/system>

/* Global system tick counter */
static std::atomic<size_t> sSysTick = 0;

/**
 *	Thread that updates the Chimera millisecond timer counter
 *	@return void
 */
static void SimSystemTick();
static std::thread sSysTickThread;

namespace Chimera::System
{
  Chimera::Status_t prjSystemStartup()
  {
    sSysTick       = 0;
    //sSysTickThread = std::thread( SimSystemTick );

    return Chimera::Status::OK;
  }

  InterruptMask prjDisableInterrupts()
  {
    return {};
  }

  void prjEnableInterrupts( InterruptMask &interruptMask )
  {
    //
  }

  int prjMaxConcurrentThreads()
  {
    return -1;
  }

  size_t getSystemTick()
  {
    /*------------------------------------------------
    Last known value of the system millisecond timer. Intentionally
    using an async thread to update the tick count to reflect how
    FreeRTOS updates their system tick counter. Most of my systems
    at the moment are Embedded FreeRTOS based, so it makes some sense.
    ------------------------------------------------*/
    return sSysTick;
  }
}  // namespace Chimera::System


namespace Chimera::System::Backend
{
  Chimera::Status_t registerDriver( struct Chimera::System::Backend::DriverConfig &cfg )
  {
    cfg.isSupported            = true;
    cfg.desc_About             = nullptr;
    cfg.desc_BackendDriverName = nullptr;
    cfg.desc_DocumentationLink = nullptr;
    cfg.disableInterrupts      = prjDisableInterrupts;
    cfg.enableInterrupts       = prjEnableInterrupts;
    cfg.getResetReason         = nullptr;
    cfg.getSystemInformation   = nullptr;
    cfg.initialize             = nullptr;
    cfg.maxConcurrentThreads   = prjMaxConcurrentThreads;
    cfg.reset                  = nullptr;
    cfg.systemStartup          = prjSystemStartup;
    cfg.version_AsString       = nullptr;
    cfg.version_Major          = nullptr;
    cfg.version_Minor          = nullptr;
    cfg.version_Patch          = nullptr;

    return Chimera::Status::OK;
  }
}


static void SimSystemTick()
{
  using namespace std::chrono;

  /*------------------------------------------------
  Initialize the timer
  ------------------------------------------------*/
  const size_t tickStart = duration_cast<milliseconds>( system_clock::now().time_since_epoch() ).count();
  size_t currentTick = tickStart;
  sSysTick = 0;

  /*------------------------------------------------
  As long as the program is executing, this thread cannot quit.
  Unfortunately that also means the system tick can't quit either, so debugging
  timing issues while using breakpoints are going to be a pain in the butt.
  ------------------------------------------------*/
  while ( true )
  {
    currentTick = duration_cast<milliseconds>( system_clock::now().time_since_epoch() ).count();
    sSysTick = currentTick - tickStart;

    // I can't really guarantee that this will sleep for this amount of time...
    std::this_thread::sleep_for( std::chrono::microseconds( 1000 ) );
  }
}


#endif /* _WIN32 || _WIN64 */
