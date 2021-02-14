/********************************************************************************
 *  File Name:
 *    sim_spi_types.hpp
 *
 *  Description:
 *    Configuration options and types for the sim driver
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_SPI_DETAIL_HPP
#define CHIMERA_SIM_SPI_DETAIL_HPP

/* STL Includes */
#include <cstddef>
#include <mutex>

/* Chimera Includes */
#include <Chimera/spi>

/* Simulator Includes */
#include <ChimeraSim/source/shared/common_types.hpp>

namespace Chimera::SPI::SIM
{
  /*-------------------------------------------------------------------------------
  Forward Declarations
  -------------------------------------------------------------------------------*/
  class MockSPI;
  class BasicSPI;

  /*-------------------------------------------------------------------------------
  Aliases
  -------------------------------------------------------------------------------*/
  using SPIDevice = Chimera::SIM::VirtualDevice<BasicSPI, MockSPI, Driver_rPtr>;

  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t NUM_DRIVERS = static_cast<size_t>( Chimera::SPI::Channel::NUM_OPTIONS );

  /*-------------------------------------------------------------------------------
  Structures
  -------------------------------------------------------------------------------*/
  /**
   *  Tracks the simulated state of the virtual device
   */
  struct VirtualState
  {
    std::recursive_timed_mutex mtx; /**< Driver lock */
    DriverConfig config;            /**< SPI configuration */
    size_t clockFrequency;          /**< Current clock speed */
    Chimera::Hardware::PeripheralMode periphMode;
  };

}  // namespace Chimera::SPI::SIM

#endif  /* !CHIMERA_SIM_SPI_DETAIL_HPP */
