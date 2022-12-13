/********************************************************************************
 *  File Name:
 *    json_parser.hpp
 *
 *  Description:
 *    Parses JSON files into expected configuration types
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_JSON_PARSER_HPP
#define CHIMERA_SIM_JSON_PARSER_HPP

/* STL Includes */
#include <string>

/* Chimera Includes */
#include <Chimera/common>

namespace Chimera::SIM::JSON
{
  /*---------------------------------------------------------------------------
  Enumerations
  ---------------------------------------------------------------------------*/
  enum class SchemaStyle : uint8_t
  {
    VIRTUAL_PERIPH_SERVER,   /**< Communication server for peripherals */

    NUM_OPTIONS
  };

  /*---------------------------------------------------------------------------
  Structures
  ---------------------------------------------------------------------------*/
  struct PeriphServerCfg_t
  {
    Chimera::Peripheral::Type periphType; /**< Peripheral type in use */
    std::string name;
    size_t txPortBase;                    /**< Transmit port from peripheral perspective */
    size_t rxPortBase;                    /**< Receive port from peripheral perspective */

    bool valid;
  };


  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  PeriphServerCfg_t parsePeriphServerConfig( const std::string &path );

}  // namespace Chimera::SIM::JSON

#endif  /* !CHIMERA_SIM_JSON_PARSER_HPP */
