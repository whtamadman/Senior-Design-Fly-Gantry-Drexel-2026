// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Kind of I/O pin to use.
 */
enum class IoPortType {
    /* No port type specified. */
    NONE = 0,
    /* An analog input channel that reads a voltage. */
    ANALOG_INPUT = 1,
    /* An analog output channel that outputs a voltage. */
    ANALOG_OUTPUT = 2,
    /* A digital input channel that reads a boolean state. */
    DIGITAL_INPUT = 3,
    /* A digital output channel that controls a boolean state. */
    DIGITAL_OUTPUT = 4,
};

/**
 * Returns string representation of IoPortType value
 */
std::string IoPortType_toString(IoPortType value);


} // namespace ascii
} // namespace motion
} // namespace zaber
