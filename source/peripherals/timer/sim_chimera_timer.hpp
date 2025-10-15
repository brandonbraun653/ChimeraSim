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

namespace ChimeraSim::Timer
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
   *  @note     May not be exact delays as this is OS dependent
   *
   *	@param[in]	val   Microseconds to block the thread
   *	@return void
   */
  void delayMicroseconds( const size_t val );

  /**
   * @brief Enables an external time source and seeds it with the initial timestamp
   * @param sim_time_us Latest timestamp provided by the external simulator (microseconds)
   */
  void enableExternalTimeSource( size_t sim_time_us );

  /**
   * @brief Updates the external time source with a new timestamp (microseconds)
   * @param sim_time_us Latest timestamp provided by the external simulator (microseconds)
   */
  void updateExternalTime( size_t sim_time_us );

  /**
   * @brief Disables the external time source and reverts to realtime execution
   */
  void disableExternalTimeSource();

  /**
   * @brief Indicates if the external time source is currently active
   */
  bool isExternalTimeSourceActive();

}    // namespace ChimeraSim::Timer

#endif /* CHIMERA_SIMULATOR */
#endif /* SIM_CHIMERA_HPP */
