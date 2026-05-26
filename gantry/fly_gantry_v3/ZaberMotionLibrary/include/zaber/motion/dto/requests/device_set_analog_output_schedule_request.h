// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceSetAnalogOutputScheduleRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int channelNumber {0};
    double value {0.0};
    double futureValue {0.0};
    double delay {0.0};
    Units unit {Units::NATIVE};

    DeviceSetAnalogOutputScheduleRequest();

    DeviceSetAnalogOutputScheduleRequest(
        int p_interfaceId,
        int p_device,
        int p_channelNumber,
        double p_value,
        double p_futureValue,
        double p_delay,
        Units p_unit
    );

    bool operator==(const DeviceSetAnalogOutputScheduleRequest& other) const;

    bool operator!=(const DeviceSetAnalogOutputScheduleRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getChannelNumber() const;
    void setChannelNumber(int p_channelNumber);

    double getValue() const;
    void setValue(double p_value);

    double getFutureValue() const;
    void setFutureValue(double p_futureValue);

    double getDelay() const;
    void setDelay(double p_delay);

    Units getUnit() const;
    void setUnit(Units p_unit);

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
