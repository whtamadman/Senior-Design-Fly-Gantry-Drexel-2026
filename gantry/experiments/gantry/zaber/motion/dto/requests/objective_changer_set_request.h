// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class ObjectiveChangerSetRequest: public Serializable {
public:
    int interfaceId {0};
    int turretAddress {0};
    int focusAddress {0};
    int focusAxis {0};
    double value {0.0};
    Units unit {Units::NATIVE};

    ObjectiveChangerSetRequest();

    ObjectiveChangerSetRequest(
        int p_interfaceId,
        int p_turretAddress,
        int p_focusAddress,
        int p_focusAxis,
        double p_value,
        Units p_unit
    );

    bool operator==(const ObjectiveChangerSetRequest& other) const;

    bool operator!=(const ObjectiveChangerSetRequest& other) const {
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

    double getValue() const;
    void setValue(double p_value);

    Units getUnit() const;
    void setUnit(Units p_unit);

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
