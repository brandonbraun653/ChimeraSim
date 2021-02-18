/********************************************************************************
 *  File Name:
 *    ctrl_types.hpp
 *
 *  Description:
 *    Sim controller types
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_CONTROLLER_TYPES_HPP
#define CHIMERA_SIM_CONTROLLER_TYPES_HPP

/* STL Includes */
#include <cstdint>

/* Chimera Includes */
#include <Chimera/common>

namespace Chimera::SIM
{
  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  enum class Driver_t : uint8_t
  {
    BASIC_STUB,        /**< Simulates a working driver, but without much functionality */
    NETWORKED_CONTROL, /**< Driver has network ports exposed for data injection */

    NUM_OPTIONS,
    INVALID
  };

  /*-------------------------------------------------------------------------------
  Aliases
  -------------------------------------------------------------------------------*/
  using AdjustDriverFunc_t = Chimera::Status_t ( * )( const Chimera::SIM::Driver_t, const size_t );

}    // namespace Chimera::SIM

#endif /* !CHIMERA_SIM_CONTROLLER_TYPES_HPP */
