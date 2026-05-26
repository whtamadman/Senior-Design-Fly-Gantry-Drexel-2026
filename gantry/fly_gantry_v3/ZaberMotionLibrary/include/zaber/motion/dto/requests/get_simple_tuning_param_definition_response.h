// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/simple_tuning_param_definition.h"

namespace zaber {
namespace motion {
namespace requests {

class GetSimpleTuningParamDefinitionResponse: public Serializable {
public:
    std::vector<ascii::SimpleTuningParamDefinition> params;

    GetSimpleTuningParamDefinitionResponse();

    GetSimpleTuningParamDefinitionResponse(
        std::vector<ascii::SimpleTuningParamDefinition> p_params
    );

    bool operator==(const GetSimpleTuningParamDefinitionResponse& other) const;

    bool operator!=(const GetSimpleTuningParamDefinitionResponse& other) const {
        return !(*this == other);
    }

    std::vector<ascii::SimpleTuningParamDefinition> const& getParams() const;
    void setParams(std::vector<ascii::SimpleTuningParamDefinition> p_params);

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
