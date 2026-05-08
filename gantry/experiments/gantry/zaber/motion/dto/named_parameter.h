// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <optional>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {

/**
 * Named parameter with optional value.
 */
class NamedParameter: public Serializable {
public:
    std::string name;
    std::optional<double> value;

    NamedParameter();

    NamedParameter(
        std::string p_name,
        std::optional<double> p_value
    );

    NamedParameter(
        std::string p_name
    );

    bool operator==(const NamedParameter& other) const;

    bool operator!=(const NamedParameter& other) const {
        return !(*this == other);
    }

    /**
     * Name of the parameter.
     */
    std::string const& getName() const;
    void setName(std::string p_name);

    /**
     * Optional value of the parameter.
     */
    std::optional<double> getValue() const;
    void setValue(std::optional<double> p_value);

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
