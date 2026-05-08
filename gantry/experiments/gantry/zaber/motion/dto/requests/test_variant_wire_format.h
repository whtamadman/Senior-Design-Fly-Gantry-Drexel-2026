// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/requests/test_variant.h"

namespace zaber {
namespace motion {
namespace requests {

/**
 * Serialization wrapper for the TestVariant variant. Not part of the public API.
 */
class TestVariantWireFormat: public Serializable {
public:
    std::string variantValueType;
    std::optional<ascii::AxisType> axisTypeValue;
    std::optional<ascii::IoPortLabel> ioPortLabelValue;
    std::optional<int> int32Value;
    std::optional<double> optionalDoubleValue;
    std::optional<std::vector<std::string>> stringArrayValue;

    TestVariantWireFormat() = default;
    TestVariantWireFormat(const TestVariant& value);

    TestVariant convertBack() const;

    bool operator==(const TestVariantWireFormat& other) const;

    bool operator!=(const TestVariantWireFormat& other) const {
        return !(*this == other);
    }

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
