// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/microscopy/microscope_config.h"

namespace zaber {
namespace motion {
namespace requests {

class MicroscopeConfigResponse: public Serializable {
public:
    microscopy::MicroscopeConfig config;

    MicroscopeConfigResponse();

    MicroscopeConfigResponse(
        microscopy::MicroscopeConfig p_config
    );

    bool operator==(const MicroscopeConfigResponse& other) const;

    bool operator!=(const MicroscopeConfigResponse& other) const {
        return !(*this == other);
    }

    microscopy::MicroscopeConfig const& getConfig() const;
    void setConfig(microscopy::MicroscopeConfig p_config);

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
