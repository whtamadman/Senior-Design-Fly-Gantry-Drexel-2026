// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Contains additional data for InvalidResponseException.
 */
class InvalidResponseExceptionData: public Serializable {
public:
    std::string response;

    InvalidResponseExceptionData();

    InvalidResponseExceptionData(
        std::string p_response
    );

    bool operator==(const InvalidResponseExceptionData& other) const;

    bool operator!=(const InvalidResponseExceptionData& other) const {
        return !(*this == other);
    }

    /**
     * The response data.
     */
    std::string const& getResponse() const;
    void setResponse(std::string p_response);

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

} // namespace exceptions
} // namespace motion
} // namespace zaber
