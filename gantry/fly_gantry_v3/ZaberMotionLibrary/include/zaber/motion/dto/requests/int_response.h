// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class IntResponse: public Serializable {
public:
    int value {0};

    IntResponse();

    IntResponse(
        int p_value
    );

    bool operator==(const IntResponse& other) const;

    bool operator!=(const IntResponse& other) const {
        return !(*this == other);
    }

    int getValue() const;
    void setValue(int p_value);

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
