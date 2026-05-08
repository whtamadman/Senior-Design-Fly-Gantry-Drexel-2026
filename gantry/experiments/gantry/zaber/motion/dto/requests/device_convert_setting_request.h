// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceConvertSettingRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    std::string setting;
    Units unit {Units::NATIVE};
    double value {0.0};
    bool fromNative {false};

    DeviceConvertSettingRequest();

    DeviceConvertSettingRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        std::string p_setting,
        Units p_unit,
        double p_value,
        bool p_fromNative
    );

    bool operator==(const DeviceConvertSettingRequest& other) const;

    bool operator!=(const DeviceConvertSettingRequest& other) const {
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

    double getValue() const;
    void setValue(double p_value);

    bool getFromNative() const;
    void setFromNative(bool p_fromNative);

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
