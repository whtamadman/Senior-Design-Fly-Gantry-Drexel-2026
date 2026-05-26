// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Kind of channel to record in the Oscilloscope.
 */
enum class OscilloscopeDataSource {
    /* Records the value of a device or axis setting over time. */
    SETTING = 0,
    /* Records the value of an I/O pin over time. */
    IO = 1,
};

/**
 * Returns string representation of OscilloscopeDataSource value
 */
std::string OscilloscopeDataSource_toString(OscilloscopeDataSource value);


} // namespace ascii
} // namespace motion
} // namespace zaber
