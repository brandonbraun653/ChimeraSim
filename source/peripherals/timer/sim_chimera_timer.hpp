/********************************************************************************
 *  File Name:
 *    sim_chimera_timer.hpp
 *
 *  Description:
 *    Simulator variant of the core chimera functionality.
 *
 *  2019-2025 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#pragma once
#ifndef SIM_CHIMERA_HPP
#define SIM_CHIMERA_HPP

#if defined( CHIMERA_SIMULATOR )

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <cstdlib>
#include <Chimera/common>

namespace Chimera::Timer::Sim
{
  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  /**
   * @brief Initializes the timer system for the simulator
   * @return Chimera::Status_t
   */
  Chimera::Status_t initialize();

  /**
   * @brief Resets the timer system to its initial state
   * @return Chimera::Status_t
   */
  Chimera::Status_t reset();

  /**
   *	Returns the number of milliseconds that have elapsed since the beginning
   *  of the program.
   *
   *  When external time source is active, returns the external time in milliseconds.
   *  When using realtime (default), returns the actual elapsed time since program start.
   *
   *  @warning  Must call ChimeraInit() in order for this function to work
   *  @note     May not be exactly 1mS period as this is OS dependent
   *
   *	@return size_t
   */
  size_t millis();

  /**
   * @brief Returns the number of microseconds that have elapsed since the beginning
   * of the program.
   *
   * When external time source is active, returns the external time (baseline + offset).
   * When using realtime (default), returns the actual elapsed time since program start.
   *
   * @return size_t
   */
  size_t micros();

  /**
   *  Delays (blocks) the current thread execution for a number of milliseconds
   *
   *  @note     May not be exact delays as this is OS dependent
   *
   *	@param[in]	val   Milliseconds to block the thread
   *	@return void
   */
  void delayMilliseconds( const size_t val );

  /**
   *  Delays (blocks) the current thread execution for a number of microseconds
   *
   *  When external time source is active, the delay blocks until the external time advances
   *  by the specified amount. When using realtime (default), this blocks for approximately
   *  the specified duration using system sleep functions.
   *
   *  @note     May not be exact delays as this is OS dependent
   *
   *	@param[in]	val   Microseconds to delay (external time advance when external source active)
   *	@return void
   */
  void delayMicroseconds( const size_t val );

  /**
   * @brief Enables external time source control with an initial offset
   *
   * When enabled, the timer captures the current internal time as a baseline and uses the provided
   * offset to calculate external time. External time is computed as: baseline + offset.
   *
   * @param sim_time_us Initial time offset from the captured baseline (microseconds)
   */
  void enableExternalTimeSource( size_t sim_time_us );

  /**
   * @brief Updates the external time source with a new offset
   *
   * The offset must be monotonically increasing. If the new offset is less than or equal to
   * the current offset, the update is ignored. External time advances as: baseline + new_offset.
   *
   * @param sim_time_us New time offset from the baseline (microseconds, must be >= current offset)
   * @return true if the update was successful, false otherwise
   */
  bool updateExternalTime( size_t sim_time_us );

  /**
   * @brief Disables the external time source and reverts to realtime execution
   *
   * Resumes normal realtime operation, adjusting the internal clock to maintain
   * monotonic time continuity (realtime = current_wall_time - (baseline + last_offset)).
   */
  void disableExternalTimeSource();

  /**
   * @brief Indicates if the external time source is currently active
   */
  bool isExternalTimeSourceActive();

}    // namespace Chimera::Timer::Sim

#endif /* CHIMERA_SIMULATOR */
#endif /* SIM_CHIMERA_HPP */
