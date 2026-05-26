// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/get_setting.h"
#include "zaber/motion/dto/ascii/get_axis_setting.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceMultiGetSettingRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    std::vector<ascii::GetSetting> settings;
    std::vector<ascii::GetAxisSetting> axisSettings;

    DeviceMultiGetSettingRequest();

    DeviceMultiGetSettingRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        std::vector<ascii::GetSetting> p_settings,
        std::vector<ascii::GetAxisSetting> p_axisSettings
    );

    bool operator==(const DeviceMultiGetSettingRequest& other) const;

    bool operator!=(const DeviceMultiGetSettingRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    std::vector<ascii::GetSetting> const& getSettings() const;
    void setSettings(std::vector<ascii::GetSetting> p_settings);

    std::vector<ascii::GetAxisSetting> const& getAxisSettings() const;
    void setAxisSettings(std::vector<ascii::GetAxisSetting> p_axisSettings);

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
