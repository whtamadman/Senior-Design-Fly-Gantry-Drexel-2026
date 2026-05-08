// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/named_parameter.h"

namespace zaber {
namespace motion {
namespace requests {

class AutofocusGetObjectiveParamsResponse: public Serializable {
public:
    std::vector<NamedParameter> parameters;

    AutofocusGetObjectiveParamsResponse();

    AutofocusGetObjectiveParamsResponse(
        std::vector<NamedParameter> p_parameters
    );

    bool operator==(const AutofocusGetObjectiveParamsResponse& other) const;

    bool operator!=(const AutofocusGetObjectiveParamsResponse& other) const {
        return !(*this == other);
    }

    std::vector<NamedParameter> const& getParameters() const;
    void setParameters(std::vector<NamedParameter> p_parameters);

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
