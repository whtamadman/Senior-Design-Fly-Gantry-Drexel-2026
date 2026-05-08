// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"
#include "zaber/motion/dto/unit_conversion_descriptor.h"

namespace zaber {
namespace motion {
namespace requests {

class UnitConvertNativeRequest: public Serializable {
public:
    double value {0.0};
    std::vector<double> values;
    Units unit {Units::NATIVE};
    UnitConversionDescriptor conversion;

    UnitConvertNativeRequest();

    UnitConvertNativeRequest(
        double p_value,
        std::vector<double> p_values,
        Units p_unit,
        UnitConversionDescriptor p_conversion
    );

    bool operator==(const UnitConvertNativeRequest& other) const;

    bool operator!=(const UnitConvertNativeRequest& other) const {
        return !(*this == other);
    }

    double getValue() const;
    void setValue(double p_value);

    std::vector<double> const& getValues() const;
    void setValues(std::vector<double> p_values);

    Units getUnit() const;
    void setUnit(Units p_unit);

    UnitConversionDescriptor const& getConversion() const;
    void setConversion(UnitConversionDescriptor p_conversion);

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
