// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {

/**
 * Mode of logging output of the library.
 */
enum class LogOutputMode {
    /* Discard all log output. */
    OFF = 0,
    /* Write logs to standard output. */
    STDOUT = 1,
    /* Write logs to standard error. */
    STDERR = 2,
    /* Write logs to a specified file. */
    FILE = 3,
};

/**
 * Returns string representation of LogOutputMode value
 */
std::string LogOutputMode_toString(LogOutputMode value);


} // namespace motion
} // namespace zaber
