// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Servo Tuning Parameter Set to target.
 */
enum class ServoTuningParamset {
    /* The currently active servo tuning parameters. */
    LIVE = 0,
    /* Stored parameter set 1. */
    P_1 = 1,
    /* Stored parameter set 2. */
    P_2 = 2,
    /* Stored parameter set 3. */
    P_3 = 3,
    /* Stored parameter set 4. */
    P_4 = 4,
    /* Stored parameter set 5. */
    P_5 = 5,
    /* Stored parameter set 6. */
    P_6 = 6,
    /* Stored parameter set 7. */
    P_7 = 7,
    /* Stored parameter set 8. */
    P_8 = 8,
    /* Stored parameter set 9. */
    P_9 = 9,
    /* A temporary working area for preparing tuning changes. */
    STAGING = 10,
    /* The factory default parameter set. */
    DEFAULT = 11,
};

/**
 * Returns string representation of ServoTuningParamset value
 */
std::string ServoTuningParamset_toString(ServoTuningParamset value);


} // namespace ascii
} // namespace motion
} // namespace zaber
