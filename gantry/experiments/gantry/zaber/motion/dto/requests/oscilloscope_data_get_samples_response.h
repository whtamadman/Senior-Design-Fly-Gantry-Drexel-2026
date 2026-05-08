// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class OscilloscopeDataGetSamplesResponse: public Serializable {
public:
    std::vector<double> data;

    OscilloscopeDataGetSamplesResponse();

    OscilloscopeDataGetSamplesResponse(
        std::vector<double> p_data
    );

    bool operator==(const OscilloscopeDataGetSamplesResponse& other) const;

    bool operator!=(const OscilloscopeDataGetSamplesResponse& other) const {
        return !(*this == other);
    }

    std::vector<double> const& getData() const;
    void setData(std::vector<double> p_data);

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
