// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class StringResponse: public Serializable {
public:
    std::string value;

    StringResponse();

    StringResponse(
        std::string p_value
    );

    bool operator==(const StringResponse& other) const;

    bool operator!=(const StringResponse& other) const {
        return !(*this == other);
    }

    std::string const& getValue() const;
    void setValue(std::string p_value);

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
