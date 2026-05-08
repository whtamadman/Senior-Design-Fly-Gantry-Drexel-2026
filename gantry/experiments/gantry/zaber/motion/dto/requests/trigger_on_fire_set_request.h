// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/trigger_action.h"
#include "zaber/motion/dto/ascii/trigger_operation.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class TriggerOnFireSetRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int triggerNumber {0};
    ascii::TriggerAction action {0};
    int axis {0};
    std::string setting;
    ascii::TriggerOperation operation {0};
    double value {0.0};
    Units unit {Units::NATIVE};

    TriggerOnFireSetRequest();

    TriggerOnFireSetRequest(
        int p_interfaceId,
        int p_device,
        int p_triggerNumber,
        ascii::TriggerAction p_action,
        int p_axis,
        std::string p_setting,
        ascii::TriggerOperation p_operation,
        double p_value,
        Units p_unit
    );

    bool operator==(const TriggerOnFireSetRequest& other) const;

    bool operator!=(const TriggerOnFireSetRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getTriggerNumber() const;
    void setTriggerNumber(int p_triggerNumber);

    ascii::TriggerAction const& getAction() const;
    void setAction(ascii::TriggerAction p_action);

    int getAxis() const;
    void setAxis(int p_axis);

    std::string const& getSetting() const;
    void setSetting(std::string p_setting);

    ascii::TriggerOperation const& getOperation() const;
    void setOperation(ascii::TriggerOperation p_operation);

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
