include(CTEmbedded)

set(CHIMERA_SIM_ROOT ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "The root directory of the ChimeraSim project" FORCE)

# ====================================================
# Sub Projects
# ====================================================
add_subdirectory(source/peripherals)

# ====================================================
# Core Library
# ====================================================
gen_intf_lib_variants(
  TARGET
    chimera_sim_core
  LIBRARIES
    chimera_sim_adc
    chimera_sim_can
    chimera_sim_clock
    chimera_sim_exti
    chimera_sim_gpio
    chimera_sim_i2c
    chimera_sim_interrupt
    chimera_sim_pwm
    chimera_sim_sdio
    chimera_sim_serial
    chimera_sim_spi
    chimera_sim_system
    chimera_sim_timer
    chimera_sim_uart
    chimera_sim_usart
    chimera_sim_watchdog
  EXPORT_DIR
    ${PROJECT_BINARY_DIR}/Chimera
)

# ====================================================
# Interface Library
# ====================================================
gen_intf_lib(
  TARGET
    chimera_sim_intf_inc
  INTF_INCLUDES
    "${CHIMERA_SIM_ROOT}/../"
    "${CHIMERA_SIM_ROOT}/include"
    "${CHIMERA_SIM_ROOT}/lib/json/include"
    "${CHIMERA_SIM_ROOT}/lib/zeromq"
  INTF_LIBRARIES
    etl_inc
    aurora_intf_inc
    chimera_intf_inc
  EXPORT_DIR
    ${PROJECT_BINARY_DIR}/Chimera
)

# ====================================================
# Test Executable
# ====================================================
add_subdirectory(test/timer)