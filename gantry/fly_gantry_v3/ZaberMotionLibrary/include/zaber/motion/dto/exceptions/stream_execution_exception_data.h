// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Contains additional data for StreamExecutionException.
 */
class StreamExecutionExceptionData: public Serializable {
public:
    std::string errorFlag;
    std::string reason;

    StreamExecutionExceptionData();

    StreamExecutionExceptionData(
        std::string p_errorFlag,
        std::string p_reason
    );

    bool operator==(const StreamExecutionExceptionData& other) const;

    bool operator!=(const StreamExecutionExceptionData& other) const {
        return !(*this == other);
    }

    /**
     * The error flag that caused the exception.
     */
    std::string const& getErrorFlag() const;
    void setErrorFlag(std::string p_errorFlag);

    /**
     * The reason for the exception.
     */
    std::string const& getReason() const;
    void setReason(std::string p_reason);

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
