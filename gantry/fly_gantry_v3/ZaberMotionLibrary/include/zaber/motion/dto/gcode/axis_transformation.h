// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <optional>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace gcode {

/**
 * Represents a transformation of a translator axis.
 */
class AxisTransformation: public Serializable {
public:
    std::string axisLetter;
    std::optional<double> scaling;
    std::optional<Measurement> translation;

    AxisTransformation();

    AxisTransformation(
        std::string p_axisLetter,
        std::optional<double> p_scaling,
        std::optional<Measurement> p_translation
    );

    AxisTransformation(
        std::string p_axisLetter
    );

    bool operator==(const AxisTransformation& other) const;

    bool operator!=(const AxisTransformation& other) const {
        return !(*this == other);
    }

    /**
     * Letter of the translator axis (X,Y,Z,A,B,C,E).
     */
    std::string const& getAxisLetter() const;
    void setAxisLetter(std::string p_axisLetter);

    /**
     * Scaling factor.
     */
    std::optional<double> getScaling() const;
    void setScaling(std::optional<double> p_scaling);

    /**
     * Translation distance.
     */
    std::optional<Measurement> const& getTranslation() const;
    void setTranslation(std::optional<Measurement> p_translation);

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
