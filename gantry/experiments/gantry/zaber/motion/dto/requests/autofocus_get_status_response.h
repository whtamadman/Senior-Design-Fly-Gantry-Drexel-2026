// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/microscopy/autofocus_status.h"

namespace zaber {
namespace motion {
namespace requests {

class AutofocusGetStatusResponse: public Serializable {
public:
    microscopy::AutofocusStatus status;

    AutofocusGetStatusResponse();

    AutofocusGetStatusResponse(
        microscopy::AutofocusStatus p_status
    );

    bool operator==(const AutofocusGetStatusResponse& other) const;

    bool operator!=(const AutofocusGetStatusResponse& other) const {
        return !(*this == other);
    }

    microscopy::AutofocusStatus const& getStatus() const;
    void setStatus(microscopy::AutofocusStatus p_status);

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
