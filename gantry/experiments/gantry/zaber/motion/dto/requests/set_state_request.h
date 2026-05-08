// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class SetStateRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    std::string state;
    bool deviceOnly {false};

    SetStateRequest();

    SetStateRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        std::string p_state,
        bool p_deviceOnly
    );

    bool operator==(const SetStateRequest& other) const;

    bool operator!=(const SetStateRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    std::string const& getState() const;
    void setState(std::string p_state);

    bool getDeviceOnly() const;
    void setDeviceOnly(bool p_deviceOnly);

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
