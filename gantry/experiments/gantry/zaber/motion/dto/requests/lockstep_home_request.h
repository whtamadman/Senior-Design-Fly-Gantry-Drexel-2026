// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class LockstepHomeRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int lockstepGroupId {0};
    bool waitUntilIdle {false};

    LockstepHomeRequest();

    LockstepHomeRequest(
        int p_interfaceId,
        int p_device,
        int p_lockstepGroupId,
        bool p_waitUntilIdle
    );

    bool operator==(const LockstepHomeRequest& other) const;

    bool operator!=(const LockstepHomeRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getLockstepGroupId() const;
    void setLockstepGroupId(int p_lockstepGroupId);

    bool getWaitUntilIdle() const;
    void setWaitUntilIdle(bool p_waitUntilIdle);

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
