/********************************************************************************
 *  File Name:
 *    full_duplex_pipe.hpp
 *
 *  Description:
 *    Full duplex communication with ZeroMQ
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_TRANSPORT_FULL_DUPLEX_HPP
#define CHIMERA_SIM_TRANSPORT_FULL_DUPLEX_HPP

/* Network Includes */
#include <zmq.hpp>

namespace Chimera::SIM::Transport
{
  /*
  - Configure a new endpoint for TX/RX based on a JSON file
  - Make the endpoint interface its own class for easily adding on to a virtual peripheral driver
  - This should probably be very low level to allow the communication protocol to be
    customized on a per-peripheral basis. Some peripherals are byte stream focused, some are packet
    based, etc.
  */
}  // namespace Chimera::SIM::Transport

#endif  /* !CHIMERA_SIM_TRANSPORT_FULL_DUPLEX_HPP */
