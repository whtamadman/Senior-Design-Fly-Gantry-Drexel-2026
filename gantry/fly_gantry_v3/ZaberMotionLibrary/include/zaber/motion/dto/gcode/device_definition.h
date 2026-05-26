// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/gcode/axis_definition.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace gcode {

/**
 * Holds information about device and its axes for purpose of a translator.
 */
class DeviceDefinition: public Serializable {
public:
    int deviceId {0};
    std::vector<AxisDefinition> axes;
    Measurement maxSpeed;

    DeviceDefinition();

    DeviceDefinition(
        int p_deviceId,
        std::vector<AxisDefinition> p_axes,
        Measurement p_maxSpeed
    );

    bool operator==(const DeviceDefinition& other) const;

    bool operator!=(const DeviceDefinition& other) const {
        return !(*this == other);
    }

    /**
     * Device ID of the controller.
     * Can be obtained from device settings.
     */
    int getDeviceId() const;
    void setDeviceId(int p_deviceId);

    /**
     * Applicable axes of the device.
     */
    std::vector<AxisDefinition> const& getAxes() const;
    void setAxes(std::vector<AxisDefinition> p_axes);

    /**
     * The smallest of each axis' maxspeed setting value.
     * This value becomes the traverse rate of the translator.
     */
    Measurement const& getMaxSpeed() const;
    void setMaxSpeed(Measurement p_maxSpeed);

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

} // namespace gcode
} // namespace motion
} // namespace zaber
