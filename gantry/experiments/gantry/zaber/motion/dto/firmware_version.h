// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#pragma push_macro("major")
#undef major
#pragma push_macro("minor")
#undef minor

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {

/**
 * Class representing version of firmware in the controller.
 */
class FirmwareVersion: public Serializable {
public:
    int major {0};
    int minor {0};
    int build {0};

    FirmwareVersion();

    FirmwareVersion(
        int p_major,
        int p_minor,
        int p_build
    );

    bool operator==(const FirmwareVersion& other) const;

    bool operator!=(const FirmwareVersion& other) const {
        return !(*this == other);
    }

    /**
     * Major version number.
     */
    int getMajor() const;
    void setMajor(int p_major);

    /**
     * Minor version number.
     */
    int getMinor() const;
    void setMinor(int p_minor);

    /**
     * Build version number.
     */
    int getBuild() const;
    void setBuild(int p_build);

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

} // namespace motion
} // namespace zaber

#pragma pop_macro("major")
#pragma pop_macro("minor")
