// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <vector>
#include <string>
#include <variant>

#include "zaber/motion/dto/ascii/axis_type.h"
#include "zaber/motion/dto/ascii/io_port_label.h"

namespace zaber {
namespace motion {
namespace requests {

/**
 * Test case for variant support. Not part of the public API. Do not use.
 */
using TestVariant = std::variant<
    ascii::AxisType,
    ascii::IoPortLabel,
    int,
    std::optional<double>,
    std::vector<std::string>
>;

/**
 * Converts a TestVariant variant to a string representation.
 */
std::string TestVariant_toString(const TestVariant& value);

} // namespace requests
} // namespace motion
} // namespace zaber
