// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/pvt_partial_sequence_item.h"

namespace zaber {
namespace motion {
namespace requests {

class PvtGeneratePositionsRequest: public Serializable {
public:
    std::vector<ascii::PvtPartialSequenceItem> sequenceItems;

    PvtGeneratePositionsRequest();

    PvtGeneratePositionsRequest(
        std::vector<ascii::PvtPartialSequenceItem> p_sequenceItems
    );

    bool operator==(const PvtGeneratePositionsRequest& other) const;

    bool operator!=(const PvtGeneratePositionsRequest& other) const {
        return !(*this == other);
    }

    std::vector<ascii::PvtPartialSequenceItem> const& getSequenceItems() const;
    void setSequenceItems(std::vector<ascii::PvtPartialSequenceItem> p_sequenceItems);

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
