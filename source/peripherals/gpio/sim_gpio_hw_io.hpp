/********************************************************************************
 *  File Name:
 *    sim_gpio_hw_io.hpp
 *
 *  Description:
 *    GPIO simulator device driver that can inject/read hardware conditions onto
 *    the virtual GPIO pin.
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_GPIO_HW_IO_DRIVER_HPP
#define CHIMERA_SIM_GPIO_HW_IO_DRIVER_HPP

/* Simulator Includes */
#include <ChimeraSim/source/peripherals/gpio/sim_gpio_mock.hpp>

/* Chimera Includes */
#include <Chimera/gpio>

namespace Chimera::GPIO::SIM
{

  // Rename to something more like...BenchControl...and inherit from the dispatch class
  class RemoteControl : public MockBaseGPIO
  {
  public:

    void applyVoltageToPin( const float voltage, const Chimera::GPIO::Pin pin );
  };
}  // namespace Chimera::GPIO::SIM

#endif  /* !CHIMERA_SIM_GPIO_HW_IO_DRIVER_HPP */
