// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/firmware_version.h"
#include "zaber/motion/dto/binary/device_type.h"

namespace zaber {
namespace motion {
namespace binary {

/**
 * Representation of data gathered during device identification.
 */
class DeviceIdentity: public Serializable {
public:
    int deviceId {0};
    unsigned int serialNumber {0};
    std::string name;
    FirmwareVersion firmwareVersion;
    bool isPeripheral {false};
    int peripheralId {0};
    std::string peripheralName;
    DeviceType deviceType {0};

    DeviceIdentity();

    DeviceIdentity(
        int p_deviceId,
        unsigned int p_serialNumber,
        std::string p_name,
        FirmwareVersion p_firmwareVersion,
        bool p_isPeripheral,
        int p_peripheralId,
        std::string p_peripheralName,
        DeviceType p_deviceType
    );

    bool operator==(const DeviceIdentity& other) const;

    bool operator!=(const DeviceIdentity& other) const {
        return !(*this == other);
    }

    /**
     * Unique ID of the device hardware.
     */
    int getDeviceId() const;
    void setDeviceId(int p_deviceId);

    /**
     * Serial number of the device.
     * Requires at least Firmware 6.15 for devices or 6.24 for peripherals.
     */
    unsigned int getSerialNumber() const;
    void setSerialNumber(unsigned int p_serialNumber);

    /**
     * Name of the product.
     */
    std::string const& getName() const;
    void setName(std::string p_name);

    /**
     * Version of the firmware.
     */
    FirmwareVersion const& getFirmwareVersion() const;
    void setFirmwareVersion(FirmwareVersion p_firmwareVersion);

    /**
     * Indicates whether the device is a peripheral or part of an integrated device.
     */
    bool getIsPeripheral() const;
    void setIsPeripheral(bool p_isPeripheral);

    /**
     * Unique ID of the peripheral hardware.
     */
    int getPeripheralId() const;
    void setPeripheralId(int p_peripheralId);

    /**
     * Name of the peripheral hardware.
     */
    std::string const& getPeripheralName() const;
    void setPeripheralName(std::string p_peripheralName);

    /**
     * Determines the type of an device and units it accepts.
     */
    DeviceType const& getDeviceType() const;
    void setDeviceType(DeviceType p_deviceType);

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

} // namespace binary
} // namespace motion
} // namespace zaber
