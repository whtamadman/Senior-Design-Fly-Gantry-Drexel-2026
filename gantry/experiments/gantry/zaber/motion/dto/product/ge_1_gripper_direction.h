// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace product {

/**
 * Direction for a GE1 series gripper.
 */
enum class Ge1GripperDirection {
    OPEN = 0,
    CLOSE = 1,
};

/**
 * Returns string representation of Ge1GripperDirection value
 */
std::string Ge1GripperDirection_toString(Ge1GripperDirection value);


} // namespace product
} // namespace motion
} // namespace zaber
