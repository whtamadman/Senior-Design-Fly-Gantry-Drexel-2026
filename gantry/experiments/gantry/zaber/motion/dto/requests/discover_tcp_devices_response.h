// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/device_discovery_result.h"

namespace zaber {
namespace motion {
namespace requests {

class DiscoverTCPDevicesResponse: public Serializable {
public:
    std::vector<DeviceDiscoveryResult> result;

    DiscoverTCPDevicesResponse();

    DiscoverTCPDevicesResponse(
        std::vector<DeviceDiscoveryResult> p_result
    );

    bool operator==(const DiscoverTCPDevicesResponse& other) const;

    bool operator!=(const DiscoverTCPDevicesResponse& other) const {
        return !(*this == other);
    }

    std::vector<DeviceDiscoveryResult> const& getResult() const;
    void setResult(std::vector<DeviceDiscoveryResult> p_result);

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
