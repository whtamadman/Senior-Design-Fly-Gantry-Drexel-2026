// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Represents a sequence of numerical values with optional units specified.
 */
class MeasurementSequence: public Serializable {
public:
    std::vector<double> values;
    std::optional<Units> unit;

    MeasurementSequence();

    MeasurementSequence(
        std::vector<double> p_values,
        std::optional<Units> p_unit
    );

    MeasurementSequence(
        std::vector<double> p_values
    );

    bool operator==(const MeasurementSequence& other) const;

    bool operator!=(const MeasurementSequence& other) const {
        return !(*this == other);
    }

    /**
     * Sequence of values.
     */
    std::vector<double> const& getValues() const;
    void setValues(std::vector<double> p_values);

    /**
     * Optional units of the sequence.
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

} // namespace ascii
} // namespace motion
} // namespace zaber
