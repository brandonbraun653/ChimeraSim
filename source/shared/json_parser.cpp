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
#include <fstream>

/* JSON Includes */
#include <nlohmann/json.hpp>

/* Simulator Includes */
#include <ChimeraSim/source/shared/json_parser.hpp>

namespace Chimera::SIM::JSON
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  PeriphServerCfg_t parsePeriphServerConfig( const std::string &path )
  {
    using namespace nlohmann;

    PeriphServerCfg_t result;
    std::ifstream ifs( path );

    json j = json::parse( ifs );

    result.rxPortBase = j["network"]["rx_port_base"];
    result.txPortBase = j["network"]["tx_port_base"];
    result.valid = true;

    return result;
  }
}  // namespace Chimera::SIM::JSON
