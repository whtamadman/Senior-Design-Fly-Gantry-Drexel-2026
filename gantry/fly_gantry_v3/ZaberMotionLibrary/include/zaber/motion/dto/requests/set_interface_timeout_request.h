// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class SetInterfaceTimeoutRequest: public Serializable {
public:
    int interfaceId {0};
    int timeout {0};

    SetInterfaceTimeoutRequest();

    SetInterfaceTimeoutRequest(
        int p_interfaceId,
        int p_timeout
    );

    bool operator==(const SetInterfaceTimeoutRequest& other) const;

    bool operator!=(const SetInterfaceTimeoutRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

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
