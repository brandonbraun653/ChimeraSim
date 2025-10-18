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
#include <ChimeraSim/timer>
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

TEST_F( TimerExternalTimeTest, Delay_With_External_Time_Source )
{
  /*-------------------------------------------------------------------------
  Test that delays work with external time source
  -------------------------------------------------------------------------*/
  const size_t initial_time_us = 1000000;    // 1 second
  const size_t delay_us        = 50000;      // 50 milliseconds

  ChimeraSim::Timer::enableExternalTimeSource( initial_time_us );

  const size_t start = ChimeraSim::Timer::micros();

  // Spawn a thread to update external time after a short delay
  std::thread updater_thread([initial_time_us, delay_us]() -> void {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Wait a bit in realtime
    ChimeraSim::Timer::updateExternalTime( initial_time_us + delay_us );
  });

  // This should block until the external time is updated
  ChimeraSim::Timer::delayMicroseconds( delay_us );
  const size_t end = ChimeraSim::Timer::micros();

  updater_thread.join();

  // With external time source, delay should advance the external time by at least the requested amount
  ASSERT_GE( end, start + delay_us );
  ASSERT_LE( end - start, delay_us + 1000 );  // Allow up to 1ms extra due to timing variations
}

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
  const size_t baseline_us = ChimeraSim::Timer::micros();

  ChimeraSim::Timer::enableExternalTimeSource( external_time_us );

  ASSERT_TRUE( ChimeraSim::Timer::isExternalTimeSourceActive() );
  const size_t actual_micros = ChimeraSim::Timer::micros();
  const size_t expected_min = baseline_us + external_time_us;
  const size_t expected_max = baseline_us + external_time_us + 10;  // Allow small timing variation

  ASSERT_GE( actual_micros, expected_min );
  ASSERT_LE( actual_micros, expected_max );
  ASSERT_EQ( actual_micros / 1000U, ChimeraSim::Timer::millis() );
}

TEST_F( TimerExternalTimeTest, Update_External_Time_In_Order )
{
  /*---------------------------------------------------------------------------
  Ensure we start with a non-zero "standard" time
  ---------------------------------------------------------------------------*/
  while( ChimeraSim::Timer::micros() < 500u );
  const size_t baseline_us = ChimeraSim::Timer::micros();
  ASSERT_GE( baseline_us, 500u );

  /*-------------------------------------------------------------------------
  Test updating external time with increasing timestamps
  -------------------------------------------------------------------------*/
  const size_t initial_time_us = 1000000;    // 1 second
  const size_t updated_time_us = 2000000;    // 2 seconds

  ChimeraSim::Timer::enableExternalTimeSource( initial_time_us );
  size_t actual_after_enable = ChimeraSim::Timer::micros();
  ASSERT_GE( actual_after_enable, baseline_us + initial_time_us );
  ASSERT_LE( actual_after_enable, baseline_us + initial_time_us + 10 );  // Allow small timing variation

  ChimeraSim::Timer::updateExternalTime( updated_time_us );
  size_t actual_after_update = ChimeraSim::Timer::micros();
  ASSERT_GE( actual_after_update, baseline_us + updated_time_us );
  ASSERT_LE( actual_after_update, baseline_us + updated_time_us + 10 );  // Allow small timing variation
}

TEST_F( TimerExternalTimeTest, Update_External_Time_Out_Of_Order_Ignored )
{
  /*-------------------------------------------------------------------------
  Test that out-of-order timestamps are ignored
  -------------------------------------------------------------------------*/
  const size_t initial_time_us = 2000000;    // 2 seconds
  const size_t older_time_us   = 1000000;    // 1 second (older)
  const size_t baseline_us = ChimeraSim::Timer::micros();

  ChimeraSim::Timer::enableExternalTimeSource( initial_time_us );
  size_t time_after_enable = ChimeraSim::Timer::micros();
  ASSERT_GE( time_after_enable, baseline_us + initial_time_us );
  ASSERT_LE( time_after_enable, baseline_us + initial_time_us + 10 );

  // This should be ignored
  ChimeraSim::Timer::updateExternalTime( older_time_us );
  size_t time_after_ignored_update = ChimeraSim::Timer::micros();
  ASSERT_GE( time_after_ignored_update, baseline_us + initial_time_us );
  ASSERT_LE( time_after_ignored_update, baseline_us + initial_time_us + 10 );  // Should remain unchanged
}

TEST_F( TimerExternalTimeTest, Update_External_Time_Duplicate_Ignored )
{
  /*-------------------------------------------------------------------------
  Test that duplicate timestamps are ignored
  -------------------------------------------------------------------------*/
  const size_t initial_time_us = 1000000;    // 1 second
  const size_t baseline_us = ChimeraSim::Timer::micros();

  ChimeraSim::Timer::enableExternalTimeSource( initial_time_us );
  size_t time_after_enable = ChimeraSim::Timer::micros();
  ASSERT_GE( time_after_enable, baseline_us + initial_time_us );
  ASSERT_LE( time_after_enable, baseline_us + initial_time_us + 10 );

  // This should be ignored
  ChimeraSim::Timer::updateExternalTime( initial_time_us );
  size_t time_after_duplicate_update = ChimeraSim::Timer::micros();
  ASSERT_GE( time_after_duplicate_update, baseline_us + initial_time_us );
  ASSERT_LE( time_after_duplicate_update, baseline_us + initial_time_us + 10 );  // Should remain unchanged
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

TEST_F( TimerExternalTimeTest, External_Time_After_Disable )
{
  /*-------------------------------------------------------------------------
  Test that external time is properly restored when disabled
  -------------------------------------------------------------------------*/
  const size_t external_time_us = 5000000;    // 5 seconds
  const size_t baseline_us = ChimeraSim::Timer::micros();

  ChimeraSim::Timer::enableExternalTimeSource( external_time_us );

  // Let some real time pass while external time is active
  std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );

  const size_t external_micros = ChimeraSim::Timer::micros();
  ASSERT_GE( external_micros, baseline_us + external_time_us );
  ASSERT_LE( external_micros, baseline_us + external_time_us + 10 );

  ChimeraSim::Timer::disableExternalTimeSource();

  // After disabling, real time should be restored and continue advancing
  const size_t real_start = ChimeraSim::Timer::micros();
  std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
  const size_t real_end = ChimeraSim::Timer::micros();

  ASSERT_TRUE( real_end > real_start );
}
