// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/dto/ascii/io_port_type.h"
#include "zaber/motion/dto/ascii/trigger_action.h"
#include "zaber/motion/dto/ascii/trigger_condition.h"
#include "zaber/motion/dto/ascii/trigger_enabled_state.h"
#include "zaber/motion/dto/ascii/trigger_operation.h"
#include "zaber/motion/dto/ascii/trigger_state.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {


/**
 * A handle for a trigger with this number on the device.
 * Triggers allow setting up actions that occur when a certain condition has been met or an event has occurred.
 * Please note that the Triggers API is currently an experimental feature.
 * Requires at least Firmware 7.06.
 */
class Trigger {
public:
    Trigger(Device device, int triggerNumber);

    /**
     * Enables the trigger.
     * Once a trigger is enabled, it will fire whenever its condition transitions from false to true.
     * If a trigger condition is true when a disabled trigger is enabled, the trigger will fire immediately.
     * @param count Number of times the trigger will fire before disabling itself.
     * If count is not specified, or 0, the trigger will fire indefinitely.
     */
    void enable(int count = 0);
    /**
     * Disables the trigger.
     * Once disabled, the trigger will not fire and trigger actions will not run, even if trigger conditions are met.
     */
    void disable();
    /**
     * Gets the state of the trigger.
     * @return Complete state of the trigger.
     */
    TriggerState getState();
    /**
     * Gets the enabled state of the trigger.
     * @return Whether the trigger is enabled and the number of times it will fire.
     */
    TriggerEnabledState getEnabledState();
    /**
     * Set a generic trigger condition.
     * @param condition The condition to set for this trigger.
     */
    void fireWhen(const std::string& condition);
    /**
     * Set a trigger condition for when an encoder position has changed by a specific distance.
     * @param axis The axis to monitor for this condition.
     * May be set to 0 on single-axis devices only.
     * @param distance The measured encoder distance between trigger fires.
     * @param unit Units of dist.
     */
    void fireWhenEncoderDistanceTravelled(int axis, double distance, Units unit = Units::NATIVE);
    /**
     * Set a trigger condition for when an axis position has changed by a specific distance.
     * @param axis The axis to monitor for this condition.
     * May be set to 0 on single-axis devices only.
     * @param distance The measured distance between trigger fires.
     * @param unit Units of dist.
     */
    void fireWhenDistanceTravelled(int axis, double distance, Units unit = Units::NATIVE);
    /**
     * Set a trigger condition based on an IO channel value.
     * @param portType The type of IO channel to monitor.
     * @param channel The IO channel to monitor.
     * @param triggerCondition Comparison operator.
     * @param value Comparison value.
     */
    void fireWhenIo(IoPortType portType, int channel, TriggerCondition triggerCondition, double value);
    /**
     * Set a trigger condition based on a setting value.
     * @param axis The axis to monitor for this condition.
     * Set to 0 for device-scope settings.
     * @param setting The setting to monitor.
     * @param triggerCondition Comparison operator.
     * @param value Comparison value.
     * @param unit Units of value.
     */
    void fireWhenSetting(int axis, const std::string& setting, TriggerCondition triggerCondition, double value, Units unit = Units::NATIVE);
    /**
     * Set a trigger condition based on an absolute setting value.
     * @param axis The axis to monitor for this condition.
     * Set to 0 for device-scope settings.
     * @param setting The setting to monitor.
     * @param triggerCondition Comparison operator.
     * @param value Comparison value.
     * @param unit Units of value.
     */
    void fireWhenAbsoluteSetting(int axis, const std::string& setting, TriggerCondition triggerCondition, double value, Units unit = Units::NATIVE);
    /**
     * Set a trigger condition based on a time interval.
     * @param interval The time interval between trigger fires.
     * @param unit Units of time.
     */
    void fireAtInterval(double interval, Units unit = Units::NATIVE);
    /**
     * Set a command to be a trigger action.
     * @param action The action number to assign the command to.
     * @param axis The axis to on which to run this command.
     * Set to 0 for device-scope settings or to run command on all axes.
     * @param command The command to run when the action is triggered.
     */
    void onFire(TriggerAction action, int axis, const std::string& command);
    /**
     * Set a trigger action to update a setting.
     * @param action The action number to assign the command to.
     * @param axis The axis on which to change the setting.
     * Set to 0 to change the setting for the device.
     * @param setting The name of the setting to change.
     * @param operation The operation to apply to the setting.
     * @param value Operation value.
     * @param unit Units of value.
     */
    void onFireSet(TriggerAction action, int axis, const std::string& setting, TriggerOperation operation, double value, Units unit = Units::NATIVE);
    /**
     * Set a trigger action to update a setting with the value of another setting.
     * @param action The action number to assign the command to.
     * @param axis The axis on which to change the setting.
     * Set to 0 to change the setting for the device.
     * @param setting The name of the setting to change.
     * Must have either integer or boolean type.
     * @param operation The operation to apply to the setting.
     * @param fromAxis The axis from which to read the setting.
     * Set to 0 to read the setting from the device.
     * @param fromSetting The name of the setting to read.
     * Must have either integer or boolean type.
     */
    void onFireSetToSetting(TriggerAction action, int axis, const std::string& setting, TriggerOperation operation, int fromAxis, const std::string& fromSetting);
    /**
     * Clear a trigger action.
     * @param action The action number to clear.
     * The default option is to clear all actions.
     */
    void clearAction(TriggerAction action = TriggerAction::ALL);
    /**
     * Returns the label for the trigger.
     * @return The label for the trigger.
     */
    std::string getLabel();
    /**
     * Sets the label for the trigger.
     * @param label The label to set for this trigger.
     * If no value or an empty string is provided, this label is deleted.
     */
    void setLabel(const std::optional<std::string>& label);
    /**
     * Device that this trigger belongs to.
     */
    Device getDevice() const;
    /**
     * Number of this trigger.
     */
    int getTriggerNumber() const;
protected:
    Device _device;
    int _triggerNumber;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
