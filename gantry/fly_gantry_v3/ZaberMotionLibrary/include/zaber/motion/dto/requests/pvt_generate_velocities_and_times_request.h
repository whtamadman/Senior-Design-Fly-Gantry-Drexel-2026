// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/pvt_partial_sequence_item.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace requests {

class PvtGenerateVelocitiesAndTimesRequest: public Serializable {
public:
    std::vector<ascii::PvtPartialSequenceItem> sequenceItems;
    Measurement targetSpeed;
    Measurement targetAcceleration;
    std::optional<int> resampleNumber;

    PvtGenerateVelocitiesAndTimesRequest();

    PvtGenerateVelocitiesAndTimesRequest(
        std::vector<ascii::PvtPartialSequenceItem> p_sequenceItems,
        Measurement p_targetSpeed,
        Measurement p_targetAcceleration,
        std::optional<int> p_resampleNumber
    );

    PvtGenerateVelocitiesAndTimesRequest(
        std::vector<ascii::PvtPartialSequenceItem> p_sequenceItems,
        Measurement p_targetSpeed,
        Measurement p_targetAcceleration
    );

    bool operator==(const PvtGenerateVelocitiesAndTimesRequest& other) const;

    bool operator!=(const PvtGenerateVelocitiesAndTimesRequest& other) const {
        return !(*this == other);
    }

    std::vector<ascii::PvtPartialSequenceItem> const& getSequenceItems() const;
    void setSequenceItems(std::vector<ascii::PvtPartialSequenceItem> p_sequenceItems);

    Measurement const& getTargetSpeed() const;
    void setTargetSpeed(Measurement p_targetSpeed);

    Measurement const& getTargetAcceleration() const;
    void setTargetAcceleration(Measurement p_targetAcceleration);

    std::optional<int> getResampleNumber() const;
    void setResampleNumber(std::optional<int> p_resampleNumber);

    /**
     * Convert object to human-readable string format
     */
    std::string toString() const;

#ifdef ZML_SERIALIZATION_PUBLIC
public:
#else
private:
#endif

    std::string toByteArray() const override;
    void populateFromByteArray(const std::string& buffer) override;

};

} // namespace requests
} // namespace motion
} // namespace zaber
