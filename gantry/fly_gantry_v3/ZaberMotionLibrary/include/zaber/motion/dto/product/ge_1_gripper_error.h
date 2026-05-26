// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace product {

/**
 * Error for a GE1 series gripper.
 */
enum class Ge1GripperError {
    /* No error. */
    NONE = 0,
    /* The gripper supply voltage is too low. */
    UNDERVOLTAGE = 1,
    /* The gripper supply voltage is too high. */
    OVERVOLTAGE = 2,
    /* The gripper is drawing too much current. */
    OVERCURRENT = 3,
    /* The gripper temperature is too high. */
    OVERTEMPERATURE = 4,
    /* There is a 3-phase imbalance in the motor. */
    MOTOR_PHASE_LOSS = 10,
    /* The gripper has exceeded its rated speed. */
    OVERSPEED = 11,
    /* There is an error with the gripper encoder. */
    ENCODER_ERROR = 32,
    /* There is a communication error with the gripper encoder. */
    ENCODER_COMMUNICATION_ERROR = 33,
    /* The gripper current sampling offset is abnormal. */
    SAMPLING_CIRCUIT_ERROR = 34,
    /* There is an error with the gripper driver circuit. */
    DRIVER_CIRCUIT_ERROR = 35,
    /* There is an error with the gripper flash memory. */
    FLASH_CHIP_ERROR = 36,
    /* There is an error with the gripper file system. */
    FILE_SYSTEM_ERROR = 37,
};

/**
 * Returns string representation of Ge1GripperError value
 */
std::string Ge1GripperError_toString(Ge1GripperError value);


} // namespace product
} // namespace motion
} // namespace zaber
