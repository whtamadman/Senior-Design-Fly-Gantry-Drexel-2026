// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Definition of a mock peripheral.
 */
class MockPeripheral: public Serializable {
public:
    int peripheralId {0};
    std::optional<bool> isModified;
    std::optional<int> resolution;

    MockPeripheral();

    MockPeripheral(
        int p_peripheralId,
        std::optional<bool> p_isModified,
        std::optional<int> p_resolution
    );

    MockPeripheral(
        int p_peripheralId
    );

    bool operator==(const MockPeripheral& other) const;

    bool operator!=(const MockPeripheral& other) const {
        return !(*this == other);
    }

    /**
     * A valid Zaber peripheral ID.
     */
    int getPeripheralId() const;
    void setPeripheralId(int p_peripheralId);

    /**
     * The peripheral has hardware modifications. Defaults to false.
     */
    std::optional<bool> getIsModified() const;
    void setIsModified(std::optional<bool> p_isModified);

    /**
     * The number of microsteps per full step for peripheral. Defaults to device database default.
     */
    std::optional<int> getResolution() const;
    void setResolution(std::optional<int> p_resolution);

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

} // namespace ascii
} // namespace motion
} // namespace zaber
