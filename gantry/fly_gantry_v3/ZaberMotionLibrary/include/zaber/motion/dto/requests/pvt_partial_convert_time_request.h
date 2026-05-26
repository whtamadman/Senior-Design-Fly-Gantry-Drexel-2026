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

class PvtPartialConvertTimeRequest: public Serializable {
public:
    std::vector<ascii::PvtPartialSequenceItem> sequenceData;
    bool fromAbsolute {false};

    PvtPartialConvertTimeRequest();

    PvtPartialConvertTimeRequest(
        std::vector<ascii::PvtPartialSequenceItem> p_sequenceData,
        bool p_fromAbsolute
    );

    bool operator==(const PvtPartialConvertTimeRequest& other) const;

    bool operator!=(const PvtPartialConvertTimeRequest& other) const {
        return !(*this == other);
    }

    std::vector<ascii::PvtPartialSequenceItem> const& getSequenceData() const;
    void setSequenceData(std::vector<ascii::PvtPartialSequenceItem> p_sequenceData);

    bool getFromAbsolute() const;
    void setFromAbsolute(bool p_fromAbsolute);

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
