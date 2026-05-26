// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class GatewayRequest: public Serializable {
public:
    std::string request;

    GatewayRequest();

    GatewayRequest(
        std::string p_request
    );

    bool operator==(const GatewayRequest& other) const;

    bool operator!=(const GatewayRequest& other) const {
        return !(*this == other);
    }

    std::string const& getRequest() const;
    void setRequest(std::string p_request);

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
