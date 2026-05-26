// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace microscopy {

/**
 * Status of the WDI autofocus.
 */
class WdiAutofocusProviderStatus: public Serializable {
public:
    bool inRange {false};
    bool laserOn {false};

    WdiAutofocusProviderStatus();

    WdiAutofocusProviderStatus(
        bool p_inRange,
        bool p_laserOn
    );

    bool operator==(const WdiAutofocusProviderStatus& other) const;

    bool operator!=(const WdiAutofocusProviderStatus& other) const {
        return !(*this == other);
    }

    /**
     * Indicates whether the autofocus is in range.
     */
    bool getInRange() const;
    void setInRange(bool p_inRange);

    /**
     * Indicates whether the laser is turned on.
     */
    bool getLaserOn() const;
    void setLaserOn(bool p_laserOn);

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

} // namespace microscopy
} // namespace motion
} // namespace zaber
