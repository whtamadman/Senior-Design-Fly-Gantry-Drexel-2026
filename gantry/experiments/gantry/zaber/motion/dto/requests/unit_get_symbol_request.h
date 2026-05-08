// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class UnitGetSymbolRequest: public Serializable {
public:
    Units unit {Units::NATIVE};

    UnitGetSymbolRequest();

    UnitGetSymbolRequest(
        Units p_unit
    );

    bool operator==(const UnitGetSymbolRequest& other) const;

    bool operator!=(const UnitGetSymbolRequest& other) const {
        return !(*this == other);
    }

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

} // namespace requests
} // namespace motion
} // namespace zaber
