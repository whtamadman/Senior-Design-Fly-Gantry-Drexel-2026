// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceSetStorageRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    std::string key;
    std::string value;
    bool encode {false};

    DeviceSetStorageRequest();

    DeviceSetStorageRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        std::string p_key,
        std::string p_value,
        bool p_encode
    );

    bool operator==(const DeviceSetStorageRequest& other) const;

    bool operator!=(const DeviceSetStorageRequest& other) const {
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

    std::string const& getValue() const;
    void setValue(std::string p_value);

    bool getEncode() const;
    void setEncode(bool p_encode);

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
