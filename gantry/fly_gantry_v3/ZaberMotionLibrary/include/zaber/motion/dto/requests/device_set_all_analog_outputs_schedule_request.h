// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceSetAllAnalogOutputsScheduleRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    std::vector<double> values;
    std::vector<double> futureValues;
    double delay {0.0};
    Units unit {Units::NATIVE};

    DeviceSetAllAnalogOutputsScheduleRequest();

    DeviceSetAllAnalogOutputsScheduleRequest(
        int p_interfaceId,
        int p_device,
        std::vector<double> p_values,
        std::vector<double> p_futureValues,
        double p_delay,
        Units p_unit
    );

    bool operator==(const DeviceSetAllAnalogOutputsScheduleRequest& other) const;

    bool operator!=(const DeviceSetAllAnalogOutputsScheduleRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    std::vector<double> const& getValues() const;
    void setValues(std::vector<double> p_values);

    std::vector<double> const& getFutureValues() const;
    void setFutureValues(std::vector<double> p_futureValues);

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
