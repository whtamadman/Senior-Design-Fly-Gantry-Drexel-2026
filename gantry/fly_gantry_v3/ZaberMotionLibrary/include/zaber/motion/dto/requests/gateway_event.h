// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class GatewayEvent: public Serializable {
public:
    std::string event;

    GatewayEvent();

    GatewayEvent(
        std::string p_event
    );

    bool operator==(const GatewayEvent& other) const;

    bool operator!=(const GatewayEvent& other) const {
        return !(*this == other);
    }

    std::string const& getEvent() const;
    void setEvent(std::string p_event);

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
