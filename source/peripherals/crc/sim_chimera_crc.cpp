/********************************************************************************
 *  File Name:
 *    sim_chimera_crc.cpp
 *
 *  Description:
 *    Simulator CRC driver
 *
 *  2025 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/crc>

namespace Chimera::CRC::Backend
{
  Chimera::Status_t initialize()
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t reset()
  {
    return Chimera::Status::OK;
  }

  Driver_rPtr getDriver( [[maybe_unused]] const Channel channel )
  {
    return nullptr;  // Simulator doesn't provide actual CRC drivers
  }

  Chimera::Status_t registerDriver( Chimera::CRC::Backend::DriverConfig &registry )
  {
    registry.isSupported = true;
    registry.initialize  = initialize;
    registry.reset       = reset;
    registry.getDriver   = getDriver;
    return Chimera::Status::OK;
  }
}  // namespace Chimera::CRC::Backend
