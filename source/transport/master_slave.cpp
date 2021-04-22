/********************************************************************************
 *  File Name:
 *    master_slave.cpp
 *
 *  Description:
 *    Models a master/slave style communication protocol
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* STL Includes */
#include <filesystem>

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Sim Includes */
#include <ChimeraSim/transport>
#include <ChimeraSim/source/shared/json_parser.hpp>

namespace Chimera::SIM::Transport
{
  /*-------------------------------------------------------------------------------
  Synchronous Master-Slave Implementation
  -------------------------------------------------------------------------------*/
  SynchMasterSlave::SynchMasterSlave() : mInitialized( false ), mContext( 1 )
  {
  }


  SynchMasterSlave::~SynchMasterSlave()
  {
  }


  bool SynchMasterSlave::bootServer( const std::string &configFile, const size_t periphIndex )
  {
    using namespace Aurora::Logging;
    JSON::PeriphServerCfg_t cfg = JSON::parsePeriphServerConfig( configFile );

    if ( !cfg.valid )
    {
      LOG_DEBUG( "Failed to boot server. Invalid configuration.\r\n" );
      return false;
    }

    /*-------------------------------------------------
    Boot the RX port
    -------------------------------------------------*/
    size_t rxPort         = cfg.rxPortBase + periphIndex;
    std::string rxAddress = "tcp://127.0.0.1:" + std::to_string( rxPort );
    mReceiver             = zmq::socket_t( mContext, zmq::socket_type::pull );
    mReceiver.bind( rxAddress );
    LOG_DEBUG( "Opened %s %d RX port at %s\r\n", cfg.name.c_str(), periphIndex, rxAddress.c_str() );

    /*-------------------------------------------------
    Boot the TX port
    -------------------------------------------------*/
    size_t txPort         = cfg.txPortBase + periphIndex;
    std::string txAddress = "tcp://127.0.0.1:" + std::to_string( txPort );
    mSender               = zmq::socket_t( mContext, zmq::socket_type::push );
    mSender.bind( txAddress );
    LOG_DEBUG( "Opened %s %d TX port at %s\r\n", cfg.name.c_str(), periphIndex, txAddress.c_str() );

    mInitialized = true;
    return true;
  }


  Chimera::Status_t SynchMasterSlave::doTransaction( const void *const txBuffer, void *const rxBuffer, const size_t length,
                                                     const std::chrono::seconds timeout )
  {
    using namespace Aurora::Logging;

    /*-------------------------------------------------
    Input protection
    -------------------------------------------------*/
    if( !mInitialized || !txBuffer || !rxBuffer || !length )
    {
      return Chimera::Status::FAIL;
    }

    /*-------------------------------------------------
    Prepare the data buffers
    -------------------------------------------------*/
    zmq::message_t txData = zmq::message_t( txBuffer, length );
    zmq::message_t rxData;

    /*-------------------------------------------------
    Perform the transaction. Send will block until the
    remote accepts the data, recv will block until the
    remote sends data back.
    -------------------------------------------------*/
    mSender.send( txData );
    mReceiver.recv( &rxData );

    /*-------------------------------------------------
    Copy out the received data
    -------------------------------------------------*/
    if( rxData.size() != length )
    {
      LOG_DEBUG( "Failed SPI transaction\r\n" );
      return Chimera::Status::FAIL;
    }
    else
    {
      memcpy( rxBuffer, rxData.data(), length );
      return Chimera::Status::OK;
    }
  }
}    // namespace Chimera::SIM::Transport
