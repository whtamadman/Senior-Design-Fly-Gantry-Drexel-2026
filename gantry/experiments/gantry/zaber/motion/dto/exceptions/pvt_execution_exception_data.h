// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/exceptions/invalid_pvt_point.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Contains additional data for PvtExecutionException.
 */
class PvtExecutionExceptionData: public Serializable {
public:
    std::string errorFlag;
    std::string reason;
    std::vector<InvalidPvtPoint> invalidPoints;

    PvtExecutionExceptionData();

    PvtExecutionExceptionData(
        std::string p_errorFlag,
        std::string p_reason,
        std::vector<InvalidPvtPoint> p_invalidPoints
    );

    bool operator==(const PvtExecutionExceptionData& other) const;

    bool operator!=(const PvtExecutionExceptionData& other) const {
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
     * A list of points that cause the error (if applicable).
     */
    std::vector<InvalidPvtPoint> const& getInvalidPoints() const;
    void setInvalidPoints(std::vector<InvalidPvtPoint> p_invalidPoints);

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
