// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Comparison operator for trigger condition.
 */
enum class TriggerCondition {
    /* Equal To (==) */
    EQ = 0,
    /* Not Equal To (!=) */
    NE = 1,
    /* Greater Than (>) */
    GT = 2,
    /* Greater Than or Equal To (>=) */
    GE = 3,
    /* Less Than (<) */
    LT = 4,
    /* Less Than or Equal To (<=) */
    LE = 5,
};

/**
 * Returns string representation of TriggerCondition value
 */
std::string TriggerCondition_toString(TriggerCondition value);


} // namespace ascii
} // namespace motion
} // namespace zaber
