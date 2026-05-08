// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/alert_event.h"

namespace zaber {
namespace motion {
namespace requests {

class AlertEventWrapper: public Serializable {
public:
    int interfaceId {0};
    int sessionId {0};
    ascii::AlertEvent alert;

    AlertEventWrapper();

    AlertEventWrapper(
        int p_interfaceId,
        int p_sessionId,
        ascii::AlertEvent p_alert
    );

    bool operator==(const AlertEventWrapper& other) const;

    bool operator!=(const AlertEventWrapper& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    /**
     * The id of the connection session.
     */
    int getSessionId() const;
    void setSessionId(int p_sessionId);

    ascii::AlertEvent const& getAlert() const;
    void setAlert(ascii::AlertEvent p_alert);

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
