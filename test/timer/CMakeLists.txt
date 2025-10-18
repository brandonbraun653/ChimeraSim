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
    ${CHIMERA_SIM_ROOT}/include
  LIBRARIES
    aurora_intf_inc
    aurora_logging
    chimera_core
    chimera_sim_crc
    chimera_sim_intf_inc
    chimera_sim_power
    chimera_sim_serial
    prj_device_target
)
