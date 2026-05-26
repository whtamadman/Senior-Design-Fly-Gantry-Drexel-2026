// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperOpenConnectionRequest: public Serializable {
public:
    std::string portName;
    int deviceAddress {0};
    int timeout {0};

    Ge1GripperOpenConnectionRequest();

    Ge1GripperOpenConnectionRequest(
        std::string p_portName,
        int p_deviceAddress,
        int p_timeout
    );

    bool operator==(const Ge1GripperOpenConnectionRequest& other) const;

    bool operator!=(const Ge1GripperOpenConnectionRequest& other) const {
        return !(*this == other);
    }

    std::string const& getPortName() const;
    void setPortName(std::string p_portName);

    int getDeviceAddress() const;
    void setDeviceAddress(int p_deviceAddress);

    int getTimeout() const;
    void setTimeout(int p_timeout);

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
