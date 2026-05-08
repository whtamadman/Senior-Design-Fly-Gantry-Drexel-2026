// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Represents unit conversion factor for a single dimension.
 */
class ConversionFactor: public Serializable {
public:
    std::string setting;
    double value {0.0};
    Units unit {Units::NATIVE};

    ConversionFactor();

    ConversionFactor(
        std::string p_setting,
        double p_value,
        Units p_unit
    );

    bool operator==(const ConversionFactor& other) const;

    bool operator!=(const ConversionFactor& other) const {
        return !(*this == other);
    }

    /**
     * Setting representing the dimension.
     */
    std::string const& getSetting() const;
    void setSetting(std::string p_setting);

    /**
     * Value representing 1 native device unit in specified real-word units.
     */
    double getValue() const;
    void setValue(double p_value);

    /**
     * Units of the value.
     */
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

} // namespace ascii
} // namespace motion
} // namespace zaber
