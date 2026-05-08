// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class StreamBufferGetContentResponse: public Serializable {
public:
    std::vector<std::string> bufferLines;

    StreamBufferGetContentResponse();

    StreamBufferGetContentResponse(
        std::vector<std::string> p_bufferLines
    );

    bool operator==(const StreamBufferGetContentResponse& other) const;

    bool operator!=(const StreamBufferGetContentResponse& other) const {
        return !(*this == other);
    }

    std::vector<std::string> const& getBufferLines() const;
    void setBufferLines(std::vector<std::string> p_bufferLines);

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
