// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class StringArrayResponse: public Serializable {
public:
    std::vector<std::string> values;

    StringArrayResponse();

    StringArrayResponse(
        std::vector<std::string> p_values
    );

    bool operator==(const StringArrayResponse& other) const;

    bool operator!=(const StringArrayResponse& other) const {
        return !(*this == other);
    }

    std::vector<std::string> const& getValues() const;
    void setValues(std::vector<std::string> p_values);

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
