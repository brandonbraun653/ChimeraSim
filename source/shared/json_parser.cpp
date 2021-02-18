/********************************************************************************
 *  File Name:
 *    json_parser.cpp
 *
 *  Description:
 *    Implements the parsing of JSON configuration files into the appropriate
 *    data types
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* STL Includes */
#include <filesystem>
#include <fstream>

/* JSON Includes */
#include <nlohmann/json.hpp>

/* Aurora Includes */
#include <Aurora/logging>

/* Simulator Includes */
#include <ChimeraSim/source/shared/json_parser.hpp>

namespace Chimera::SIM::JSON
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  PeriphServerCfg_t parsePeriphServerConfig( const std::string &path )
  {
    using namespace Aurora::Logging;

    PeriphServerCfg_t result = {};

    /*-------------------------------------------------
    Input Protection
    -------------------------------------------------*/
    if ( !std::filesystem::exists( path ) )
    {
      getRootSink()->flog( Level::LVL_DEBUG, "File does not exist %s\r\n", path.c_str() );
      result.valid = false;
      return result;
    }

    /*-------------------------------------------------
    Parse the json file
    -------------------------------------------------*/
    auto j = nlohmann::json::parse( std::ifstream( path ) );

    result.name       = j[ "peripheral" ][ "name" ];
    result.rxPortBase = j[ "network" ][ "rx_port_base" ];
    result.txPortBase = j[ "network" ][ "tx_port_base" ];
    result.valid = true;

    return result;
  }
}    // namespace Chimera::SIM::JSON
