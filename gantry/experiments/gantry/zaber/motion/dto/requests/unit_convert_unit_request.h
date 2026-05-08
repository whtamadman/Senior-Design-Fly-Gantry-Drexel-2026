// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class UnitConvertUnitRequest: public Serializable {
public:
    double value {0.0};
    Units fromUnit {Units::NATIVE};
    Units toUnit {Units::NATIVE};

    UnitConvertUnitRequest();

    UnitConvertUnitRequest(
        double p_value,
        Units p_fromUnit,
        Units p_toUnit
    );

    bool operator==(const UnitConvertUnitRequest& other) const;

    bool operator!=(const UnitConvertUnitRequest& other) const {
        return !(*this == other);
    }

    double getValue() const;
    void setValue(double p_value);

    Units getFromUnit() const;
    void setFromUnit(Units p_fromUnit);

    Units getToUnit() const;
    void setToUnit(Units p_toUnit);

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
