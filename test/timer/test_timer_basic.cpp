/********************************************************************************
 *  File Name:
 *    test_timer_basic.cpp
 *
 *  Description:
 *    Basic timer functionality tests for ChimeraSim
 *
 *  2025 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#include <CppUTest/TestHarness.h>
#include "sim_chimera_timer.hpp"
#include <chrono>
#include <thread>

TEST_GROUP( TimerBasic ){ void setup(){ ChimeraSim::Timer::reset();
}

void teardown()
{
  // Cleanup if needed
}
}
;

TEST( TimerBasic, Initialization )
{
  /*-------------------------------------------------------------------------
  Test that initialization succeeds
  -------------------------------------------------------------------------*/
  CHECK_EQUAL( Chimera::Status::OK, ChimeraSim::Timer::initialize() );
}

TEST( TimerBasic, Reset )
{
  /*-------------------------------------------------------------------------
  Test that reset succeeds
  -------------------------------------------------------------------------*/
  CHECK_EQUAL( Chimera::Status::OK, ChimeraSim::Timer::reset() );
}

TEST( TimerBasic, Microseconds_Increases_Over_Time )
{
  /*-------------------------------------------------------------------------
  Test that micros() increases over time when using real time
  -------------------------------------------------------------------------*/
  ChimeraSim::Timer::initialize();

  const size_t start = ChimeraSim::Timer::micros();
  std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
  const size_t end = ChimeraSim::Timer::micros();

  CHECK( end > start );
}

TEST( TimerBasic, Milliseconds_Increases_Over_Time )
{
  /*-------------------------------------------------------------------------
  Test that millis() increases over time when using real time
  -------------------------------------------------------------------------*/
  ChimeraSim::Timer::initialize();

  const size_t start = ChimeraSim::Timer::millis();
  std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
  const size_t end = ChimeraSim::Timer::millis();

  CHECK( end > start );
}

TEST( TimerBasic, Millis_Micros_Relationship )
{
  /*-------------------------------------------------------------------------
  Test that millis() is approximately micros() / 1000
  -------------------------------------------------------------------------*/
  ChimeraSim::Timer::initialize();

  const size_t micros_val = ChimeraSim::Timer::micros();
  const size_t millis_val = ChimeraSim::Timer::millis();

  // Allow for some timing variance, but should be within 1ms difference
  const size_t micros_to_millis = micros_val / 1000U;
  const size_t difference =
      ( micros_to_millis > millis_val ) ? ( micros_to_millis - millis_val ) : ( millis_val - micros_to_millis );

  CHECK( difference <= 1U );
}
