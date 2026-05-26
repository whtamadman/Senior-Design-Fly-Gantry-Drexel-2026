// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceCancelAllOutputsScheduleRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    bool analog {false};
    std::vector<bool> channels;

    DeviceCancelAllOutputsScheduleRequest();

    DeviceCancelAllOutputsScheduleRequest(
        int p_interfaceId,
        int p_device,
        bool p_analog,
        std::vector<bool> p_channels
    );

    bool operator==(const DeviceCancelAllOutputsScheduleRequest& other) const;

    bool operator!=(const DeviceCancelAllOutputsScheduleRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    bool getAnalog() const;
    void setAnalog(bool p_analog);

    std::vector<bool> const& getChannels() const;
    void setChannels(std::vector<bool> p_channels);

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
