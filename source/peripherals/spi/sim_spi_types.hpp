/********************************************************************************
 *  File Name:
 *    sim_spi_types.hpp
 *
 *  Description:
 *    Configuration options and types for the sim driver
 *
 *  2021-2025 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_SPI_DETAIL_HPP
#define CHIMERA_SIM_SPI_DETAIL_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <cstddef>
#include <Chimera/spi>

namespace Chimera::SPI::Sim
{
  /*---------------------------------------------------------------------------
  Constants
  ---------------------------------------------------------------------------*/
  static constexpr size_t NUM_DRIVERS = static_cast<size_t>( Chimera::SPI::Channel::NUM_OPTIONS );

}    // namespace Chimera::SPI::Sim

#endif /* !CHIMERA_SIM_SPI_DETAIL_HPP */
