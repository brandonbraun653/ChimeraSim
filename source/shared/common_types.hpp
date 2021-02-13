/********************************************************************************
 *  File Name:
 *    common_types.hpp
 *
 *  Description:
 *    Shared information among the whole project
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_SHARED_DATA_HPP
#define CHIMERA_SIM_SHARED_DATA_HPP

/* STL Includes */
#include <cstddef>
#include <limits>

namespace Chimera::SIM
{
  static constexpr size_t INVALID_RESOURCE_INDEX = std::numeric_limits<size_t>::max();
}  // namespace Chimera::SIM

#endif  /* !CHIMERA_SIM_SHARED_DATA_HPP */
