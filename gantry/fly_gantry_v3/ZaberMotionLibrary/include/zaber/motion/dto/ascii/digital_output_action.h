// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Action type for digital output.
 */
enum class DigitalOutputAction {
    /* Set the digital output low. */
    OFF = 0,
    /* Set the digital output high. */
    ON = 1,
    /* Toggle the current state of the digital output. */
    TOGGLE = 2,
    /* Leave the digital output in its current state. */
    KEEP = 3,
};

/**
 * Returns string representation of DigitalOutputAction value
 */
std::string DigitalOutputAction_toString(DigitalOutputAction value);


} // namespace ascii
} // namespace motion
} // namespace zaber
