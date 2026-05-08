// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class OscilloscopeReadResponse: public Serializable {
public:
    std::vector<int> dataIds;

    OscilloscopeReadResponse();

    OscilloscopeReadResponse(
        std::vector<int> p_dataIds
    );

    bool operator==(const OscilloscopeReadResponse& other) const;

    bool operator!=(const OscilloscopeReadResponse& other) const {
        return !(*this == other);
    }

    std::vector<int> const& getDataIds() const;
    void setDataIds(std::vector<int> p_dataIds);

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
