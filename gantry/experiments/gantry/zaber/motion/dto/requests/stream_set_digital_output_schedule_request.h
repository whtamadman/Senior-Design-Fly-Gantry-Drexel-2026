// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/digital_output_action.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class StreamSetDigitalOutputScheduleRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int streamId {0};
    bool pvt {false};
    int channelNumber {0};
    ascii::DigitalOutputAction value {0};
    ascii::DigitalOutputAction futureValue {0};
    double delay {0.0};
    Units unit {Units::NATIVE};

    StreamSetDigitalOutputScheduleRequest();

    StreamSetDigitalOutputScheduleRequest(
        int p_interfaceId,
        int p_device,
        int p_streamId,
        bool p_pvt,
        int p_channelNumber,
        ascii::DigitalOutputAction p_value,
        ascii::DigitalOutputAction p_futureValue,
        double p_delay,
        Units p_unit
    );

    bool operator==(const StreamSetDigitalOutputScheduleRequest& other) const;

    bool operator!=(const StreamSetDigitalOutputScheduleRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getStreamId() const;
    void setStreamId(int p_streamId);

    bool getPvt() const;
    void setPvt(bool p_pvt);

    int getChannelNumber() const;
    void setChannelNumber(int p_channelNumber);

    ascii::DigitalOutputAction const& getValue() const;
    void setValue(ascii::DigitalOutputAction p_value);

    ascii::DigitalOutputAction const& getFutureValue() const;
    void setFutureValue(ascii::DigitalOutputAction p_futureValue);

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
