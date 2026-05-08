// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class SetInterfaceChecksumEnabledRequest: public Serializable {
public:
    int interfaceId {0};
    bool isEnabled {false};

    SetInterfaceChecksumEnabledRequest();

    SetInterfaceChecksumEnabledRequest(
        int p_interfaceId,
        bool p_isEnabled
    );

    bool operator==(const SetInterfaceChecksumEnabledRequest& other) const;

    bool operator!=(const SetInterfaceChecksumEnabledRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    bool getIsEnabled() const;
    void setIsEnabled(bool p_isEnabled);

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
