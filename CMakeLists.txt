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

# ====================================================
# Test Executable
# ====================================================
add_executable(chimera_sim_tests
  test/test_main.cpp
  test/timer/test_timer_basic.cpp
  test/timer/test_timer_delays.cpp
  test/timer/test_timer_external.cpp
  source/peripherals/timer/sim_chimera_timer.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/CommandLineArguments.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/MemoryLeakWarningPlugin.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/TestHarness_c.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/TestRegistry.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/CommandLineTestRunner.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/SimpleString.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/SimpleStringInternalCache.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/TestMemoryAllocator.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/TestResult.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/JUnitTestOutput.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/TeamCityTestOutput.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/TestFailure.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/TestOutput.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/MemoryLeakDetector.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/TestFilter.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/TestPlugin.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/TestTestingFixture.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/SimpleMutex.cpp
  ${COMMON_TOOL_ROOT}/cpputest/src/CppUTest/Utest.cpp
  ${COMMON_TOOL_ROOT}/cpputest/platforms/gcc/UTestPlatform.cpp
)

target_link_libraries(chimera_sim_tests
  PRIVATE
    chimera_sim_intf_inc
    aurora_intf_inc
)

target_compile_definitions(chimera_sim_tests
  PRIVATE
    CHIMERA_SIMULATOR
    CPPUTEST_MEM_LEAK_DETECTION_DISABLED
)

target_include_directories(chimera_sim_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/source/peripherals/timer
    ${COMMON_TOOL_ROOT}/cpputest/include
)

# ====================================================
# Register Test with CTest
# ====================================================
add_test(
  NAME chimera_sim_tests
  COMMAND chimera_sim_tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
