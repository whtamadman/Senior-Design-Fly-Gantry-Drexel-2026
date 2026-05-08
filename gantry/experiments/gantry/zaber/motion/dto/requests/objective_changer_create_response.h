// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class ObjectiveChangerCreateResponse: public Serializable {
public:
    int turret {0};
    int focusAddress {0};
    int focusAxis {0};

    ObjectiveChangerCreateResponse();

    ObjectiveChangerCreateResponse(
        int p_turret,
        int p_focusAddress,
        int p_focusAxis
    );

    bool operator==(const ObjectiveChangerCreateResponse& other) const;

    bool operator!=(const ObjectiveChangerCreateResponse& other) const {
        return !(*this == other);
    }

    int getTurret() const;
    void setTurret(int p_turret);

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
