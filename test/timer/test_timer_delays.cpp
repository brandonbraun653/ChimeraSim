/********************************************************************************
 *  File Name:
 *    test_timer_delays.cpp
 *
 *  Description:
 *    Timer delay functionality tests for ChimeraSim
 *
 *  2025 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#include <gtest/gtest.h>
#include "sim_chimera_timer.hpp"
#include <chrono>
#include <thread>

class TimerDelaysTest : public ::testing::Test {
protected:
  void SetUp() override {
    ChimeraSim::Timer::reset();
  }

  void TearDown() override {
    // Cleanup if needed
  }
};

TEST_F( TimerDelaysTest, DelayMicroseconds_Zero_Delay )
{
  /*-------------------------------------------------------------------------
  Test that zero delay doesn't block
  -------------------------------------------------------------------------*/
  const size_t start = ChimeraSim::Timer::micros();
  ChimeraSim::Timer::delayMicroseconds( 0 );
  const size_t end = ChimeraSim::Timer::micros();

  // Should complete very quickly
  ASSERT_LT( ( end - start ), 10U );    // Less than 10 microseconds
}

TEST_F( TimerDelaysTest, DelayMicroseconds_Small_Delay )
{
  /*-------------------------------------------------------------------------
  Test small delay (100 microseconds)
  -------------------------------------------------------------------------*/
  const size_t start = ChimeraSim::Timer::micros();
  ChimeraSim::Timer::delayMicroseconds( 100 );
  const size_t end = ChimeraSim::Timer::micros();

  const size_t elapsed = end - start;

  // Should be at least the requested delay, but allow some variance
  ASSERT_GE( elapsed, 90U );     // At least 90 microseconds
  ASSERT_LE( elapsed, 200U );    // But not excessively longer
}

TEST_F( TimerDelaysTest, DelayMilliseconds_Zero_Delay )
{
  /*-------------------------------------------------------------------------
  Test that zero millisecond delay doesn't block
  -------------------------------------------------------------------------*/
  const size_t start = ChimeraSim::Timer::millis();
  ChimeraSim::Timer::delayMilliseconds( 0 );
  const size_t end = ChimeraSim::Timer::millis();

  // Should complete very quickly
  ASSERT_LT( ( end - start ), 1U );    // Less than 1 millisecond
}

TEST_F( TimerDelaysTest, DelayMilliseconds_Small_Delay )
{
  /*-------------------------------------------------------------------------
  Test small millisecond delay (10 milliseconds)
  -------------------------------------------------------------------------*/
  const size_t start = ChimeraSim::Timer::millis();
  ChimeraSim::Timer::delayMilliseconds( 10 );
  const size_t end = ChimeraSim::Timer::millis();

  const size_t elapsed = end - start;

  // Should be at least the requested delay, but allow some variance
  ASSERT_GE( elapsed, 9U );     // At least 9 milliseconds
  ASSERT_LE( elapsed, 20U );    // But not excessively longer
}
