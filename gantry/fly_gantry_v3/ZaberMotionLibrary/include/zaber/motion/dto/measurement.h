// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {

/**
 * Represents a numerical value with optional units specified.
 */
class Measurement: public Serializable {
public:
    double value {0.0};
    std::optional<Units> unit;

    Measurement();

    Measurement(
        double p_value,
        std::optional<Units> p_unit
    );

    Measurement(
        double p_value
    );

    bool operator==(const Measurement& other) const;

    bool operator!=(const Measurement& other) const {
        return !(*this == other);
    }

    /**
     * Value of the measurement.
     */
    double getValue() const;
    void setValue(double p_value);

    /**
     * Optional units of the measurement.
     */
    std::optional<Units> getUnit() const;
    void setUnit(std::optional<Units> p_unit);

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

} // namespace motion
} // namespace zaber
