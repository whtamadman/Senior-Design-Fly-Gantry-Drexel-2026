// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceSetAllAnalogOutputsRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    std::vector<double> values;

    DeviceSetAllAnalogOutputsRequest();

    DeviceSetAllAnalogOutputsRequest(
        int p_interfaceId,
        int p_device,
        std::vector<double> p_values
    );

    bool operator==(const DeviceSetAllAnalogOutputsRequest& other) const;

    bool operator!=(const DeviceSetAllAnalogOutputsRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    std::vector<double> const& getValues() const;
    void setValues(std::vector<double> p_values);

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
