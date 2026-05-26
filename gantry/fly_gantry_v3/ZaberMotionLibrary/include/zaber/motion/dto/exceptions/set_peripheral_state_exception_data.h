// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Contains additional data for a SetPeripheralStateFailedException.
 */
class SetPeripheralStateExceptionData: public Serializable {
public:
    int axisNumber {0};
    std::vector<std::string> settings;
    std::string servoTuning;
    std::vector<std::string> storedPositions;
    std::vector<std::string> storage;

    SetPeripheralStateExceptionData();

    SetPeripheralStateExceptionData(
        int p_axisNumber,
        std::vector<std::string> p_settings,
        std::string p_servoTuning,
        std::vector<std::string> p_storedPositions,
        std::vector<std::string> p_storage
    );

    bool operator==(const SetPeripheralStateExceptionData& other) const;

    bool operator!=(const SetPeripheralStateExceptionData& other) const {
        return !(*this == other);
    }

    /**
     * The number of axis where the exception originated.
     */
    int getAxisNumber() const;
    void setAxisNumber(int p_axisNumber);

    /**
     * A list of settings which could not be set.
     */
    std::vector<std::string> const& getSettings() const;
    void setSettings(std::vector<std::string> p_settings);

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
