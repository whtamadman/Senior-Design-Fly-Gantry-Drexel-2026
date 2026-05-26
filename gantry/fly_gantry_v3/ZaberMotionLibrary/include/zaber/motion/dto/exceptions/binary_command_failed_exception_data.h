// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Contains additional data for BinaryCommandFailedException.
 */
class BinaryCommandFailedExceptionData: public Serializable {
public:
    int responseData {0};

    BinaryCommandFailedExceptionData();

    BinaryCommandFailedExceptionData(
        int p_responseData
    );

    bool operator==(const BinaryCommandFailedExceptionData& other) const;

    bool operator!=(const BinaryCommandFailedExceptionData& other) const {
        return !(*this == other);
    }

    /**
     * The response data.
     */
    int getResponseData() const;
    void setResponseData(int p_responseData);

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
