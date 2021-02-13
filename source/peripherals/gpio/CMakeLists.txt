include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    chimera_sim_gpio
  SOURCES
    sim_gpio_basic.cpp
    sim_gpio_controlled.cpp
    sim_gpio_driver.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    chimera_sim_intf_inc
    gmock_inc
    gtest_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/Chimera"
)
