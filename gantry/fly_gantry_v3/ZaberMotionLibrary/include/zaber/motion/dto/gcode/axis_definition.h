// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace gcode {

/**
 * Defines an axis of the translator.
 */
class AxisDefinition: public Serializable {
public:
    int peripheralId {0};
    std::optional<int> microstepResolution;

    AxisDefinition();

    AxisDefinition(
        int p_peripheralId,
        std::optional<int> p_microstepResolution
    );

    AxisDefinition(
        int p_peripheralId
    );

    bool operator==(const AxisDefinition& other) const;

    bool operator!=(const AxisDefinition& other) const {
        return !(*this == other);
    }

    /**
     * ID of the peripheral.
     */
    int getPeripheralId() const;
    void setPeripheralId(int p_peripheralId);

    /**
     * Microstep resolution of the axis.
     * Can be obtained by reading the resolution setting.
     * Leave empty if the axis does not have the setting.
     */
    std::optional<int> getMicrostepResolution() const;
    void setMicrostepResolution(std::optional<int> p_microstepResolution);

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
