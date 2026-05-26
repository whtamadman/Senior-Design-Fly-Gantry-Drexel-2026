// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Trigger action identifier.
 */
enum class TriggerAction {
    /* Refers to all trigger actions. */
    ALL = 0,
    /* Action A on a trigger. */
    A = 1,
    /* Action B on a trigger. */
    B = 2,
};

/**
 * Returns string representation of TriggerAction value
 */
std::string TriggerAction_toString(TriggerAction value);


} // namespace ascii
} // namespace motion
} // namespace zaber
