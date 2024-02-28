/******************************************************************************
 *  File Name:
 *    sim_chimera_sdio.cpp
 *
 *  Description:
 *    Simulator driver for the Chimera SDIO peripheral
 *
 *  2024 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#if defined( CHIMERA_SIMULATOR )

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Aurora/utility>
#include <Chimera/sdio>
#include <Chimera/peripheral>

namespace Chimera::SDIO
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static DeviceManager<Driver, Chimera::SDIO::Channel, EnumValue( Chimera::SDIO::Channel::NUM_OPTIONS )> s_raw_driver;

  /*---------------------------------------------------------------------------
  Driver Implementation
  ---------------------------------------------------------------------------*/
  Driver::Driver()
  {
  }


  Driver::~Driver()
  {
  }


  Chimera::Status_t Driver::open( const HWConfig &init )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::connect()
  {
    return Chimera::Status::OK;
  }


  void Driver::close()
  {
  }


  Chimera::Status_t Driver::writeBlock( const uint32_t blockAddress, const size_t blockCount, const void *const buffer )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::readBlock( const uint32_t blockAddress, const size_t blockCount, void *const buffer )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::eraseBlock( const uint32_t blockAddress, const size_t blockCount )
  {
    return Chimera::Status::OK;
  }


  CardState Driver::getCardState()
  {
    return CardState::CARD_READY;
  }


  Chimera::Status_t Driver::getCardStatus( CardStatus &status )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::getCardIdentity( CardIdentity &identity )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::getCardSpecificData( CardSpecificData &data )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::getCardInfo( CardInfo &info )
  {
    return Chimera::Status::OK;
  }


  namespace Backend
  {
    Chimera::Status_t initialize()
    {
      return Chimera::Status::OK;
    }


    Chimera::Status_t reset()
    {
      return Chimera::Status::OK;
    }


    Driver_rPtr getDriver( const Chimera::SDIO::Channel channel )
    {
      return s_raw_driver.getOrCreate( channel );
    }


    Chimera::Status_t registerDriver( Chimera::SDIO::Backend::DriverConfig &registry )
    {
      registry.isSupported = true;
      registry.getDriver   = ::Chimera::SDIO::Backend::getDriver;
      registry.initialize  = ::Chimera::SDIO::Backend::initialize;
      registry.reset       = ::Chimera::SDIO::Backend::reset;

      return Chimera::Status::OK;
    }
  }    // namespace Backend
}    // namespace Chimera::SDIO

#endif  /* CHIMERA_SIMULATOR */
