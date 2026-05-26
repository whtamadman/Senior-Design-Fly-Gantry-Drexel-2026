// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/pvt_sequence_item.h"

namespace zaber {
namespace motion {
namespace requests {

class PvtConvertTimeResponse: public Serializable {
public:
    std::vector<ascii::PvtSequenceItem> sequenceData;

    PvtConvertTimeResponse();

    PvtConvertTimeResponse(
        std::vector<ascii::PvtSequenceItem> p_sequenceData
    );

    bool operator==(const PvtConvertTimeResponse& other) const;

    bool operator!=(const PvtConvertTimeResponse& other) const {
        return !(*this == other);
    }

    std::vector<ascii::PvtSequenceItem> const& getSequenceData() const;
    void setSequenceData(std::vector<ascii::PvtSequenceItem> p_sequenceData);

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
