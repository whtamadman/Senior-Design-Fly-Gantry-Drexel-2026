// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/exceptions/set_peripheral_state_exception_data.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Contains additional data for a SetDeviceStateFailedException.
 */
class SetDeviceStateExceptionData: public Serializable {
public:
    std::vector<std::string> settings;
    std::vector<std::string> streamBuffers;
    std::vector<std::string> pvtBuffers;
    std::vector<std::string> triggers;
    std::string servoTuning;
    std::vector<std::string> storedPositions;
    std::vector<std::string> storage;
    std::vector<SetPeripheralStateExceptionData> peripherals;

    SetDeviceStateExceptionData();

    SetDeviceStateExceptionData(
        std::vector<std::string> p_settings,
        std::vector<std::string> p_streamBuffers,
        std::vector<std::string> p_pvtBuffers,
        std::vector<std::string> p_triggers,
        std::string p_servoTuning,
        std::vector<std::string> p_storedPositions,
        std::vector<std::string> p_storage,
        std::vector<SetPeripheralStateExceptionData> p_peripherals
    );

    bool operator==(const SetDeviceStateExceptionData& other) const;

    bool operator!=(const SetDeviceStateExceptionData& other) const {
        return !(*this == other);
    }

    /**
     * A list of settings which could not be set.
     */
    std::vector<std::string> const& getSettings() const;
    void setSettings(std::vector<std::string> p_settings);

    /**
     * The reason the stream buffers could not be set.
     */
    std::vector<std::string> const& getStreamBuffers() const;
    void setStreamBuffers(std::vector<std::string> p_streamBuffers);

    /**
     * The reason the pvt buffers could not be set.
     */
    std::vector<std::string> const& getPvtBuffers() const;
    void setPvtBuffers(std::vector<std::string> p_pvtBuffers);

    /**
     * The reason the triggers could not be set.
     */
    std::vector<std::string> const& getTriggers() const;
    void setTriggers(std::vector<std::string> p_triggers);

    /**
     * The reason servo tuning could not be set.
     */
    std::string const& getServoTuning() const;
    void setServoTuning(std::string p_servoTuning);

    /**
     * The reasons stored positions could not be set.
     */
    std::vector<std::string> const& getStoredPositions() const;
    void setStoredPositions(std::vector<std::string> p_storedPositions);

    /**
     * The reasons storage could not be set.
     */
    std::vector<std::string> const& getStorage() const;
    void setStorage(std::vector<std::string> p_storage);

    /**
     * Errors for any peripherals that could not be set.
     */
    std::vector<SetPeripheralStateExceptionData> const& getPeripherals() const;
    void setPeripherals(std::vector<SetPeripheralStateExceptionData> p_peripherals);

    /**
     * Convert object to human-readable string format
     */
    std::string toString() const;

#ifdef ZML_SERIALIZATION_PUBLIC
public:
#else
private:
#endif

    std::string toByteArray() const override;
    void populateFromByteArray(const std::string& buffer) override;

};

} // namespace exceptions
} // namespace motion
} // namespace zaber
