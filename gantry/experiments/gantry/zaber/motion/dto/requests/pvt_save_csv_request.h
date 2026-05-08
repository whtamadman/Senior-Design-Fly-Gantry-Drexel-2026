// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>
#include <optional>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/pvt_sequence_item.h"

namespace zaber {
namespace motion {
namespace requests {

class PvtSaveCsvRequest: public Serializable {
public:
    std::vector<ascii::PvtSequenceItem> sequenceData;
    std::string path;
    std::vector<std::string> dimensionNames;

    PvtSaveCsvRequest();

    PvtSaveCsvRequest(
        std::vector<ascii::PvtSequenceItem> p_sequenceData,
        std::string p_path,
        std::vector<std::string> p_dimensionNames
    );

    PvtSaveCsvRequest(
        std::vector<ascii::PvtSequenceItem> p_sequenceData,
        std::string p_path
    );

    bool operator==(const PvtSaveCsvRequest& other) const;

    bool operator!=(const PvtSaveCsvRequest& other) const {
        return !(*this == other);
    }

    std::vector<ascii::PvtSequenceItem> const& getSequenceData() const;
    void setSequenceData(std::vector<ascii::PvtSequenceItem> p_sequenceData);

    std::string const& getPath() const;
    void setPath(std::string p_path);

    std::vector<std::string> const& getDimensionNames() const;
    void setDimensionNames(std::vector<std::string> p_dimensionNames);

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
