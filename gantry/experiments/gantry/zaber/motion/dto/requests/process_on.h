// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class ProcessOn: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    bool on {false};
    double duration {0.0};
    Units unit {Units::NATIVE};

    ProcessOn();

    ProcessOn(
        int p_interfaceId,
        int p_device,
        int p_axis,
        bool p_on,
        double p_duration,
        Units p_unit
    );

    bool operator==(const ProcessOn& other) const;

    bool operator!=(const ProcessOn& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    bool getOn() const;
    void setOn(bool p_on);

    double getDuration() const;
    void setDuration(double p_duration);

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
