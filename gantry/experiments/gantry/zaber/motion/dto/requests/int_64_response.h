// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <cstdint>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class Int64Response: public Serializable {
public:
    int64_t value {0};

    Int64Response();

    Int64Response(
        int64_t p_value
    );

    bool operator==(const Int64Response& other) const;

    bool operator!=(const Int64Response& other) const {
        return !(*this == other);
    }

    int64_t getValue() const;
    void setValue(int64_t p_value);

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
