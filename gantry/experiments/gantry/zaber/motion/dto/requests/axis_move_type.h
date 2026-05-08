// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace requests {

enum class AxisMoveType {
    ABS = 0,
    REL = 1,
    VEL = 2,
    MAX = 3,
    MIN = 4,
    INDEX = 5,
};

/**
 * Returns string representation of AxisMoveType value
 */
std::string AxisMoveType_toString(AxisMoveType value);


} // namespace requests
} // namespace motion
} // namespace zaber
