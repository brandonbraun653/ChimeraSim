/********************************************************************************
 *  File Name:
 *    ctrl_intf.hpp
 *
 *  Description:
 *    Simulator high level control interface
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_CONTROL_INTF_HPP
#define CHIMERA_SIM_CONTROL_INTF_HPP

/* Chimera Includes */
#include <Chimera/common>

/* Simulator Includes */
#include <ChimeraSim/source/controller/ctrl_types.hpp>

namespace Chimera::SIM
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Sets the peripheral driver implementation, but performs no setup.
   *
   *  @param[in]  periph      Which peripheral to set
   *  @param[in]  driver      Driver type to configure
   *  @return Chimera::Status_t
   */
  Chimera::Status_t setDriverType( const Chimera::Peripheral::Type periph, const Driver_t driver );

}  // namespace Chimera::SIM

#endif  /* !CHIMERA_SIM_CONTROL_INTF_HPP */
