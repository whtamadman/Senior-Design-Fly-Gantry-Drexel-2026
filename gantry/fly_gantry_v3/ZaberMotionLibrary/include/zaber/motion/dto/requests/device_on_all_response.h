// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceOnAllResponse: public Serializable {
public:
    std::vector<int> deviceAddresses;

    DeviceOnAllResponse();

    DeviceOnAllResponse(
        std::vector<int> p_deviceAddresses
    );

    bool operator==(const DeviceOnAllResponse& other) const;

    bool operator!=(const DeviceOnAllResponse& other) const {
        return !(*this == other);
    }

    std::vector<int> const& getDeviceAddresses() const;
    void setDeviceAddresses(std::vector<int> p_deviceAddresses);

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
