// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class LockstepGetRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int lockstepGroupId {0};
    Units unit {Units::NATIVE};

    LockstepGetRequest();

    LockstepGetRequest(
        int p_interfaceId,
        int p_device,
        int p_lockstepGroupId,
        Units p_unit
    );

    bool operator==(const LockstepGetRequest& other) const;

    bool operator!=(const LockstepGetRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getLockstepGroupId() const;
    void setLockstepGroupId(int p_lockstepGroupId);

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
