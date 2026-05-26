// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * The response from a multi-get command.
 */
class GetSettingResult: public Serializable {
public:
    std::string setting;
    std::vector<double> values;
    Units unit {Units::NATIVE};

    GetSettingResult();

    GetSettingResult(
        std::string p_setting,
        std::vector<double> p_values,
        Units p_unit
    );

    bool operator==(const GetSettingResult& other) const;

    bool operator!=(const GetSettingResult& other) const {
        return !(*this == other);
    }

    /**
     * The setting read.
     */
    std::string const& getSetting() const;
    void setSetting(std::string p_setting);

    /**
     * The list of values returned.
     */
    std::vector<double> const& getValues() const;
    void setValues(std::vector<double> p_values);

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
