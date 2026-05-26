// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class ObjectiveChangerRequest: public Serializable {
public:
    int interfaceId {0};
    int turretAddress {0};
    int focusAddress {0};
    int focusAxis {0};

    ObjectiveChangerRequest();

    ObjectiveChangerRequest(
        int p_interfaceId,
        int p_turretAddress,
        int p_focusAddress,
        int p_focusAxis
    );

    bool operator==(const ObjectiveChangerRequest& other) const;

    bool operator!=(const ObjectiveChangerRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getTurretAddress() const;
    void setTurretAddress(int p_turretAddress);

    int getFocusAddress() const;
    void setFocusAddress(int p_focusAddress);

    int getFocusAxis() const;
    void setFocusAxis(int p_focusAxis);

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
