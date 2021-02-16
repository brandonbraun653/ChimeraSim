/********************************************************************************
 *  File Name:
 *    master_slave.cpp
 *
 *  Description:
 *    Models a master/slave style communication protocol
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Sim Includes */
#include <ChimeraSim/transport>
#include <ChimeraSim/source/shared/json_parser.hpp>

namespace Chimera::SIM::Transport
{
  /*-------------------------------------------------------------------------------
  Synchronous Master-Slave Implementation
  -------------------------------------------------------------------------------*/
  SynchMasterSlave::SynchMasterSlave() : mContext( 1 )
  {

  }

  SynchMasterSlave::~SynchMasterSlave()
  {

  }

  bool SynchMasterSlave::bootServer( const std::string &configFile, const size_t periphIndex )
  {

    JSON::PeriphServerCfg_t cfg = JSON::parsePeriphServerConfig( configFile );


    if( cfg.valid )
    {
      mReceiver = zmq::socket_t( mContext, zmq::socket_type::pull );
      mReceiver.bind( "tcp://127.0.0.1:" + std::to_string( cfg.rxPortBase + periphIndex ) );

      mSender = zmq::socket_t( mContext, zmq::socket_type::push );
      mSender.bind( "tcp://127.0.0.1:" + std::to_string( cfg.txPortBase + periphIndex ) );
    }

    return cfg.valid;
  }

  Chimera::Status_t SynchMasterSlave::doTransaction( const void *const txBuffer, void *const rxBuffer, const size_t length, const size_t timeout )
  {
    return Chimera::Status::FAIL;
  }
}  // namespace Chimera::SIM::Transport
