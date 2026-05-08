// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceGetSettingRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    std::string setting;
    Units unit {Units::NATIVE};

    DeviceGetSettingRequest();

    DeviceGetSettingRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        std::string p_setting,
        Units p_unit
    );

    bool operator==(const DeviceGetSettingRequest& other) const;

    bool operator!=(const DeviceGetSettingRequest& other) const {
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

    Units getUnit() const;
    void setUnit(Units p_unit);

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
