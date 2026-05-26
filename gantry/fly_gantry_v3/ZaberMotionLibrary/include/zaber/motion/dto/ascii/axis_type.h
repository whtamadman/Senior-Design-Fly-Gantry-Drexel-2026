// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Denotes type of an axis and units it accepts.
 */
enum class AxisType {
    /* Axis type could not be determined. */
    UNKNOWN = 0,
    /* A linear axis that accepts length units for position. */
    LINEAR = 1,
    /* A rotary axis that accepts angle units for position. */
    ROTARY = 2,
    /* A process on a process controller. */
    PROCESS = 3,
    /* A lamp on a light source controller. */
    LAMP = 4,
};

/**
 * Returns string representation of AxisType value
 */
std::string AxisType_toString(AxisType value);


} // namespace ascii
} // namespace motion
} // namespace zaber
