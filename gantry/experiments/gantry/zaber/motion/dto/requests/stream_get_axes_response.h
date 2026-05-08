// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/stream_axis_definition.h"
#include "zaber/motion/dto/ascii/pvt_axis_definition.h"

namespace zaber {
namespace motion {
namespace requests {

class StreamGetAxesResponse: public Serializable {
public:
    std::vector<ascii::StreamAxisDefinition> axes;
    std::vector<ascii::PvtAxisDefinition> pvtAxes;

    StreamGetAxesResponse();

    StreamGetAxesResponse(
        std::vector<ascii::StreamAxisDefinition> p_axes,
        std::vector<ascii::PvtAxisDefinition> p_pvtAxes
    );

    bool operator==(const StreamGetAxesResponse& other) const;

    bool operator!=(const StreamGetAxesResponse& other) const {
        return !(*this == other);
    }

    std::vector<ascii::StreamAxisDefinition> const& getAxes() const;
    void setAxes(std::vector<ascii::StreamAxisDefinition> p_axes);

    std::vector<ascii::PvtAxisDefinition> const& getPvtAxes() const;
    void setPvtAxes(std::vector<ascii::PvtAxisDefinition> p_pvtAxes);

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
