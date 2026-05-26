// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/binary/binary_settings.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class BinaryDeviceGetSettingRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    binary::BinarySettings setting {0};
    Units unit {Units::NATIVE};

    BinaryDeviceGetSettingRequest();

    BinaryDeviceGetSettingRequest(
        int p_interfaceId,
        int p_device,
        binary::BinarySettings p_setting,
        Units p_unit
    );

    bool operator==(const BinaryDeviceGetSettingRequest& other) const;

    bool operator!=(const BinaryDeviceGetSettingRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    binary::BinarySettings const& getSetting() const;
    void setSetting(binary::BinarySettings p_setting);

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
