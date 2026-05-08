// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class FindDeviceRequest: public Serializable {
public:
    int interfaceId {0};
    int deviceAddress {0};

    FindDeviceRequest();

    FindDeviceRequest(
        int p_interfaceId,
        int p_deviceAddress
    );

    bool operator==(const FindDeviceRequest& other) const;

    bool operator!=(const FindDeviceRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDeviceAddress() const;
    void setDeviceAddress(int p_deviceAddress);

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
