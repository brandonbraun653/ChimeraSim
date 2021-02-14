/********************************************************************************
 *  File Name:
 *    sim_spi_intf.hpp
 *
 *  Description:
 *    SPI simulator interface
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_SPI_INTERFACE_HPP
#define CHIMERA_SIM_SPI_INTERFACE_HPP

/* STL Includes */
#include <cstddef>

/* Chimera Includes */
#include <Chimera/spi>

namespace Chimera::SPI::SIM
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Validates that a driver model actually has been initialized
   *
   *  @param[in]  driver      Opaque pointer to the driver control structure
   *  @return bool
   */
  bool validateDriver( void *const driver );

  /**
   *  Checks if the given hardware channel is supported on this device.
   *
   *  @param[in]  channel     Which channel to check
   *  @return bool
   */
  bool isSupported( const Chimera::SPI::Channel channel );

  /**
   *  Gets the resource index for the given channel
   *
   *  @param[in]  channel     Which channel to look up
   *  @return size_t
   */
  size_t getResourceIndex( const Chimera::SPI::Channel channel );

}  // namespace Chimera::SPI::SIM

#endif  /* !CHIMERA_SIM_SPI_INTERFACE_HPP */
