// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/firmware_version.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Representation of data gathered during device identification.
 */
class DeviceIdentity: public Serializable {
public:
    int deviceId {0};
    unsigned int serialNumber {0};
    std::string name;
    int axisCount {0};
    FirmwareVersion firmwareVersion;
    bool isModified {false};
    bool isIntegrated {false};

    DeviceIdentity();

    DeviceIdentity(
        int p_deviceId,
        unsigned int p_serialNumber,
        std::string p_name,
        int p_axisCount,
        FirmwareVersion p_firmwareVersion,
        bool p_isModified,
        bool p_isIntegrated
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
     */
    unsigned int getSerialNumber() const;
    void setSerialNumber(unsigned int p_serialNumber);

    /**
     * Name of the product.
     */
    std::string const& getName() const;
    void setName(std::string p_name);

    /**
     * Number of axes this device has.
     */
    int getAxisCount() const;
    void setAxisCount(int p_axisCount);

    /**
     * Version of the firmware.
     */
    FirmwareVersion const& getFirmwareVersion() const;
    void setFirmwareVersion(FirmwareVersion p_firmwareVersion);

    /**
     * The device has hardware modifications.
     */
    bool getIsModified() const;
    void setIsModified(bool p_isModified);

    /**
     * The device is an integrated product.
     */
    bool getIsIntegrated() const;
    void setIsIntegrated(bool p_isIntegrated);

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
