// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceGetWarningsRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    bool clear {false};

    DeviceGetWarningsRequest();

    DeviceGetWarningsRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        bool p_clear
    );

    bool operator==(const DeviceGetWarningsRequest& other) const;

    bool operator!=(const DeviceGetWarningsRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    bool getClear() const;
    void setClear(bool p_clear);

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
