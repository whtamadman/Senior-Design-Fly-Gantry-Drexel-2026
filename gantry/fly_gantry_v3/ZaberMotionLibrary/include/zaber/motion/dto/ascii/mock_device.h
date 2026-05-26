// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/firmware_version.h"
#include "zaber/motion/dto/ascii/mock_peripheral.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Definition of a mock device.
 */
class MockDevice: public Serializable {
public:
    int deviceId {0};
    std::optional<FirmwareVersion> firmwareVersion;
    std::optional<bool> isModified;
    std::optional<int> resolution;
    std::vector<MockPeripheral> peripherals;

    MockDevice();

    MockDevice(
        int p_deviceId,
        std::optional<FirmwareVersion> p_firmwareVersion,
        std::optional<bool> p_isModified,
        std::optional<int> p_resolution,
        std::vector<MockPeripheral> p_peripherals
    );

    MockDevice(
        int p_deviceId
    );

    bool operator==(const MockDevice& other) const;

    bool operator!=(const MockDevice& other) const {
        return !(*this == other);
    }

    /**
     * A valid Zaber device ID.
     */
    int getDeviceId() const;
    void setDeviceId(int p_deviceId);

    /**
     * Version of the firmware. Defaults to device database latest. To omit minor or build version, set them to -1.
     */
    std::optional<FirmwareVersion> const& getFirmwareVersion() const;
    void setFirmwareVersion(std::optional<FirmwareVersion> p_firmwareVersion);

    /**
     * The device has hardware modifications. Defaults to false.
     */
    std::optional<bool> getIsModified() const;
    void setIsModified(std::optional<bool> p_isModified);

    /**
     * The number of microsteps per full step for integrated devices. Defaults to device database default.
     */
    std::optional<int> getResolution() const;
    void setResolution(std::optional<int> p_resolution);

    /**
     * List of mock peripherals connected to the device.
     */
    std::vector<MockPeripheral> const& getPeripherals() const;
    void setPeripherals(std::vector<MockPeripheral> p_peripherals);

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
