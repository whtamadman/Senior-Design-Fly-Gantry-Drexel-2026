// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/ascii/trigger.h"
#include "zaber/motion/dto/ascii/trigger_enabled_state.h"
#include "zaber/motion/dto/ascii/trigger_state.h"

namespace zaber {
namespace motion {
namespace ascii {


/**
 * Class providing access to device triggers.
 * Please note that the Triggers API is currently an experimental feature.
 * Requires at least Firmware 7.06.
 */
class Triggers {
public:
    Triggers(Device device);

    /**
     * Get the number of triggers for this device.
     * @return Number of triggers for this device.
     */
    int getNumberOfTriggers();
    /**
     * Get the number of actions for each trigger for this device.
     * @return Number of actions for each trigger for this device.
     */
    int getNumberOfActions();
    /**
     * Get a specific trigger for this device.
     * @param triggerNumber The number of the trigger to control. Trigger numbers start at 1.
     * @return Trigger instance.
     */
    Trigger getTrigger(int triggerNumber);
    /**
     * Get the state for every trigger for this device.
     * @return Complete state for every trigger.
     */
    std::vector<TriggerState> getTriggerStates();
    /**
     * Gets the enabled state for every trigger for this device.
     * @return Whether triggers are enabled and the number of times they will fire.
     */
    std::vector<TriggerEnabledState> getEnabledStates();
    /**
     * Gets the labels for every trigger for this device.
     * @return The labels for every trigger for this device. If a trigger has no label, the value will be an empty string.
     */
    std::vector<std::string> getAllLabels();
    /**
     * Device that these triggers belong to.
     */
    Device getDevice() const;
protected:
    Device _device;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
