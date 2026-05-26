// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {

/**
 * Direction of rotation.
 */
enum class RotationDirection {
    /* Rotate in the clockwise direction. */
    CLOCKWISE = 0,
    /* Rotate in the counterclockwise direction. */
    COUNTERCLOCKWISE = 1,
    /* Shorthand alias for Clockwise. */
    CW = 0,
    /* Shorthand alias for Counterclockwise. */
    CCW = 1,
};

/**
 * Returns string representation of RotationDirection value
 */
std::string RotationDirection_toString(RotationDirection value);


} // namespace motion
} // namespace zaber
