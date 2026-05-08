// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Operation for trigger action.
 */
enum class TriggerOperation {
    /* Assign the value to the setting (=). */
    SET_TO = 0,
    /* Add the value to the current setting value (+=). */
    INCREMENT_BY = 1,
    /* Subtract the value from the current setting value (-=). */
    DECREMENT_BY = 2,
};

/**
 * Returns string representation of TriggerOperation value
 */
std::string TriggerOperation_toString(TriggerOperation value);


} // namespace ascii
} // namespace motion
} // namespace zaber
