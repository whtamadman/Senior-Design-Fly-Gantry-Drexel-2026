// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/gcode/translator_config.h"

namespace zaber {
namespace motion {
namespace requests {

class TranslatorCreateLiveRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int streamId {0};
    std::optional<gcode::TranslatorConfig> config;

    TranslatorCreateLiveRequest();

    TranslatorCreateLiveRequest(
        int p_interfaceId,
        int p_device,
        int p_streamId,
        std::optional<gcode::TranslatorConfig> p_config
    );

    TranslatorCreateLiveRequest(
        int p_interfaceId,
        int p_device,
        int p_streamId
    );

    bool operator==(const TranslatorCreateLiveRequest& other) const;

    bool operator!=(const TranslatorCreateLiveRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getStreamId() const;
    void setStreamId(int p_streamId);

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
