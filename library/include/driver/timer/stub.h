/**
 * @brief Timer stub.
 */
#pragma once

#include <stdint.h>

#include "driver/timer/interface.h"

namespace driver
{
namespace timer
{
/**
 * @brief Timer stub.
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
        : myInitialized{true}
        , myEnabled{false}
        , myTimedOut{false}
        , myTimeout_ms{1000U}
    {}
    
    /**
     * @brief Destructor.
     */
    ~Stub() noexcept override = default;

    /**
     * @brief Check if the timer is initialized.
     * 
     *        An uninitialized timer indicates that no timer circuit was available when the timer 
     *        was created.
     * 
     * @return True if the timer is initialized, false otherwise.
     */
    bool isInitialized() const noexcept override { return myInitialized; }

    /**
     * @brief Check whether the timer is enabled.
     *
     * @return True if the timer is enabled, false otherwise.
     */
    bool isEnabled() const noexcept override { return myEnabled; }

    /**
     * @brief Check whether the timer has timed out.
     *
     * @return True if the timer has timed out, false otherwise.
     */
    bool hasTimedOut() const noexcept override { return myTimedOut; }

    /**
     * @brief Get the timeout of the timer.
     * 
     * @return The timeout in milliseconds.
     */
    uint32_t timeout_ms() const noexcept override { return myTimeout_ms; }

    /**
     * @brief Set timeout of the timer.
     * 
     * @param[in] timeout_ms The new timeout in milliseconds.
     */
    void setTimeout_ms(uint32_t timeout_ms) noexcept override
    {
        // Only update the timeout if the device is initialized.
        if (myInitialized) { myTimeout_ms = timeout_ms; }
    }

    /**
     * @brief Start the timer.
     */
    void start() noexcept override
    {
        // Only enable the timer if the device is initialized.
        if (myInitialized) { myEnabled = true; }
    }

    /**
     * @brief Stop the timer.
     */
    void stop() noexcept override
    {
        // Only disable the timer if the device is initialized.
        if (myInitialized) { myEnabled = false; }
    }

    /**
     * @brief Toggle the timer.
     */
    void toggle() noexcept override
    {
        // Only toggle the timer if the device is initialized.
        if (myInitialized) { myEnabled = !myEnabled; }
    }

    /**
     * @brief Restart the timer.
     */
    void restart() noexcept override
    {
        // Only restart the timer if the device is initialized.
        if (myInitialized) { myTimedOut = false; }
    }

    /**
     * @brief Set timer initialization state.
     * 
     *        The timer is disabled automatically if the timer is set to unitialized.
     * 
     * @param[in] initialized True to set the timer to initialized, otherwise false.
     */
    void setInitialized(bool initialized) noexcept
    {
        myInitialized = initialized;

        // Disable the timer if unitialized.
        if (!myInitialized)
        {
            myEnabled  = false;
            myTimedOut = false;
            myTimedOut = 0;
        }
    }

    /**
     * @brief Set timeout state.
     * 
     * @param[in] timedOut True if the timer has timed out, otherwise false.
     */
    void setTimedOut(bool timedOut) noexcept
    {
        // Only set the timeout state if the device is initialized and running.
        if (myInitialized && myEnabled) { myTimedOut = timedOut; }
    }

    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // No move assignment.

private:
    /** Timer initialization state (true = initialized) */
    bool myInitialized;

    /** Timer enablement state (true = enabled) */
    bool myEnabled;

    /** Timer timeout state (true = timed out) */
    bool myTimedOut;

    /** Timer timeout in milliseconds */
    uint32_t myTimeout_ms;
};
} // namespace timer
} // namespace driver
