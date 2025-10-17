/********************************************************************************
 *  File Name:
 *    test_timer_external.cpp
 *
 *  Description:
 *    External time source functionality tests for ChimeraSim
 *
 *  2025 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#include <gtest/gtest.h>
#include "sim_chimera_timer.hpp"
#include <chrono>
#include <thread>

class TimerExternalTimeTest : public ::testing::Test {
protected:
  void SetUp() override {
    ChimeraSim::Timer::reset();
  }

  void TearDown() override {
    ChimeraSim::Timer::disableExternalTimeSource();
  }
};

TEST_F( TimerExternalTimeTest, External_Time_Source_Initially_Disabled )
{
  /*-------------------------------------------------------------------------
  Test that external time source is disabled after initialization
  -------------------------------------------------------------------------*/
  ASSERT_FALSE( ChimeraSim::Timer::isExternalTimeSourceActive() );
}

TEST_F( TimerExternalTimeTest, Enable_External_Time_Source )
{
  /*-------------------------------------------------------------------------
  Test enabling external time source
  -------------------------------------------------------------------------*/
  const size_t external_time_us = 1000000;    // 1 second

  ChimeraSim::Timer::enableExternalTimeSource( external_time_us );

  ASSERT_TRUE( ChimeraSim::Timer::isExternalTimeSourceActive() );
  ASSERT_EQ( external_time_us, ChimeraSim::Timer::micros() );
  ASSERT_EQ( external_time_us / 1000U, ChimeraSim::Timer::millis() );
}

TEST_F( TimerExternalTimeTest, Update_External_Time_In_Order )
{
  /*-------------------------------------------------------------------------
  Test updating external time with increasing timestamps
  -------------------------------------------------------------------------*/
  const size_t initial_time_us = 1000000;    // 1 second
  const size_t updated_time_us = 2000000;    // 2 seconds

  ChimeraSim::Timer::enableExternalTimeSource( initial_time_us );
  ASSERT_EQ( initial_time_us, ChimeraSim::Timer::micros() );

  ChimeraSim::Timer::updateExternalTime( updated_time_us );
  ASSERT_EQ( updated_time_us, ChimeraSim::Timer::micros() );
}

TEST_F( TimerExternalTimeTest, Update_External_Time_Out_Of_Order_Ignored )
{
  /*-------------------------------------------------------------------------
  Test that out-of-order timestamps are ignored
  -------------------------------------------------------------------------*/
  const size_t initial_time_us = 2000000;    // 2 seconds
  const size_t older_time_us   = 1000000;    // 1 second (older)

  ChimeraSim::Timer::enableExternalTimeSource( initial_time_us );
  ASSERT_EQ( initial_time_us, ChimeraSim::Timer::micros() );

  // This should be ignored
  ChimeraSim::Timer::updateExternalTime( older_time_us );
  ASSERT_EQ( initial_time_us, ChimeraSim::Timer::micros() );    // Should remain unchanged
}

TEST_F( TimerExternalTimeTest, Update_External_Time_Duplicate_Ignored )
{
  /*-------------------------------------------------------------------------
  Test that duplicate timestamps are ignored
  -------------------------------------------------------------------------*/
  const size_t initial_time_us = 1000000;    // 1 second

  ChimeraSim::Timer::enableExternalTimeSource( initial_time_us );
  ASSERT_EQ( initial_time_us, ChimeraSim::Timer::micros() );

  // This should be ignored
  ChimeraSim::Timer::updateExternalTime( initial_time_us );
  ASSERT_EQ( initial_time_us, ChimeraSim::Timer::micros() );    // Should remain unchanged
}

TEST_F( TimerExternalTimeTest, Disable_External_Time_Source )
{
  /*-------------------------------------------------------------------------
  Test disabling external time source reverts to real time
  -------------------------------------------------------------------------*/
  const size_t external_time_us = 1000000;    // 1 second

  ChimeraSim::Timer::enableExternalTimeSource( external_time_us );
  ASSERT_TRUE( ChimeraSim::Timer::isExternalTimeSourceActive() );

  ChimeraSim::Timer::disableExternalTimeSource();
  ASSERT_FALSE( ChimeraSim::Timer::isExternalTimeSourceActive() );

  // After disabling, time should advance with real time again
  const size_t start = ChimeraSim::Timer::micros();
  std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
  const size_t end = ChimeraSim::Timer::micros();

  ASSERT_TRUE( end > start );
}

TEST_F( TimerExternalTimeTest, Delay_With_External_Time_Source )
{
  /*-------------------------------------------------------------------------
  Test that delays work with external time source
  -------------------------------------------------------------------------*/
  const size_t initial_time_us = 1000000;    // 1 second
  const size_t delay_us        = 50000;      // 50 milliseconds

  ChimeraSim::Timer::enableExternalTimeSource( initial_time_us );

  const size_t start = ChimeraSim::Timer::micros();
  ChimeraSim::Timer::delayMicroseconds( delay_us );
  const size_t end = ChimeraSim::Timer::micros();

  // With external time source, delay should advance the external time
  ASSERT_EQ( start + delay_us, end );
}

TEST_F( TimerExternalTimeTest, External_Time_After_Disable )
{
  /*-------------------------------------------------------------------------
  Test that external time is properly restored when disabled
  -------------------------------------------------------------------------*/
  const size_t external_time_us = 5000000;    // 5 seconds

  ChimeraSim::Timer::enableExternalTimeSource( external_time_us );

  // Let some real time pass while external time is active
  std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );

  const size_t external_micros = ChimeraSim::Timer::micros();
  ASSERT_EQ( external_time_us, external_micros );

  ChimeraSim::Timer::disableExternalTimeSource();

  // After disabling, real time should be restored and continue advancing
  const size_t real_start = ChimeraSim::Timer::micros();
  std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
  const size_t real_end = ChimeraSim::Timer::micros();

  ASSERT_TRUE( real_end > real_start );
}
