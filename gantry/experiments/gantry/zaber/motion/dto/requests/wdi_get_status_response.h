// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/microscopy/wdi_autofocus_provider_status.h"

namespace zaber {
namespace motion {
namespace requests {

class WdiGetStatusResponse: public Serializable {
public:
    microscopy::WdiAutofocusProviderStatus status;

    WdiGetStatusResponse();

    WdiGetStatusResponse(
        microscopy::WdiAutofocusProviderStatus p_status
    );

    bool operator==(const WdiGetStatusResponse& other) const;

    bool operator!=(const WdiGetStatusResponse& other) const {
        return !(*this == other);
    }

    microscopy::WdiAutofocusProviderStatus const& getStatus() const;
    void setStatus(microscopy::WdiAutofocusProviderStatus p_status);

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
