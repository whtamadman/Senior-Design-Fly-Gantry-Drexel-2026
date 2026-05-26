// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace binary {

/**
 * Denotes type of an device and units it accepts.
 */
enum class DeviceType {
    /* Device type could not be determined. */
    UNKNOWN = 0,
    /* A linear device that accepts length units for position. */
    LINEAR = 1,
    /* A rotary device that accepts angle units for position. */
    ROTARY = 2,
};

/**
 * Returns string representation of DeviceType value
 */
std::string DeviceType_toString(DeviceType value);


} // namespace binary
} // namespace motion
} // namespace zaber
