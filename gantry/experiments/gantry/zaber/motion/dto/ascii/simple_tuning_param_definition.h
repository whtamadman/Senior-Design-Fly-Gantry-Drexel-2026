// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <optional>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Information about a parameter used for the simple tuning method.
 */
class SimpleTuningParamDefinition: public Serializable {
public:
    std::string name;
    std::string minLabel;
    std::string maxLabel;
    std::string dataType;
    std::optional<double> defaultValue;

    SimpleTuningParamDefinition();

    SimpleTuningParamDefinition(
        std::string p_name,
        std::string p_minLabel,
        std::string p_maxLabel,
        std::string p_dataType,
        std::optional<double> p_defaultValue
    );

    SimpleTuningParamDefinition(
        std::string p_name,
        std::string p_minLabel,
        std::string p_maxLabel,
        std::string p_dataType
    );

    bool operator==(const SimpleTuningParamDefinition& other) const;

    bool operator!=(const SimpleTuningParamDefinition& other) const {
        return !(*this == other);
    }

    /**
     * The name of the parameter.
     */
    std::string const& getName() const;
    void setName(std::string p_name);

    /**
     * The human readable description of the effect of a lower value on this setting.
     */
    std::string const& getMinLabel() const;
    void setMinLabel(std::string p_minLabel);

    /**
     * The human readable description of the effect of a higher value on this setting.
     */
    std::string const& getMaxLabel() const;
    void setMaxLabel(std::string p_maxLabel);

    /**
     * How this parameter will be parsed by the tuner.
     */
    std::string const& getDataType() const;
    void setDataType(std::string p_dataType);

    /**
     * The default value of this parameter.
     */
    std::optional<double> getDefaultValue() const;
    void setDefaultValue(std::optional<double> p_defaultValue);

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

} // namespace ascii
} // namespace motion
} // namespace zaber
