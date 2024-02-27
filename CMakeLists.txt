include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

# ====================================================
# Sub Projects
# ====================================================
add_subdirectory(lib/json)
add_subdirectory(source/controller)
add_subdirectory(source/peripherals)
add_subdirectory(source/shared)
add_subdirectory(source/transport)

# ====================================================
# Core Library
# ====================================================
gen_intf_lib_variants(
  TARGET
    chimera_sim_core
  LIBRARIES
    chimera_sim_adc
    chimera_sim_can
    chimera_sim_controller
    chimera_sim_clock
    chimera_sim_exti
    chimera_sim_gpio
    chimera_sim_i2c
    chimera_sim_interrupt
    chimera_sim_pwm
    chimera_sim_sdio
    chimera_sim_serial
    chimera_sim_shared
    chimera_sim_spi
    chimera_sim_system
    chimera_sim_timer
    chimera_sim_transport
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
    "./../"
    "./include"
    "./lib/json/include"
    "./lib/zeromq"
  INTF_LIBRARIES
    etl_inc
    aurora_intf_inc
    chimera_intf_inc
    gtest_inc
    gmock_inc

  EXPORT_DIR
    ${PROJECT_BINARY_DIR}/Chimera
)
