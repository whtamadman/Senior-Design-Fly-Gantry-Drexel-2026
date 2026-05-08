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
 * The response from a multi-get axis command.
 */
class GetAxisSettingResult: public Serializable {
public:
    std::string setting;
    double value {0.0};
    Units unit {Units::NATIVE};

    GetAxisSettingResult();

    GetAxisSettingResult(
        std::string p_setting,
        double p_value,
        Units p_unit
    );

    bool operator==(const GetAxisSettingResult& other) const;

    bool operator!=(const GetAxisSettingResult& other) const {
        return !(*this == other);
    }

    /**
     * The setting read.
     */
    std::string const& getSetting() const;
    void setSetting(std::string p_setting);

    /**
     * The value read.
     */
    double getValue() const;
    void setValue(double p_value);

    /**
     * The unit of the values.
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
