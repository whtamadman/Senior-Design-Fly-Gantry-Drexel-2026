// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/device_db_source.h"

namespace zaber {
namespace motion {
namespace requests {

class SetDeviceDbLayeredSourcesRequest: public Serializable {
public:
    std::vector<DeviceDbSource> sources;

    SetDeviceDbLayeredSourcesRequest();

    SetDeviceDbLayeredSourcesRequest(
        std::vector<DeviceDbSource> p_sources
    );

    bool operator==(const SetDeviceDbLayeredSourcesRequest& other) const;

    bool operator!=(const SetDeviceDbLayeredSourcesRequest& other) const {
        return !(*this == other);
    }

    std::vector<DeviceDbSource> const& getSources() const;
    void setSources(std::vector<DeviceDbSource> p_sources);

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
