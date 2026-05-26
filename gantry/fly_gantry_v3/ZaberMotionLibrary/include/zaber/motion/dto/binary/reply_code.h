// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#pragma push_macro("ERROR")
#undef ERROR

#include <string>

namespace zaber {
namespace motion {
namespace binary {

/**
 * Named constants for all Zaber Binary protocol reply-only command codes.
 */
enum class ReplyCode {
    MOVE_TRACKING = 8,
    LIMIT_ACTIVE = 9,
    MANUAL_MOVE_TRACKING = 10,
    MANUAL_MOVE = 11,
    SLIP_TRACKING = 12,
    UNEXPECTED_POSITION = 13,
    ERROR = 255,
};

/**
 * Returns string representation of ReplyCode value
 */
std::string ReplyCode_toString(ReplyCode value);


} // namespace binary
} // namespace motion
} // namespace zaber

#pragma pop_macro("ERROR")
