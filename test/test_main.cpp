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

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::GTEST_FLAG(color) = "auto";
  testing::GTEST_FLAG(print_time) = true;

  return RUN_ALL_TESTS();
}
