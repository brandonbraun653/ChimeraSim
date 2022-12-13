/********************************************************************************
 *  File Name:
 *    sim_spi_networked.cpp
 *
 *  Description:
 *    Networked variant of the SPI protocol
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* STL Includes */
#include <chrono>
#include <filesystem>

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Includes */
#include <ChimeraSim/spi>

namespace Chimera::SPI::SIM
{
  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  Chimera::Status_t NetworkedSPI::init( const Chimera::SPI::DriverConfig &setupStruct )
  {
    using namespace Aurora::Logging;

    /*-------------------------------------------------
    Store the driver configuration for other virtual
    functions to use.
    -------------------------------------------------*/
    mHWState.config = setupStruct;

    /*-------------------------------------------------
    Find the network configuration file
    -------------------------------------------------*/
    std::filesystem::path cfgFile = std::filesystem::path{ __FILE__ }.parent_path() / "spi_config.json";
    RT_HARD_ASSERT( std::filesystem::exists( cfgFile ) );

    /*-------------------------------------------------
    Try and boot the server
    -------------------------------------------------*/
    if ( this->bootServer( cfgFile.string(), static_cast<size_t>( setupStruct.HWInit.hwChannel ) ) )
    {
      LOG_DEBUG( "Server initialized\r\n" );
      return Chimera::Status::OK;
    }
    else
    {
      return Chimera::Status::FAIL;
    }
  }


  Chimera::Status_t NetworkedSPI::readWriteBytes( const void *const txBuffer, void *const rxBuffer, const size_t length )
  {
    return this->doTransaction( txBuffer, rxBuffer, length, std::chrono::seconds( 10 ) );
  }
}    // namespace Chimera::SPI::SIM
