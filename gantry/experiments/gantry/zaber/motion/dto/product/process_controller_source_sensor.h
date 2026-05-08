// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace product {

/**
 * The type of input sensor that provides feedback to the process controller.
 */
enum class ProcessControllerSourceSensor {
    /* Use a thermistor sensor port on the device to measure temperature. */
    THERMISTOR = 10,
    /* Use an analog input I/O channel on the device to measure voltage. */
    ANALOG_INPUT = 20,
};

/**
 * Returns string representation of ProcessControllerSourceSensor value
 */
std::string ProcessControllerSourceSensor_toString(ProcessControllerSourceSensor value);


} // namespace product
} // namespace motion
} // namespace zaber
