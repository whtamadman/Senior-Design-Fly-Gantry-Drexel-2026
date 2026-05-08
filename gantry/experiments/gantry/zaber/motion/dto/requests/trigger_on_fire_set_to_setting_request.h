// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/trigger_action.h"
#include "zaber/motion/dto/ascii/trigger_operation.h"

namespace zaber {
namespace motion {
namespace requests {

class TriggerOnFireSetToSettingRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int triggerNumber {0};
    ascii::TriggerAction action {0};
    int axis {0};
    std::string setting;
    ascii::TriggerOperation operation {0};
    int fromAxis {0};
    std::string fromSetting;

    TriggerOnFireSetToSettingRequest();

    TriggerOnFireSetToSettingRequest(
        int p_interfaceId,
        int p_device,
        int p_triggerNumber,
        ascii::TriggerAction p_action,
        int p_axis,
        std::string p_setting,
        ascii::TriggerOperation p_operation,
        int p_fromAxis,
        std::string p_fromSetting
    );

    bool operator==(const TriggerOnFireSetToSettingRequest& other) const;

    bool operator!=(const TriggerOnFireSetToSettingRequest& other) const {
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

    int getFromAxis() const;
    void setFromAxis(int p_fromAxis);

    std::string const& getFromSetting() const;
    void setFromSetting(std::string p_fromSetting);

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
