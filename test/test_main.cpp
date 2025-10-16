/********************************************************************************
 *  File Name:
 *    test_main.cpp
 *
 *  Description:
 *    Main entry point for ChimeraSim unit tests
 *
 *  2025 | Brandon Braun | brandonbraun653@gmail.com
 ********************************************************************************/

#include <CppUTest/CommandLineTestRunner.h>
#include <Chimera/common>

int main( int argc, char **argv )
{
  /*-------------------------------------------------------------------------
  Run all tests
  -------------------------------------------------------------------------*/
  int result = CommandLineTestRunner::RunAllTests( argc, argv );

  return result;
}
