// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DiscoverMdnsRequest: public Serializable {
public:
    int duration {0};
    std::optional<std::string> interfaceIpAddress;

    DiscoverMdnsRequest();

    DiscoverMdnsRequest(
        int p_duration,
        std::optional<std::string> p_interfaceIpAddress
    );

    DiscoverMdnsRequest(
        int p_duration
    );

    bool operator==(const DiscoverMdnsRequest& other) const;

    bool operator!=(const DiscoverMdnsRequest& other) const {
        return !(*this == other);
    }

    int getDuration() const;
    void setDuration(int p_duration);

    std::optional<std::string> const& getInterfaceIpAddress() const;
    void setInterfaceIpAddress(std::optional<std::string> p_interfaceIpAddress);

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
