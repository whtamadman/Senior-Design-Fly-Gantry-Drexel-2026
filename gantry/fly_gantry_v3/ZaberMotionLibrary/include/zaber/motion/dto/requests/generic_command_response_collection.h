// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/response.h"

namespace zaber {
namespace motion {
namespace requests {

class GenericCommandResponseCollection: public Serializable {
public:
    std::vector<ascii::Response> responses;

    GenericCommandResponseCollection();

    GenericCommandResponseCollection(
        std::vector<ascii::Response> p_responses
    );

    bool operator==(const GenericCommandResponseCollection& other) const;

    bool operator!=(const GenericCommandResponseCollection& other) const {
        return !(*this == other);
    }

    std::vector<ascii::Response> const& getResponses() const;
    void setResponses(std::vector<ascii::Response> p_responses);

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
