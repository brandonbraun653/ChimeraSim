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
#include <mutex>

namespace Chimera::SIM
{
  /*---------------------------------------------------------------------------
  Constants
  ---------------------------------------------------------------------------*/
  static constexpr size_t INVALID_RESOURCE_INDEX = std::numeric_limits<size_t>::max();

  /*---------------------------------------------------------------------------
  Structures
  ---------------------------------------------------------------------------*/
  /**
   *  Generic device descriptor for a virtual peripheral
   *
   *  @class Default_t: Default driver behavior class type
   *  @class Network_t: Driver that exposes communication channels via network ports
   *  @class Mock_t:    Mock object used for testing purposes
   *  @type RealPtr_t:  Pointer to the real Chimera driver instance type
   */
  template<class Default_t, class Mock_t, class Network_t, typename RealPtr_t>
  struct VirtualDevice
  {
    std::recursive_mutex lock;  /**< Simulator access protection */
    Default_t *defaultDriver;   /**< Default behavior driver */
    Network_t *networkedDriver; /**< Network driver variant */
    Mock_t *virtualDriver;      /**< Runtime device implementation */
    RealPtr_t realDriver;       /**< Real driver Chimera hooks into */
    size_t resourceIndex;       /**< Expected resource index associated with the driver */
    bool initialized;

    VirtualDevice() :
        defaultDriver( nullptr ), virtualDriver( nullptr ), realDriver( nullptr ),
        resourceIndex( Chimera::SIM::INVALID_RESOURCE_INDEX ), initialized( false )
    {
    }
  };
}    // namespace Chimera::SIM

#endif /* !CHIMERA_SIM_SHARED_DATA_HPP */
