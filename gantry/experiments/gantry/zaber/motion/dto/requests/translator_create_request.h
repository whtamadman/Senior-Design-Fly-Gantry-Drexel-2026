// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/gcode/device_definition.h"
#include "zaber/motion/dto/gcode/translator_config.h"

namespace zaber {
namespace motion {
namespace requests {

class TranslatorCreateRequest: public Serializable {
public:
    gcode::DeviceDefinition definition;
    std::optional<gcode::TranslatorConfig> config;

    TranslatorCreateRequest();

    TranslatorCreateRequest(
        gcode::DeviceDefinition p_definition,
        std::optional<gcode::TranslatorConfig> p_config
    );

    TranslatorCreateRequest(
        gcode::DeviceDefinition p_definition
    );

    bool operator==(const TranslatorCreateRequest& other) const;

    bool operator!=(const TranslatorCreateRequest& other) const {
        return !(*this == other);
    }

    gcode::DeviceDefinition const& getDefinition() const;
    void setDefinition(gcode::DeviceDefinition p_definition);

    std::optional<gcode::TranslatorConfig> const& getConfig() const;
    void setConfig(std::optional<gcode::TranslatorConfig> p_config);

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
