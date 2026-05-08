// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/requests/test_variant.h"

namespace zaber {
namespace motion {
namespace requests {

/**
 * A test DTO that includes variant types.
 * This is used to verify the correct handling of variant types as members of other DTO types.
 */
class TestDtoWithVariants: public Serializable {
public:
    std::optional<TestVariant> theVariant;
    std::vector<TestVariant> variantArray;

    TestDtoWithVariants();

    TestDtoWithVariants(
        std::optional<TestVariant> p_theVariant,
        std::vector<TestVariant> p_variantArray
    );

    TestDtoWithVariants(
        std::vector<TestVariant> p_variantArray
    );

    bool operator==(const TestDtoWithVariants& other) const;

    bool operator!=(const TestDtoWithVariants& other) const {
        return !(*this == other);
    }

    /**
     * Single variant instance.
     */
    std::optional<TestVariant> const& getTheVariant() const;
    void setTheVariant(std::optional<TestVariant> p_theVariant);

    /**
     * Array of variants.
     */
    std::vector<TestVariant> const& getVariantArray() const;
    void setVariantArray(std::vector<TestVariant> p_variantArray);

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
