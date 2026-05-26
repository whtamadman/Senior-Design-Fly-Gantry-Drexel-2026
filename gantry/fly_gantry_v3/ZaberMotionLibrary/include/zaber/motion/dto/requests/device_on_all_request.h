// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceOnAllRequest: public Serializable {
public:
    int interfaceId {0};
    bool waitUntilIdle {false};

    DeviceOnAllRequest();

    DeviceOnAllRequest(
        int p_interfaceId,
        bool p_waitUntilIdle
    );

    bool operator==(const DeviceOnAllRequest& other) const;

    bool operator!=(const DeviceOnAllRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

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
