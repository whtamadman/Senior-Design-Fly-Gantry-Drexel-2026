// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class DoubleResponse: public Serializable {
public:
    double value {0.0};

    DoubleResponse();

    DoubleResponse(
        double p_value
    );

    bool operator==(const DoubleResponse& other) const;

    bool operator!=(const DoubleResponse& other) const {
        return !(*this == other);
    }

    double getValue() const;
    void setValue(double p_value);

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
