// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/gcode/axis_mapping.h"
#include "zaber/motion/dto/gcode/axis_transformation.h"

namespace zaber {
namespace motion {
namespace gcode {

/**
 * Configuration of a translator.
 */
class TranslatorConfig: public Serializable {
public:
    std::vector<AxisMapping> axisMappings;
    std::vector<AxisTransformation> axisTransformations;

    TranslatorConfig();

    TranslatorConfig(
        std::vector<AxisMapping> p_axisMappings,
        std::vector<AxisTransformation> p_axisTransformations
    );

    bool operator==(const TranslatorConfig& other) const;

    bool operator!=(const TranslatorConfig& other) const {
        return !(*this == other);
    }

    /**
     * Optional custom mapping of translator axes to stream axes.
     */
    std::vector<AxisMapping> const& getAxisMappings() const;
    void setAxisMappings(std::vector<AxisMapping> p_axisMappings);

    /**
     * Optional transformation of axes.
     */
    std::vector<AxisTransformation> const& getAxisTransformations() const;
    void setAxisTransformations(std::vector<AxisTransformation> p_axisTransformations);

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
