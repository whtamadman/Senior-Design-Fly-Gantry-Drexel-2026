// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class BoolResponse: public Serializable {
public:
    bool value {false};

    BoolResponse();

    BoolResponse(
        bool p_value
    );

    bool operator==(const BoolResponse& other) const;

    bool operator!=(const BoolResponse& other) const {
        return !(*this == other);
    }

    bool getValue() const;
    void setValue(bool p_value);

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
