// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class TriggerFireWhenDistanceTravelledRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int triggerNumber {0};
    int axis {0};
    double distance {0.0};
    Units unit {Units::NATIVE};

    TriggerFireWhenDistanceTravelledRequest();

    TriggerFireWhenDistanceTravelledRequest(
        int p_interfaceId,
        int p_device,
        int p_triggerNumber,
        int p_axis,
        double p_distance,
        Units p_unit
    );

    bool operator==(const TriggerFireWhenDistanceTravelledRequest& other) const;

    bool operator!=(const TriggerFireWhenDistanceTravelledRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getTriggerNumber() const;
    void setTriggerNumber(int p_triggerNumber);

    int getAxis() const;
    void setAxis(int p_axis);

    double getDistance() const;
    void setDistance(double p_distance);

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
