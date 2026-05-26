// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/product/ge_1_gripper_state.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperGetStateResponse: public Serializable {
public:
    product::Ge1GripperState value {0};

    Ge1GripperGetStateResponse();

    Ge1GripperGetStateResponse(
        product::Ge1GripperState p_value
    );

    bool operator==(const Ge1GripperGetStateResponse& other) const;

    bool operator!=(const Ge1GripperGetStateResponse& other) const {
        return !(*this == other);
    }

    product::Ge1GripperState const& getValue() const;
    void setValue(product::Ge1GripperState p_value);

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
