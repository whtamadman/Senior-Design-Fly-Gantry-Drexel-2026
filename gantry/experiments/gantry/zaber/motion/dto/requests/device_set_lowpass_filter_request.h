// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceSetLowpassFilterRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int channelNumber {0};
    double cutoffFrequency {0.0};
    Units unit {Units::NATIVE};

    DeviceSetLowpassFilterRequest();

    DeviceSetLowpassFilterRequest(
        int p_interfaceId,
        int p_device,
        int p_channelNumber,
        double p_cutoffFrequency,
        Units p_unit
    );

    bool operator==(const DeviceSetLowpassFilterRequest& other) const;

    bool operator!=(const DeviceSetLowpassFilterRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getChannelNumber() const;
    void setChannelNumber(int p_channelNumber);

    double getCutoffFrequency() const;
    void setCutoffFrequency(double p_cutoffFrequency);

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
