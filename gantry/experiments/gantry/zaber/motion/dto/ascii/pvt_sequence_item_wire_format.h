// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/pvt_sequence_item.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Serialization wrapper for the PvtSequenceItem variant. Not part of the public API.
 */
class PvtSequenceItemWireFormat: public Serializable {
public:
    std::string variantValueType;
    std::optional<PvtPoint> pvtPointValue;
    std::optional<PvtCallAction> pvtCallActionValue;
    std::optional<PvtSetDigitalOutputAction> pvtSetDigitalOutputActionValue;
    std::optional<PvtSetAllDigitalOutputsAction> pvtSetAllDigitalOutputsActionValue;
    std::optional<PvtSetAnalogOutputAction> pvtSetAnalogOutputActionValue;
    std::optional<PvtSetAllAnalogOutputsAction> pvtSetAllAnalogOutputsActionValue;
    std::optional<PvtCancelOutputScheduleAction> pvtCancelOutputScheduleActionValue;
    std::optional<PvtCancelAllOutputsScheduleAction> pvtCancelAllOutputsScheduleActionValue;

    PvtSequenceItemWireFormat() = default;
    PvtSequenceItemWireFormat(const PvtSequenceItem& value);

    PvtSequenceItem convertBack() const;

    bool operator==(const PvtSequenceItemWireFormat& other) const;

    bool operator!=(const PvtSequenceItemWireFormat& other) const {
        return !(*this == other);
    }

#ifdef ZML_SERIALIZATION_PUBLIC
public:
#else
private:
#endif
    std::string toByteArray() const override;
    void populateFromByteArray(const std::string& buffer) override;
};

} // namespace ascii
} // namespace motion
} // namespace zaber
