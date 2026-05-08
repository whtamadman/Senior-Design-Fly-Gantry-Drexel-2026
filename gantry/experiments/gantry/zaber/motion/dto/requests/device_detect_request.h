// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/requests/device_type.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceDetectRequest: public Serializable {
public:
    int interfaceId {0};
    bool identifyDevices {false};
    DeviceType type {0};

    DeviceDetectRequest();

    DeviceDetectRequest(
        int p_interfaceId,
        bool p_identifyDevices,
        DeviceType p_type
    );

    bool operator==(const DeviceDetectRequest& other) const;

    bool operator!=(const DeviceDetectRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    bool getIdentifyDevices() const;
    void setIdentifyDevices(bool p_identifyDevices);

    DeviceType const& getType() const;
    void setType(DeviceType p_type);

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
