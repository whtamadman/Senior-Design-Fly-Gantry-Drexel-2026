// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace microscopy {

/**
 * Third party components of the microscope.
 */
class ThirdPartyComponents: public Serializable {
public:
    std::optional<int> autofocus;

    ThirdPartyComponents();

    ThirdPartyComponents(
        std::optional<int> p_autofocus
    );

    bool operator==(const ThirdPartyComponents& other) const;

    bool operator!=(const ThirdPartyComponents& other) const {
        return !(*this == other);
    }

    /**
     * Autofocus provider identifier.
     */
    std::optional<int> getAutofocus() const;
    void setAutofocus(std::optional<int> p_autofocus);

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

} // namespace microscopy
} // namespace motion
} // namespace zaber
