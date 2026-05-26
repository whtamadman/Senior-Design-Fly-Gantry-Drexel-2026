// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Contains additional data for StreamMovementFailedException.
 */
class StreamMovementFailedExceptionData: public Serializable {
public:
    std::vector<std::string> warnings;
    std::string reason;

    StreamMovementFailedExceptionData();

    StreamMovementFailedExceptionData(
        std::vector<std::string> p_warnings,
        std::string p_reason
    );

    bool operator==(const StreamMovementFailedExceptionData& other) const;

    bool operator!=(const StreamMovementFailedExceptionData& other) const {
        return !(*this == other);
    }

    /**
     * The full list of warnings.
     */
    std::vector<std::string> const& getWarnings() const;
    void setWarnings(std::vector<std::string> p_warnings);

    /**
     * The reason for the Exception.
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
