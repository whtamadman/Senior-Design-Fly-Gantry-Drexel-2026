// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class LockstepSetRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int lockstepGroupId {0};
    double value {0.0};
    Units unit {Units::NATIVE};
    int axisIndex {0};

    LockstepSetRequest();

    LockstepSetRequest(
        int p_interfaceId,
        int p_device,
        int p_lockstepGroupId,
        double p_value,
        Units p_unit,
        int p_axisIndex
    );

    bool operator==(const LockstepSetRequest& other) const;

    bool operator!=(const LockstepSetRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getLockstepGroupId() const;
    void setLockstepGroupId(int p_lockstepGroupId);

    double getValue() const;
    void setValue(double p_value);

    Units getUnit() const;
    void setUnit(Units p_unit);

    int getAxisIndex() const;
    void setAxisIndex(int p_axisIndex);

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
