// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {

/**
 * Direction a cyclic device should move when doing an absolute move.
 */
enum class CyclicDirection {
    /* Move to the target in a positive direction. */
    POSITIVE = 0,
    /* Move to the target in a negative direction. */
    NEGATIVE = 1,
    /* Take the shortest path to the target position. */
    SHORTEST = 2,
};

/**
 * Returns string representation of CyclicDirection value
 */
std::string CyclicDirection_toString(CyclicDirection value);


} // namespace motion
} // namespace zaber
