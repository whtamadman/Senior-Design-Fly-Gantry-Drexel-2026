// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/stream_mode.h"
#include "zaber/motion/dto/ascii/pvt_mode.h"

namespace zaber {
namespace motion {
namespace requests {

class StreamModeResponse: public Serializable {
public:
    ascii::StreamMode streamMode {0};
    ascii::PvtMode pvtMode {0};

    StreamModeResponse();

    StreamModeResponse(
        ascii::StreamMode p_streamMode,
        ascii::PvtMode p_pvtMode
    );

    bool operator==(const StreamModeResponse& other) const;

    bool operator!=(const StreamModeResponse& other) const {
        return !(*this == other);
    }

    ascii::StreamMode const& getStreamMode() const;
    void setStreamMode(ascii::StreamMode p_streamMode);

    ascii::PvtMode const& getPvtMode() const;
    void setPvtMode(ascii::PvtMode p_pvtMode);

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
