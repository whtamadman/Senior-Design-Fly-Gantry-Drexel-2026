// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/requests/response_type.h"
#include "zaber/motion/dto/requests/errors.h"

namespace zaber {
namespace motion {
namespace requests {

class GatewayResponse: public Serializable {
public:
    ResponseType response {0};
    Errors errorType {0};
    std::string errorMessage;

    GatewayResponse();

    GatewayResponse(
        ResponseType p_response,
        Errors p_errorType,
        std::string p_errorMessage
    );

    bool operator==(const GatewayResponse& other) const;

    bool operator!=(const GatewayResponse& other) const {
        return !(*this == other);
    }

    ResponseType const& getResponse() const;
    void setResponse(ResponseType p_response);

    Errors const& getErrorType() const;
    void setErrorType(Errors p_errorType);

    std::string const& getErrorMessage() const;
    void setErrorMessage(std::string p_errorMessage);

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
