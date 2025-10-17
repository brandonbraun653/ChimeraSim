/********************************************************************************
 *  File Name:
 *    test_main.cpp
 *
 *  Description:
 *    Main entry point for ChimeraSim unit tests
 *
 *  2025 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>

#include <Chimera/common>

int main(int argc, char **argv) {
  printf("Running ChimeraSim tests from %s\n", __FILE__);

  // Initialize Google Test
  testing::InitGoogleTest(&argc, argv);

  // Set up test output format for CI/CD
  testing::GTEST_FLAG(color) = "auto";
  testing::GTEST_FLAG(print_time) = true;

  return RUN_ALL_TESTS();
}
