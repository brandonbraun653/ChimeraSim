include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    chimera_sim_pwm
  SOURCES
    sim_chimera_pwm.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    chimera_sim_intf_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/Chimera"
)
