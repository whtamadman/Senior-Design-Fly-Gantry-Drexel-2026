// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class LockstepEnableRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int lockstepGroupId {0};
    std::vector<int> axes;

    LockstepEnableRequest();

    LockstepEnableRequest(
        int p_interfaceId,
        int p_device,
        int p_lockstepGroupId,
        std::vector<int> p_axes
    );

    bool operator==(const LockstepEnableRequest& other) const;

    bool operator!=(const LockstepEnableRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getLockstepGroupId() const;
    void setLockstepGroupId(int p_lockstepGroupId);

    std::vector<int> const& getAxes() const;
    void setAxes(std::vector<int> p_axes);

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
