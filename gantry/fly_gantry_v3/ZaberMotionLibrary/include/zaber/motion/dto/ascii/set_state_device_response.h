// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/set_state_axis_response.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * An object containing any non-blocking issues encountered when loading a saved state to a device.
 */
class SetStateDeviceResponse: public Serializable {
public:
    std::vector<std::string> warnings;
    std::vector<SetStateAxisResponse> axisResponses;

    SetStateDeviceResponse();

    SetStateDeviceResponse(
        std::vector<std::string> p_warnings,
        std::vector<SetStateAxisResponse> p_axisResponses
    );

    bool operator==(const SetStateDeviceResponse& other) const;

    bool operator!=(const SetStateDeviceResponse& other) const {
        return !(*this == other);
    }

    /**
     * The warnings encountered when applying this state to the given device.
     */
    std::vector<std::string> const& getWarnings() const;
    void setWarnings(std::vector<std::string> p_warnings);

    /**
     * A list of axis responses, potentially with warnings encountered
     * when applying this state to the device's axes.
     */
    std::vector<SetStateAxisResponse> const& getAxisResponses() const;
    void setAxisResponses(std::vector<SetStateAxisResponse> p_axisResponses);

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
