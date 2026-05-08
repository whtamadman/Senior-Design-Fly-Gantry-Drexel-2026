// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/stream_axis_type.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Defines an axis of the stream.
 */
class StreamAxisDefinition: public Serializable {
public:
    int axisNumber {0};
    std::optional<StreamAxisType> axisType;

    StreamAxisDefinition();

    StreamAxisDefinition(
        int p_axisNumber,
        std::optional<StreamAxisType> p_axisType
    );

    StreamAxisDefinition(
        int p_axisNumber
    );

    bool operator==(const StreamAxisDefinition& other) const;

    bool operator!=(const StreamAxisDefinition& other) const {
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
    std::optional<StreamAxisType> const& getAxisType() const;
    void setAxisType(std::optional<StreamAxisType> p_axisType);

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
