// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <optional>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Specifies a setting to get with one of the multi-get commands.
 */
class GetAxisSetting: public Serializable {
public:
    std::string setting;
    std::optional<Units> unit;

    GetAxisSetting();

    GetAxisSetting(
        std::string p_setting,
        std::optional<Units> p_unit
    );

    GetAxisSetting(
        std::string p_setting
    );

    bool operator==(const GetAxisSetting& other) const;

    bool operator!=(const GetAxisSetting& other) const {
        return !(*this == other);
    }

    /**
     * The setting to read.
     */
    std::string const& getSetting() const;
    void setSetting(std::string p_setting);

    /**
     * The unit to convert the read setting to.
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
