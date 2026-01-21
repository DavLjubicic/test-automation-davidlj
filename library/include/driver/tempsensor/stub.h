/**
 * @brief Temperature sensor stub.
 */
#pragma once

#include <stdint.h>

#include "driver/tempsensor/interface.h"

namespace driver
{
namespace tempsensor
{
/**
 * @brief Temperature sensor stub.
 * 
 *       This class is non-copyable and non-movable.
 */
class Stub final : public Interface
{
public:
    /**
     * @brief Constructor.
     */
    Stub() noexcept
        : myTemp{0}
        , myInitialized{true}
    {}
    
    /**
     * @brief Destructor.
     */
    ~Stub() noexcept override = default;

    /**
     * @brief Check if the temperature sensor is initialized.
     * 
     * @return True if the temperature sensor is initialized, false otherwise.
     */
    bool isInitialized() const noexcept override { return myInitialized; }

    /**
     * @brief Read the temperature sensor.
     *
     * @return The temperature in degrees Celsius.
     */
    int16_t read() const noexcept override { return myTemp; }

    /**
     * @brief Set initialization status.
     * 
     *        The temperature is set to 0 if the device is set to uninitialized.
     * 
     * @param[in] initialized Tempsensor initialization state (true = initialized).
     */
    void setInitialized(bool initialized) noexcept
    {
        myInitialized = initialized;

        // Reset the temperature to 0 if the device is uninitialized.
        if (!myInitialized) { myTemp = 0; }
    }

    /**
     * @brief Simulate temperature to read from the temp sensor.
     * 
     *        The value is only read if the device is initialized.
     * 
     * @param[in] temp Temperature value.
     */
    void setTemp(int16_t temp) noexcept
    {
        // Set the temperature if the device is initialized.
        if (myInitialized) { myTemp = temp; }
    }

    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // No move assignment.

private:
    /** Simulated temperature. */
    int16_t myTemp;

    /** Temperature sensor initialization state (true = initialized) */
    bool myInitialized;
};
} // namespace tempsensor
} // namespace driver