// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Mode of a PVT sequence.
 */
enum class PvtMode {
    /* The PVT sequence is not set up. */
    DISABLED = 0,
    /* PVT points are queued into a buffer for later playback. */
    STORE = 1,
    /* PVT points are queued and executed on the device immediately. */
    LIVE = 2,
};

/**
 * Returns string representation of PvtMode value
 */
std::string PvtMode_toString(PvtMode value);


} // namespace ascii
} // namespace motion
} // namespace zaber
