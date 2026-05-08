// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace requests {

enum class InterfaceType {
    SERIAL_PORT = 0,
    TCP = 1,
    CUSTOM = 2,
    IOT = 3,
    NETWORK_SHARE = 4,
    MOCK = 5,
};

/**
 * Returns string representation of InterfaceType value
 */
std::string InterfaceType_toString(InterfaceType value);


} // namespace requests
} // namespace motion
} // namespace zaber
