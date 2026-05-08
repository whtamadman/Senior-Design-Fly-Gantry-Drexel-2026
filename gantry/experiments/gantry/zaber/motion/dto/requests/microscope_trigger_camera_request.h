// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class MicroscopeTriggerCameraRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int channelNumber {0};
    double delay {0.0};
    Units unit {Units::NATIVE};
    bool wait {false};

    MicroscopeTriggerCameraRequest();

    MicroscopeTriggerCameraRequest(
        int p_interfaceId,
        int p_device,
        int p_channelNumber,
        double p_delay,
        Units p_unit,
        bool p_wait
    );

    bool operator==(const MicroscopeTriggerCameraRequest& other) const;

    bool operator!=(const MicroscopeTriggerCameraRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getChannelNumber() const;
    void setChannelNumber(int p_channelNumber);

    double getDelay() const;
    void setDelay(double p_delay);

    Units getUnit() const;
    void setUnit(Units p_unit);

    bool getWait() const;
    void setWait(bool p_wait);

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
