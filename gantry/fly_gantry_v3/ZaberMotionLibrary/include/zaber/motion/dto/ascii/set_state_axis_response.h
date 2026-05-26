// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * An object containing any non-blocking issues encountered when loading a saved state to an axis.
 */
class SetStateAxisResponse: public Serializable {
public:
    std::vector<std::string> warnings;
    int axisNumber {0};

    SetStateAxisResponse();

    SetStateAxisResponse(
        std::vector<std::string> p_warnings,
        int p_axisNumber
    );

    bool operator==(const SetStateAxisResponse& other) const;

    bool operator!=(const SetStateAxisResponse& other) const {
        return !(*this == other);
    }

    /**
     * The warnings encountered when applying this state to the given axis.
     */
    std::vector<std::string> const& getWarnings() const;
    void setWarnings(std::vector<std::string> p_warnings);

    /**
     * The number of the axis that was set.
     */
    int getAxisNumber() const;
    void setAxisNumber(int p_axisNumber);

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

} // namespace ascii
} // namespace motion
} // namespace zaber
