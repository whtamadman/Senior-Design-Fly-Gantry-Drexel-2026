// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceCancelOutputScheduleRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    bool analog {false};
    int channelNumber {0};

    DeviceCancelOutputScheduleRequest();

    DeviceCancelOutputScheduleRequest(
        int p_interfaceId,
        int p_device,
        bool p_analog,
        int p_channelNumber
    );

    bool operator==(const DeviceCancelOutputScheduleRequest& other) const;

    bool operator!=(const DeviceCancelOutputScheduleRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    bool getAnalog() const;
    void setAnalog(bool p_analog);

    int getChannelNumber() const;
    void setChannelNumber(int p_channelNumber);

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
