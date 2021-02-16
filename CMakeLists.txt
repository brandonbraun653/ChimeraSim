include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")


add_subdirectory(lib/json)
add_subdirectory(source/peripherals)
add_subdirectory(source/transport)
add_subdirectory(source/shared)


gen_intf_lib_variants(
  TARGET
    chimera_sim_core
  LIBRARIES
    chimera_sim_adc
    chimera_sim_can
    chimera_sim_clock
    chimera_sim_exti
    chimera_sim_gpio
    chimera_sim_interrupt
    chimera_sim_pwm
    chimera_sim_shared
    chimera_sim_spi
    chimera_sim_system
    chimera_sim_timer
    chimera_sim_transport
    chimera_sim_uart
    chimera_sim_usart
    chimera_sim_usb
    chimera_sim_watchdog

  EXPORT_DIR
    ${PROJECT_BINARY_DIR}/Chimera
)

# ====================================================
# Public Headers
# ====================================================
set(PUB_HDR chimera_sim_intf_inc)
add_library(${PUB_HDR} INTERFACE)
target_include_directories(${PUB_HDR} INTERFACE
  "./../"
  "./include"
  "./lib/json/include"
  "./lib/zeromq"
)

target_link_libraries(${PUB_HDR} INTERFACE
  etl_inc
  Boost::boost
  chimera_intf_inc
)

export(TARGETS ${PUB_HDR} FILE "${PROJECT_BINARY_DIR}/Chimera/${PUB_HDR}.cmake")
