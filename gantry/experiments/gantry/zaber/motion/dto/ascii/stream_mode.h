// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Mode of a stream.
 */
enum class StreamMode {
    /* The stream is not set up. */
    DISABLED = 0,
    /* Actions are queued into a stream buffer for later playback. */
    STORE = 1,
    /* Actions are queued into a stream buffer for later playback (axes not specified). */
    STORE_ARBITRARY_AXES = 2,
    /* Actions are queued and executed on the device immediately. */
    LIVE = 3,
};

/**
 * Returns string representation of StreamMode value
 */
std::string StreamMode_toString(StreamMode value);


} // namespace ascii
} // namespace motion
} // namespace zaber
