// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <variant>

#include "zaber/motion/dto/ascii/pvt_point.h"
#include "zaber/motion/dto/ascii/pvt_call_action.h"
#include "zaber/motion/dto/ascii/pvt_set_digital_output_action.h"
#include "zaber/motion/dto/ascii/pvt_set_all_digital_outputs_action.h"
#include "zaber/motion/dto/ascii/pvt_set_analog_output_action.h"
#include "zaber/motion/dto/ascii/pvt_set_all_analog_outputs_action.h"
#include "zaber/motion/dto/ascii/pvt_cancel_output_schedule_action.h"
#include "zaber/motion/dto/ascii/pvt_cancel_all_outputs_schedule_action.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Union of all data types that can appear in a PVT sequence.
 */
using PvtSequenceItem = std::variant<
    PvtPoint,
    PvtCallAction,
    PvtSetDigitalOutputAction,
    PvtSetAllDigitalOutputsAction,
    PvtSetAnalogOutputAction,
    PvtSetAllAnalogOutputsAction,
    PvtCancelOutputScheduleAction,
    PvtCancelAllOutputsScheduleAction
>;

/**
 * Converts a PvtSequenceItem variant to a string representation.
 */
std::string PvtSequenceItem_toString(const PvtSequenceItem& value);

} // namespace ascii
} // namespace motion
} // namespace zaber
