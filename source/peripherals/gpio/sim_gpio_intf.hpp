/********************************************************************************
 *  File Name:
 *    sim_gpio_intf.hpp
 *
 *  Description:
 *    GPIO simulator interface
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_GPIO_INTERFACE_HPP
#define CHIMERA_SIM_GPIO_INTERFACE_HPP

/* STL Includes */
#include <cstddef>

/* Chimera Includes */
#include <Chimera/gpio>

namespace Chimera::GPIO::SIM
{
  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
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
   *  @param[in]  port        The GPIO port to grab
   *  @param[in]  pin         Which pin on the given port
   *  @return bool
   */
  bool isSupported( const Chimera::GPIO::Port port, const Chimera::GPIO::Pin pin );

  /**
   *  Gets the resource index associated with a particular port/pin combination.
   *  If not supported, will return INVALID_RESOURCE_INDEX.
   *
   *  This function adds additional checks to ensure that the exact combination
   *  exists in hardware. The resource index returned access the peripheral driver
   *  for the given hardware pin. Multiple indexes can correspond with a single
   *  peripheral instance in hardware.
   *
   *  @param[in]  port        The GPIO port to grab
   *  @param[in]  pin         Which pin on the given port, ranged from [0, DRIVER_MAX_PINS_PER_PORT]
   *  @return size_t
   */
  size_t getPinResourceIndex( const Chimera::GPIO::Port port, const Chimera::GPIO::Pin pin );

}  // namespace Chimera::GPIO::SIM

#endif  /* !CHIMERA_SIM_GPIO_INTERFACE_HPP */
