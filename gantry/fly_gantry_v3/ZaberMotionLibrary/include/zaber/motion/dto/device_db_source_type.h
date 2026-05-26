// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {

/**
 * Type of source of Device DB data.
 */
enum class DeviceDbSourceType {
    /* Fetch device information from a web service. */
    WEB_SERVICE = 0,
    /* Load device information from a local database file. */
    FILE = 1,
};

/**
 * Returns string representation of DeviceDbSourceType value
 */
std::string DeviceDbSourceType_toString(DeviceDbSourceType value);


} // namespace motion
} // namespace zaber
