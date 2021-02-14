/********************************************************************************
 *  File Name:
 *    sim_gpio_detail.hpp
 *
 *  Description:
 *    Specifies configuration characteristics of the sim driver
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_GPIO_DETAIL_HPP
#define CHIMERA_SIM_GPIO_DETAIL_HPP

/* STL Includes */
#include <cstddef>

/* Chimera Includes */
#include <Chimera/gpio>

/* Simulator Includes */
#include <ChimeraSim/source/shared/common_types.hpp>

namespace Chimera::GPIO::SIM
{
  /*-------------------------------------------------------------------------------
  Forward Declarations
  -------------------------------------------------------------------------------*/
  class MockGPIO;
  class BasicGPIO;

  /*-------------------------------------------------------------------------------
  Aliases
  -------------------------------------------------------------------------------*/
  using GPIODevice = Chimera::SIM::VirtualDevice<BasicGPIO, MockGPIO, Driver_rPtr>;

  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t NUM_PERIPHS         = 16;
  static constexpr size_t NUM_PINS_PER_PERIPH = 16;
  static constexpr size_t NUM_DRIVERS         = NUM_PERIPHS * NUM_PINS_PER_PERIPH;

  static constexpr size_t GPIOA_RESOURCE_INDEX = 0u;
  static constexpr size_t GPIOB_RESOURCE_INDEX = 1u;
  static constexpr size_t GPIOC_RESOURCE_INDEX = 2u;
  static constexpr size_t GPIOD_RESOURCE_INDEX = 3u;
  static constexpr size_t GPIOE_RESOURCE_INDEX = 4u;
  static constexpr size_t GPIOF_RESOURCE_INDEX = 5u;
  static constexpr size_t GPIOG_RESOURCE_INDEX = 6u;
  static constexpr size_t GPIOH_RESOURCE_INDEX = 7u;
  static constexpr size_t GPIOI_RESOURCE_INDEX = 8u;
  static constexpr size_t GPIOJ_RESOURCE_INDEX = 9u;
  static constexpr size_t GPIOK_RESOURCE_INDEX = 10u;
  static constexpr size_t GPIOL_RESOURCE_INDEX = 11u;
  static constexpr size_t GPIOM_RESOURCE_INDEX = 12u;
  static constexpr size_t GPION_RESOURCE_INDEX = 13u;
  static constexpr size_t GPIOO_RESOURCE_INDEX = 14u;
  static constexpr size_t GPIOP_RESOURCE_INDEX = 15u;

  static constexpr size_t GPIOA_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOB_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOC_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOD_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOE_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOF_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOG_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOH_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOI_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOJ_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOK_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOL_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOM_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPION_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOO_NUM_PINS = NUM_PINS_PER_PERIPH;
  static constexpr size_t GPIOP_NUM_PINS = NUM_PINS_PER_PERIPH;


  static constexpr size_t GPIOA_PIN_RINDEX_OFFSET = 0;
  static constexpr size_t GPIOB_PIN_RINDEX_OFFSET = GPIOA_PIN_RINDEX_OFFSET + GPIOA_NUM_PINS;
  static constexpr size_t GPIOC_PIN_RINDEX_OFFSET = GPIOB_PIN_RINDEX_OFFSET + GPIOB_NUM_PINS;
  static constexpr size_t GPIOD_PIN_RINDEX_OFFSET = GPIOC_PIN_RINDEX_OFFSET + GPIOC_NUM_PINS;
  static constexpr size_t GPIOE_PIN_RINDEX_OFFSET = GPIOD_PIN_RINDEX_OFFSET + GPIOD_NUM_PINS;
  static constexpr size_t GPIOF_PIN_RINDEX_OFFSET = GPIOE_PIN_RINDEX_OFFSET + GPIOE_NUM_PINS;
  static constexpr size_t GPIOG_PIN_RINDEX_OFFSET = GPIOF_PIN_RINDEX_OFFSET + GPIOF_NUM_PINS;
  static constexpr size_t GPIOH_PIN_RINDEX_OFFSET = GPIOG_PIN_RINDEX_OFFSET + GPIOG_NUM_PINS;
  static constexpr size_t GPIOI_PIN_RINDEX_OFFSET = GPIOH_PIN_RINDEX_OFFSET + GPIOH_NUM_PINS;
  static constexpr size_t GPIOJ_PIN_RINDEX_OFFSET = GPIOI_PIN_RINDEX_OFFSET + GPIOI_NUM_PINS;
  static constexpr size_t GPIOK_PIN_RINDEX_OFFSET = GPIOJ_PIN_RINDEX_OFFSET + GPIOJ_NUM_PINS;
  static constexpr size_t GPIOL_PIN_RINDEX_OFFSET = GPIOK_PIN_RINDEX_OFFSET + GPIOK_NUM_PINS;
  static constexpr size_t GPIOM_PIN_RINDEX_OFFSET = GPIOL_PIN_RINDEX_OFFSET + GPIOL_NUM_PINS;
  static constexpr size_t GPION_PIN_RINDEX_OFFSET = GPIOM_PIN_RINDEX_OFFSET + GPIOM_NUM_PINS;
  static constexpr size_t GPIOO_PIN_RINDEX_OFFSET = GPION_PIN_RINDEX_OFFSET + GPION_NUM_PINS;
  static constexpr size_t GPIOP_PIN_RINDEX_OFFSET = GPIOO_PIN_RINDEX_OFFSET + GPIOO_NUM_PINS;

  /*-------------------------------------------------------------------------------
  Structures
  -------------------------------------------------------------------------------*/
  /**
   *  Tracks the simulated state of the virtual GPIO device
   */
  struct VirtualState
  {
    std::recursive_timed_mutex mtx; /**< Driver lock */
    float threshold;                /**< Threshold at which logic transitions occur */
    float voltage;                  /**< Current voltage applied to the pin */
    State logicState;               /**< Current logical state */
    PinInit config;                 /**< Pin configuration settings */
  };

}    // namespace Chimera::GPIO::SIM

#endif /* !CHIMERA_SIM_GPIO_DETAIL_HPP */
