// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/microscopy/microscope_config.h"

namespace zaber {
namespace motion {
namespace requests {

class MicroscopeInitRequest: public Serializable {
public:
    int interfaceId {0};
    microscopy::MicroscopeConfig config;
    bool force {false};

    MicroscopeInitRequest();

    MicroscopeInitRequest(
        int p_interfaceId,
        microscopy::MicroscopeConfig p_config,
        bool p_force
    );

    bool operator==(const MicroscopeInitRequest& other) const;

    bool operator!=(const MicroscopeInitRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    microscopy::MicroscopeConfig const& getConfig() const;
    void setConfig(microscopy::MicroscopeConfig p_config);

    bool getForce() const;
    void setForce(bool p_force);

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
