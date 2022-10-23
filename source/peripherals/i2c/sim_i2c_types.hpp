/******************************************************************************
 *  File Name:
 *    sim_i2c_types.hpp
 *
 *  Description:
 *    Specifies configuration characteristics of the sim driver
 *
 *  2022 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_I2C_DETAIL_HPP
#define CHIMERA_SIM_I2C_DETAIL_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/i2c>
#include <ChimeraSim/source/shared/common_types.hpp>
#include <cstddef>

namespace Chimera::I2C::SIM
{
  /*---------------------------------------------------------------------------
  Forward Declarations
  ---------------------------------------------------------------------------*/
  class MockI2C;
  class BasicI2C;

  /*---------------------------------------------------------------------------
  Aliases
  ---------------------------------------------------------------------------*/
  using I2CDevice = Chimera::SIM::VirtualDevice<BasicI2C, MockI2C, void, Driver_rPtr>;

  /*---------------------------------------------------------------------------
  Constants
  ---------------------------------------------------------------------------*/
  static constexpr size_t NUM_DRIVERS = 4;

}  // namespace Chimera::I2C::SIM

#endif  /* !CHIMERA_SIM_I2C_DETAIL_HPP */
