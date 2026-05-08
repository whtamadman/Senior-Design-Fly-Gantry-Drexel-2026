// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace product {

/**
 * Mode of the process controller.
 */
enum class ProcessControllerMode {
    /* Allows direct control of the output voltage. */
    MANUAL = 0,
    /* Closed-loop PID control to maintain a setpoint. */
    PID = 1,
    /* PID control optimized for heater loads. */
    PID_HEATER = 2,
    /* Binary on/off switching based on a threshold. */
    ON_OFF = 3,
};

/**
 * Returns string representation of ProcessControllerMode value
 */
std::string ProcessControllerMode_toString(ProcessControllerMode value);


} // namespace product
} // namespace motion
} // namespace zaber
