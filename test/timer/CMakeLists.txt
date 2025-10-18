# ====================================================
# Timer Test Executable
# ====================================================
include(CTTesting)

gen_gtest_executable(
  TARGET chimera_sim_timer_tests
  SOURCES
    ${CHIMERA_SIM_ROOT}/test/test_main.cpp
    test_timer_basic.cpp
    test_timer_delays.cpp
    test_timer_external.cpp
    ${CHIMERA_SIM_ROOT}/source/peripherals/timer/sim_chimera_timer.cpp
  INCLUDES
    ${CHIMERA_SIM_ROOT}/source
    ${CHIMERA_SIM_ROOT}/source/peripherals/timer
  DEFINES
    CHIMERA_SIMULATOR
  LIBRARIES
    chimera_sim_intf_inc
    aurora_intf_inc
    aurora_logging
    chimera_core
    prj_device_target
)
