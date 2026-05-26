// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace product {

/**
 * State of a GE1 series gripper.
 */
enum class Ge1GripperState {
    /* The gripper has not been homed and does not have a reference position. */
    NO_REFERENCE_POSITION = 0,
    /* The gripper is currently performing a homing operation. */
    HOMING = 1,
    /* The gripper is idle at its target position. */
    IDLE = 2,
    /* The gripper is moving to its target position. */
    MOVING = 3,
    /* The gripper has detected an object. */
    OBJECT_DETECTED = 4,
    /* The gripper has detected that an object it was holding has been dropped. */
    OBJECT_DROPPED = 5,
};

/**
 * Returns string representation of Ge1GripperState value
 */
std::string Ge1GripperState_toString(Ge1GripperState value);


} // namespace product
} // namespace motion
} // namespace zaber
