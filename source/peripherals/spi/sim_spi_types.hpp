/********************************************************************************
 *  File Name:
 *    sim_spi_types.hpp
 *
 *  Description:
 *    Configuration options and types for the sim driver
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_SIM_SPI_DETAIL_HPP
#define CHIMERA_SIM_SPI_DETAIL_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <cstddef>
#include <mutex>
#include <Chimera/spi>

namespace Chimera::SPI::Sim
{
  /*---------------------------------------------------------------------------
  Structures
  ---------------------------------------------------------------------------*/
  /**
   *  Tracks the simulated state of the virtual SPI device
   */
  struct VirtualState
  {
    std::recursive_timed_mutex mtx; /**< Driver lock */
    DriverConfig config;            /**< SPI configuration */
    size_t clockFrequency;          /**< Current clock speed */
    Chimera::Hardware::PeripheralMode periphMode;
  };

  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  /**
   *  Basic SPI implementation that mimics a working driver with no fancy add-ons
   */
  class BasicSPI : public Chimera::Thread::AsyncIO<BasicSPI>,
                   public Chimera::Thread::Lockable<BasicSPI>,
                   public virtual Chimera::SPI::ISPI
  {
  public:
    using Chimera::Thread::AsyncIO<BasicSPI>::AsyncIO;

    virtual Chimera::Status_t init( const Chimera::SPI::DriverConfig &setupStruct ) override;
    virtual Chimera::Status_t deInit() override;
    virtual Chimera::Status_t assignChipSelect( const Chimera::GPIO::Driver_rPtr cs ) override;
    virtual Chimera::Status_t setChipSelect( const Chimera::GPIO::State value ) override;
    virtual Chimera::Status_t setChipSelectControlMode( const Chimera::SPI::CSMode mode ) override;
    virtual Chimera::Status_t writeBytes( const void *const txBuffer, const size_t length ) override;
    virtual Chimera::Status_t readBytes( void *const rxBuffer, const size_t length ) override;
    virtual Chimera::Status_t readWriteBytes( const void *const txBuffer, void *const rxBuffer, const size_t length ) override;
    virtual Chimera::Status_t setPeripheralMode( const Chimera::Hardware::PeripheralMode mode ) override;
    virtual Chimera::Status_t setClockFrequency( const size_t freq, const size_t tolerance ) override;
    virtual Chimera::SPI::HardwareInit getInit() override;
    virtual size_t getClockFrequency() override;

  protected:
    friend Chimera::Thread::Lockable<BasicSPI>;
    friend Chimera::Thread::AsyncIO<BasicSPI>;

    VirtualState mHWState;
  };

  /*---------------------------------------------------------------------------
  Constants
  ---------------------------------------------------------------------------*/
  static constexpr size_t NUM_DRIVERS = static_cast<size_t>( Chimera::SPI::Channel::NUM_OPTIONS );

}    // namespace Chimera::SPI::Sim

#endif /* !CHIMERA_SIM_SPI_DETAIL_HPP */
