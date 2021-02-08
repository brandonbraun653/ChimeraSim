include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    chimera_sim_uart
  SOURCES
    sim_chimera_uart.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    chimera_sim_intf_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/Chimera"
)
