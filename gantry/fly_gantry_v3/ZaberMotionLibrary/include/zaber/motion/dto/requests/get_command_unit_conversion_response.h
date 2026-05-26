// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/unit_conversion_descriptor.h"

namespace zaber {
namespace motion {
namespace requests {

class GetCommandUnitConversionResponse: public Serializable {
public:
    std::vector<std::optional<UnitConversionDescriptor>> value;

    GetCommandUnitConversionResponse();

    GetCommandUnitConversionResponse(
        std::vector<std::optional<UnitConversionDescriptor>> p_value
    );

    bool operator==(const GetCommandUnitConversionResponse& other) const;

    bool operator!=(const GetCommandUnitConversionResponse& other) const {
        return !(*this == other);
    }

    std::vector<std::optional<UnitConversionDescriptor>> const& getValue() const;
    void setValue(std::vector<std::optional<UnitConversionDescriptor>> p_value);

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
