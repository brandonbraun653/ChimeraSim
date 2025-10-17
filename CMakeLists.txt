include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

set(CHIMERA_SIM_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# ====================================================
# Sub Projects
# ====================================================
# add_subdirectory(lib/json)  # TODO: Empty directory, needs CMakeLists.txt
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

  EXPORT_DIR
    ${PROJECT_BINARY_DIR}/Chimera
)

# ====================================================
# Test Executable
# ====================================================
add_subdirectory(test/timer)
# add_executable(chimera_sim_tests
#   test/test_main.cpp
#   test/timer/test_timer_basic.cpp
#   test/timer/test_timer_delays.cpp
#   test/timer/test_timer_external.cpp
#   source/peripherals/timer/sim_chimera_timer.cpp
# )

# target_link_libraries(chimera_sim_tests
#   PRIVATE
#     chimera_sim_intf_inc
#     aurora_intf_inc
#     aurora_logging
#     chimera_core
#     prj_device_target
#     gtest
# )

# target_compile_definitions(chimera_sim_tests
#   PRIVATE
#     CHIMERA_SIMULATOR
# )

# target_include_directories(chimera_sim_tests
#   PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/source
#     ${CMAKE_CURRENT_SOURCE_DIR}/source/peripherals/timer
# )

# ====================================================
# Register Test with CTest
# ====================================================
# include(GoogleTest)
# gtest_discover_tests(chimera_sim_tests
#   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#   PROPERTIES
#     TIMEOUT 60
#     ENVIRONMENT "GTEST_COLOR=1"
# )
