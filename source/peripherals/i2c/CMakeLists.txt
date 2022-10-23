include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    chimera_sim_i2c
  SOURCES
    sim_i2c_basic.cpp
    sim_i2c_driver.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    chimera_sim_intf_inc
    gmock_inc
    gtest_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/Chimera"
)
