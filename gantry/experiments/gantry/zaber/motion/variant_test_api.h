// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/dto/requests/test_variant.h"

using namespace zaber::motion::requests;

namespace zaber {
namespace motion {


/**
 * Test case for certain library features. Not public API; do not use.
 */
class VariantTestApi {
public:
    VariantTestApi() = delete;

    /**
     * Tests serialization of variants.
     * @param theVariant Test value to modify and return.
     * @return Mutated input value.
     */
    static std::optional<TestVariant> mutateVariant(const TestVariant& theVariant);
    /**
     * Tests serialization of arrays of variants.
     * @param variantArray Test values to modify and return.
     * @return Mutated input values.
     */
    static std::vector<TestVariant> mutateVariantArray(const std::vector<TestVariant>& variantArray);
protected:
};


}  // Namespace motion
}  // Namespace zaber
