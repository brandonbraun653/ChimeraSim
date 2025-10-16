/********************************************************************************
 *  File Name:
 *    test_timer_delays.cpp
 *
 *  Description:
 *    Timer delay functionality tests for ChimeraSim
 *
 *  2025 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#include <CppUTest/TestHarness.h>
#include "sim_chimera_timer.hpp"
#include <chrono>
#include <thread>

TEST_GROUP( TimerDelays ){ void setup(){ ChimeraSim::Timer::reset();
}

void teardown()
{
  // Cleanup if needed
}
}
;

TEST( TimerDelays, DelayMicroseconds_Zero_Delay )
{
  /*-------------------------------------------------------------------------
  Test that zero delay doesn't block
  -------------------------------------------------------------------------*/
  const size_t start = ChimeraSim::Timer::micros();
  ChimeraSim::Timer::delayMicroseconds( 0 );
  const size_t end = ChimeraSim::Timer::micros();

  // Should complete very quickly
  CHECK( ( end - start ) < 10U );    // Less than 10 microseconds
}

TEST( TimerDelays, DelayMicroseconds_Small_Delay )
{
  /*-------------------------------------------------------------------------
  Test small delay (100 microseconds)
  -------------------------------------------------------------------------*/
  const size_t start = ChimeraSim::Timer::micros();
  ChimeraSim::Timer::delayMicroseconds( 100 );
  const size_t end = ChimeraSim::Timer::micros();

  const size_t elapsed = end - start;

  // Should be at least the requested delay, but allow some variance
  CHECK( elapsed >= 90U );     // At least 90 microseconds
  CHECK( elapsed <= 200U );    // But not excessively longer
}

TEST( TimerDelays, DelayMilliseconds_Zero_Delay )
{
  /*-------------------------------------------------------------------------
  Test that zero millisecond delay doesn't block
  -------------------------------------------------------------------------*/
  const size_t start = ChimeraSim::Timer::millis();
  ChimeraSim::Timer::delayMilliseconds( 0 );
  const size_t end = ChimeraSim::Timer::millis();

  // Should complete very quickly
  CHECK( ( end - start ) < 1U );    // Less than 1 millisecond
}

TEST( TimerDelays, DelayMilliseconds_Small_Delay )
{
  /*-------------------------------------------------------------------------
  Test small millisecond delay (10 milliseconds)
  -------------------------------------------------------------------------*/
  const size_t start = ChimeraSim::Timer::millis();
  ChimeraSim::Timer::delayMilliseconds( 10 );
  const size_t end = ChimeraSim::Timer::millis();

  const size_t elapsed = end - start;

  // Should be at least the requested delay, but allow some variance
  CHECK( elapsed >= 9U );     // At least 9 milliseconds
  CHECK( elapsed <= 20U );    // But not excessively longer
}
