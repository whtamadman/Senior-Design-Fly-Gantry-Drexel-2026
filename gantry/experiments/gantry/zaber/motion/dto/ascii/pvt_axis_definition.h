// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/pvt_axis_type.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Defines an axis of the PVT sequence.
 */
class PvtAxisDefinition: public Serializable {
public:
    int axisNumber {0};
    std::optional<PvtAxisType> axisType;

    PvtAxisDefinition();

    PvtAxisDefinition(
        int p_axisNumber,
        std::optional<PvtAxisType> p_axisType
    );

    PvtAxisDefinition(
        int p_axisNumber
    );

    bool operator==(const PvtAxisDefinition& other) const;

    bool operator!=(const PvtAxisDefinition& other) const {
        return !(*this == other);
    }

    /**
     * Number of a physical axis or a lockstep group.
     */
    int getAxisNumber() const;
    void setAxisNumber(int p_axisNumber);

    /**
     * Defines the type of the axis.
     */
    std::optional<PvtAxisType> const& getAxisType() const;
    void setAxisType(std::optional<PvtAxisType> p_axisType);

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
