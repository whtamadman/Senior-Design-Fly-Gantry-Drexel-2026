// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#pragma push_macro("ERROR")
#undef ERROR

#include <string>

namespace zaber {
namespace motion {
namespace requests {

enum class ResponseType {
    OK = 0,
    ERROR = 1,
};

/**
 * Returns string representation of ResponseType value
 */
std::string ResponseType_toString(ResponseType value);


} // namespace requests
} // namespace motion
} // namespace zaber

#pragma pop_macro("ERROR")
