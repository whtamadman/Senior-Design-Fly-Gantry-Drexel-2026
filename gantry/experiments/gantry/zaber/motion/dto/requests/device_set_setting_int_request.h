// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <cstdint>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceSetSettingIntRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    std::string setting;
    int64_t value {0};

    DeviceSetSettingIntRequest();

    DeviceSetSettingIntRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        std::string p_setting,
        int64_t p_value
    );

    bool operator==(const DeviceSetSettingIntRequest& other) const;

    bool operator!=(const DeviceSetSettingIntRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    std::string const& getSetting() const;
    void setSetting(std::string p_setting);

    int64_t getValue() const;
    void setValue(int64_t p_value);

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
