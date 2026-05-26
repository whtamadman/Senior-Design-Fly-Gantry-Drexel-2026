// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class LockstepGetAxisNumbersResponse: public Serializable {
public:
    std::vector<int> axes;

    LockstepGetAxisNumbersResponse();

    LockstepGetAxisNumbersResponse(
        std::vector<int> p_axes
    );

    bool operator==(const LockstepGetAxisNumbersResponse& other) const;

    bool operator!=(const LockstepGetAxisNumbersResponse& other) const {
        return !(*this == other);
    }

    std::vector<int> const& getAxes() const;
    void setAxes(std::vector<int> p_axes);

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
