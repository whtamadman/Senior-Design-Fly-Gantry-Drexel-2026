// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/firmware_version.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceIdentifyRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    std::optional<FirmwareVersion> assumeVersion;

    DeviceIdentifyRequest();

    DeviceIdentifyRequest(
        int p_interfaceId,
        int p_device,
        std::optional<FirmwareVersion> p_assumeVersion
    );

    DeviceIdentifyRequest(
        int p_interfaceId,
        int p_device
    );

    bool operator==(const DeviceIdentifyRequest& other) const;

    bool operator!=(const DeviceIdentifyRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    std::optional<FirmwareVersion> const& getAssumeVersion() const;
    void setAssumeVersion(std::optional<FirmwareVersion> p_assumeVersion);

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

} // namespace requests
} // namespace motion
} // namespace zaber
