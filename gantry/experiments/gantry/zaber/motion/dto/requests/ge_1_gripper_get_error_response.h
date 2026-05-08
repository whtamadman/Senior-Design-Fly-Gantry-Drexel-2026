// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/product/ge_1_gripper_error.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperGetErrorResponse: public Serializable {
public:
    product::Ge1GripperError value {0};

    Ge1GripperGetErrorResponse();

    Ge1GripperGetErrorResponse(
        product::Ge1GripperError p_value
    );

    bool operator==(const Ge1GripperGetErrorResponse& other) const;

    bool operator!=(const Ge1GripperGetErrorResponse& other) const {
        return !(*this == other);
    }

    product::Ge1GripperError const& getValue() const;
    void setValue(product::Ge1GripperError p_value);

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
