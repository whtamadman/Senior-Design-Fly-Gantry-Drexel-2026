// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceGetStorageRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    std::string key;
    bool decode {false};

    DeviceGetStorageRequest();

    DeviceGetStorageRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        std::string p_key,
        bool p_decode
    );

    bool operator==(const DeviceGetStorageRequest& other) const;

    bool operator!=(const DeviceGetStorageRequest& other) const {
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

    bool getDecode() const;
    void setDecode(bool p_decode);

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
