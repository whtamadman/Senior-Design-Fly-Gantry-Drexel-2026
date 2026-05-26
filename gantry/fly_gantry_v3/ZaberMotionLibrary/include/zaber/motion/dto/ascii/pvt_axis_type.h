// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Denotes type of the PVT sequence axis.
 */
enum class PvtAxisType {
    /* A regular physical axis of the device. */
    PHYSICAL = 0,
    /* A lockstep group combining multiple physical axes. */
    LOCKSTEP = 1,
};

/**
 * Returns string representation of PvtAxisType value
 */
std::string PvtAxisType_toString(PvtAxisType value);


} // namespace ascii
} // namespace motion
} // namespace zaber
