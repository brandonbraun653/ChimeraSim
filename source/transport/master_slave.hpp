/********************************************************************************
 *  File Name:
 *    master_slave.hpp
 *
 *  Description:
 *    Models a physical communication model where one device acts as the host
 *    controller (master) and another acts as the client (slave).
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_COMMUNICATION_MODEL_MASTER_SLAVE_HPP
#define CHIMERA_SIM_COMMUNICATION_MODEL_MASTER_SLAVE_HPP

/* Chimera Includes */
#include <Chimera/common>

/* Network Includes */
#include <zmq.hpp>


namespace Chimera::SIM::Transport
{
  /*-------------------------------------------------------------------------------
  Classes
  -------------------------------------------------------------------------------*/
  /**
   *  Models a synchronous master-slave communication device. A good example
   *  of this kind of device is SPI, or Microwire.
   */
  class SynchMasterSlave
  {
  public:
    SynchMasterSlave();
    ~SynchMasterSlave();

    /**
     *  Boots a ZeroMQ PUSH/PULL server for synchronous communication
     *
     *  @param[in]  configFile      JSON configuration file
     *  @param[in]  periphIndex     Index of the peripheral being configured
     *  @return bool
     */
    bool bootServer( const std::string &configFile, const size_t periphIndex );

    /**
     *  Performs a synchronous transation with the device on the other end. This
     *  expects the same number of bytes sent will also be received.
     *
     *  @param[in]  txBuffer        Buffer of data to be transmitted
     *  @param[out] rxBuffer        Buffer to write data into
     *  @param[in]  length          Size of both tx/rx buffers
     *  @param[in]  timeout         How long to wait for the endpoint to respond to TX/RX request
     *  @return Chimera::Status_t
     */
    Chimera::Status_t doTransaction( const void *const txBuffer, void *const rxBuffer, const size_t length,
                                     const std::chrono::seconds timeout );

  private:
    bool mInitialized;
    zmq::context_t mContext;
    zmq::socket_t mReceiver;
    zmq::socket_t mSender;
  };
}  // namespace Chimera::SIM::Model

#endif  /* !CHIMERA_SIM_COMMUNICATION_MODEL_MASTER_SLAVE_HPP */
