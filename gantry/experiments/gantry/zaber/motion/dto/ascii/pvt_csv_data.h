// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/pvt_sequence_item.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Data representing content loaded from PVT CSV file, with sequence data and sequence names.
 */
class PvtCsvData: public Serializable {
public:
    std::vector<PvtSequenceItem> sequenceData;
    std::vector<std::string> seriesNames;

    PvtCsvData();

    PvtCsvData(
        std::vector<PvtSequenceItem> p_sequenceData,
        std::vector<std::string> p_seriesNames
    );

    bool operator==(const PvtCsvData& other) const;

    bool operator!=(const PvtCsvData& other) const {
        return !(*this == other);
    }

    /**
     * The points and actions of the PVT sequence.
     */
    std::vector<PvtSequenceItem> const& getSequenceData() const;
    void setSequenceData(std::vector<PvtSequenceItem> p_sequenceData);

    /**
     * The names of the columns in the CSV header.
     * If the header columns do not contain names, these will default to `Series 1`, `Series 2`, etc..
     */
    std::vector<std::string> const& getSeriesNames() const;
    void setSeriesNames(std::vector<std::string> p_seriesNames);

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

} // namespace ascii
} // namespace motion
} // namespace zaber
