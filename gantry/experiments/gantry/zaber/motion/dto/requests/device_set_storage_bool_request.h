// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceSetStorageBoolRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    std::string key;
    bool value {false};

    DeviceSetStorageBoolRequest();

    DeviceSetStorageBoolRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        std::string p_key,
        bool p_value
    );

    bool operator==(const DeviceSetStorageBoolRequest& other) const;

    bool operator!=(const DeviceSetStorageBoolRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    std::string const& getKey() const;
    void setKey(std::string p_key);

    bool getValue() const;
    void setValue(bool p_value);

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
