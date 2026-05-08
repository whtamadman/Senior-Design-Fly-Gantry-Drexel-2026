// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/gcode/translator_config.h"

namespace zaber {
namespace motion {
namespace requests {

class TranslatorCreateFromDeviceRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    std::vector<int> axes;
    std::optional<gcode::TranslatorConfig> config;

    TranslatorCreateFromDeviceRequest();

    TranslatorCreateFromDeviceRequest(
        int p_interfaceId,
        int p_device,
        std::vector<int> p_axes,
        std::optional<gcode::TranslatorConfig> p_config
    );

    TranslatorCreateFromDeviceRequest(
        int p_interfaceId,
        int p_device,
        std::vector<int> p_axes
    );

    bool operator==(const TranslatorCreateFromDeviceRequest& other) const;

    bool operator!=(const TranslatorCreateFromDeviceRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    std::vector<int> const& getAxes() const;
    void setAxes(std::vector<int> p_axes);

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
