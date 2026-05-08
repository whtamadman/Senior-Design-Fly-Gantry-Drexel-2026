// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {

/**
 * Type of TCP port used to connect to a device on the network.
 */
enum class DevicePortType {
    /* TCP port that communicates only with the connected device. */
    DEVICE = 0,
    /* TCP port that communicates with the connected device and all chained devices. */
    DEVICE_CHAIN = 1,
};

/**
 * Returns string representation of DevicePortType value
 */
std::string DevicePortType_toString(DevicePortType value);


} // namespace motion
} // namespace zaber
