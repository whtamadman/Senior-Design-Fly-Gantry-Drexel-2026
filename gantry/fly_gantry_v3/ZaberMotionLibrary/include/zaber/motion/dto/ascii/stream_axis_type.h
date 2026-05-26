// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Denotes type of the stream axis.
 */
enum class StreamAxisType {
    /* A regular physical axis of the device. */
    PHYSICAL = 0,
    /* A lockstep group combining multiple physical axes. */
    LOCKSTEP = 1,
};

/**
 * Returns string representation of StreamAxisType value
 */
std::string StreamAxisType_toString(StreamAxisType value);


} // namespace ascii
} // namespace motion
} // namespace zaber
