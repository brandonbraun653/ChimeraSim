/******************************************************************************
 *  File Name:
 *    sim_i2c_driver.cpp
 *
 *  Description:
 *    I2C Simulator
 *
 *  2022 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Aurora/logging>
#include <Chimera/assert>
#include <Chimera/i2c>
#include <Chimera/peripheral>
#include <ChimeraSim/i2c>
#include <ChimeraSim/source/shared/common_types.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>

namespace Chimera::I2C
{
  /*---------------------------------------------------------------------------
  Structures
  ---------------------------------------------------------------------------*/
  struct SimData
  {
    Chimera::I2C::DriverConfig cfg;
  };

  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static DeviceManager<Driver, Channel, EnumValue( Channel::NUM_OPTIONS )> s_raw_driver;
  static DeviceManager<SimData, Channel, EnumValue( Channel::NUM_OPTIONS )> s_impl_driver;

  /*---------------------------------------------------------------------------
  Static Functions
  ---------------------------------------------------------------------------*/
  static Chimera::Status_t impl_initialize()
  {
    return Chimera::Status::OK;
  }


  static Chimera::Status_t impl_reset()
  {
    return Chimera::Status::OK;
  }


  static Driver_rPtr impl_getDriver( const Chimera::I2C::Channel channel )
  {
    return s_raw_driver.getOrCreate( channel );
  }

  namespace Backend
  {
    Chimera::Status_t registerDriver( Chimera::I2C::Backend::DriverConfig &registry )
    {
      registry.isSupported = true;
      registry.getDriver   = ::Chimera::I2C::impl_getDriver;
      registry.initialize  = ::Chimera::I2C::impl_initialize;
      registry.reset       = ::Chimera::I2C::impl_reset;
      return Chimera::Status::OK;
    }
  }    // namespace Backend


  /*---------------------------------------------------------------------------
  Driver Implementation
  ---------------------------------------------------------------------------*/
  Driver::Driver()
  {
  }


  Driver::~Driver()
  {
  }


  Chimera::Status_t Driver::open( const DriverConfig &cfg )
  {
    /*-------------------------------------------------------------------------
    Ensure the AsyncIO driver is ready
    -------------------------------------------------------------------------*/
    this->initAIO();

    /*-------------------------------------------------------------------------
    Map the implementation details
    -------------------------------------------------------------------------*/
    auto pImpl = s_impl_driver.getOrCreate( cfg.HWInit.channel );
    RT_HARD_ASSERT( pImpl );

    pImpl->cfg = cfg;
    mImpl = reinterpret_cast<void*>( pImpl );

    /*-------------------------------------------------------------------------
    Ensure the backing file exists with the expected properties
    -------------------------------------------------------------------------*/
    bool create = true;

    if ( std::filesystem::exists( cfg.memFile ) )
    {
      const size_t size = std::filesystem::file_size( cfg.memFile );
      if ( cfg.memSize != size )
      {
        LOG_ERROR( "File size didn't match [%d != %d]. Destroying %s\r\n",
                   cfg.memSize, size, cfg.memFile.c_str() );
        std::filesystem::remove( cfg.memFile );
      }
      else
      {
        create = false;
      }
    }

    if ( create )
    {
      /*-----------------------------------------------------------------------
      Create the parent directories
      -----------------------------------------------------------------------*/
      auto parent_dir = cfg.memFile.parent_path();
      std::filesystem::create_directories( parent_dir );
      assert( std::filesystem::exists( parent_dir ) );

      /*-----------------------------------------------------------------------
      Fill the file with empty NOR memory all the way up to the device size
      -----------------------------------------------------------------------*/
      std::ofstream file;
      file.open( cfg.memFile, std::ios::app | std::ios::binary );

      uint8_t data = 0xff;
      for ( size_t idx = 0; idx < cfg.memSize; idx++ )
      {
        file.write( reinterpret_cast<const char *>( &data ), sizeof( data ) );
      }

      file.close();
    }

    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::close()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::read( const uint16_t address, void *const data, const size_t length )
  {
    return transfer( address, nullptr, data, length );
  }


  Chimera::Status_t Driver::write( const uint16_t address, const void *const data, const size_t length )
  {
    return transfer( address, data, nullptr, length );
  }


  Chimera::Status_t Driver::transfer( const uint16_t address, const void *const tx_data, void *const rx_data,
                                      const size_t length )
  {
    RT_HARD_ASSERT( mImpl );
    SimData *pImpl = reinterpret_cast<SimData *>( mImpl );
    auto result    = Chimera::Status::OK;

    /*-------------------------------------------------------------------------
    Write to the file
    -------------------------------------------------------------------------*/
    if( tx_data && length )
    {
      FILE *file = ::fopen( pImpl->cfg.memFile.c_str(), "rb+" );
      ::fseek( file, address, SEEK_SET );

      size_t bytes_written = ::fwrite( tx_data, 1, length, file );

      ::fflush( file );
      ::fclose( file );

      if ( bytes_written != length )
      {
        LOG_TRACE( "Error writing to file: %d\r\n" );
        result = Chimera::Status::FAILED_WRITE;
      }
    }

    /*-------------------------------------------------------------------------
    Read from the file
    -------------------------------------------------------------------------*/
    if( rx_data && length )
    {
      FILE *file = ::fopen( pImpl->cfg.memFile.c_str(), "rb" );
      RT_HARD_ASSERT( file );

      ::fseek( file, address, SEEK_SET );
      RT_HARD_ASSERT( ::ftell( file ) == address );

      size_t bytes_read = ::fread( rx_data, 1, length, file );
      ::fclose( file );

      if ( bytes_read != length )
      {
        LOG_TRACE( "Error reading from file: %d\r\n" );
        result = Chimera::Status::FAILED_READ;
      }
    }

    this->signalAIO( Chimera::Event::Trigger::TRIGGER_TRANSFER_COMPLETE );
    return result;
  }


  Chimera::Status_t Driver::stop()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::start()
  {
    return Chimera::Status::OK;
  }

}    // namespace Chimera::I2C
