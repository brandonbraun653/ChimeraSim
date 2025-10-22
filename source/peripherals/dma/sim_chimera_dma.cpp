/********************************************************************************
 *  File Name:
 *    sim_chimera_dma.cpp
 *
 *  Description:
 *    DMA Simulator
 *
 *  2025 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/dma>

namespace Chimera::DMA::Backend
{
  Chimera::Status_t registerDriver( Chimera::DMA::Backend::DriverConfig &registry )
  {
    registry.isSupported   = false;
    registry.initialize    = nullptr;
    registry.reset         = nullptr;
    registry.constructPipe = nullptr;
    registry.memTransfer   = nullptr;
    registry.pipeTransfer  = nullptr;
    registry.abortTransfer = nullptr;

    return Chimera::Status::NOT_SUPPORTED;
  }
}    // namespace Chimera::DMA::Backend

#endif /* CHIMERA_SIMULATOR */
