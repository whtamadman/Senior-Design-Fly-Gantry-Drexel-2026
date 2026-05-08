// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include "zaber/motion/binary/device.h"
#include "zaber/motion/dto/binary/binary_settings.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace binary {


/**
 * Class providing access to various device settings and properties.
 */
class DeviceSettings {
public:
    DeviceSettings(Device device);

    /**
     * Returns any device setting or property.
     * @param setting Setting to get.
     * @param unit Units of setting.
     * @return Setting value.
     */
    double get(BinarySettings setting, Units unit = Units::NATIVE);
    /**
     * Sets any device setting.
     * @param setting Setting to set.
     * @param value Value of the setting.
     * @param unit Units of setting.
     */
    void set(BinarySettings setting, double value, Units unit = Units::NATIVE);
protected:
    Device getDevice() const;
    Device _device;
};


}  // Namespace binary
}  // Namespace motion
}  // Namespace zaber
