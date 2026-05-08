// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class WaitToRespondRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    double timeout {0.0};

    WaitToRespondRequest();

    WaitToRespondRequest(
        int p_interfaceId,
        int p_device,
        double p_timeout
    );

    bool operator==(const WaitToRespondRequest& other) const;

    bool operator!=(const WaitToRespondRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    double getTimeout() const;
    void setTimeout(double p_timeout);

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
