include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    chimera_sim_timer
  SOURCES
    sim_chimera_timer.cpp
    views/sim_timer_base_intf.cpp
    views/sim_timer_pwm_intf.cpp
    views/sim_timer_tri_phase_pwm.cpp
    views/sim_timer_trigger_intf.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    chimera_sim_intf_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/Chimera"
)
