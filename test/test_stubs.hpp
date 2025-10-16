/********************************************************************************
 *  File Name:
 *    test_stubs.hpp
 *
 *  Description:
 *    Stub definitions for testing ChimeraSim components
 *
 *  2025 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#ifndef CHIMERA_SIM_TEST_STUBS_HPP
#define CHIMERA_SIM_TEST_STUBS_HPP

/*-----------------------------------------------------------------------------
Logging stubs - define as empty macros for tests
-----------------------------------------------------------------------------*/
#define LOG_WARN( ... ) \
  do                    \
  {                     \
  } while( 0 )
#define LOG_DEBUG( ... ) \
  do                     \
  {                      \
  } while( 0 )

/*-----------------------------------------------------------------------------
Function stubs for testing
-----------------------------------------------------------------------------*/
namespace Chimera
{
  inline void insert_debug_breakpoint()
  {
  }
}    // namespace Chimera

#endif /* CHIMERA_SIM_TEST_STUBS_HPP */
