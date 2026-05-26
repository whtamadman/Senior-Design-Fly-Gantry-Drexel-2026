// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <utility>
#include "zaber/motion/ascii/connection.h"
#include "zaber/motion/ascii/device.h"

namespace zaber {
namespace motion {
namespace microscopy {


/**
 * An abstraction over a device and it's digital output channel.
 */
class CameraTrigger {
    using BaseConnection = zaber::motion::ascii::BaseConnection;
    using Connection = zaber::motion::ascii::Connection;
    using Device = zaber::motion::ascii::Device;

public:
    struct TriggerOptions {
        // If false, the method does not wait until the trigger pulse is finished.
        bool wait {true};
    };

    /**
     * Creates instance of `CameraTrigger` based on the given device and digital output channel.
     */
    CameraTrigger(Device device, int channel);

    CameraTrigger();

    /**
     * Triggers the camera.
     * Schedules trigger pulse on the digital output channel.
     * By default, the method waits until the trigger pulse is finished.
     * @param pulseWidth The time duration of the trigger pulse.
     * Depending on the camera setting, the argument can be use to specify exposure.
     * @param unit Units of time.
     * @param wait If false, the method does not wait until the trigger pulse is finished.
     */
    void trigger(double pulseWidth, Units unit = Units::NATIVE, bool wait = true);

    /**
     * Triggers the camera.
     * Schedules trigger pulse on the digital output channel.
     * By default, the method waits until the trigger pulse is finished.
     * @param pulseWidth The time duration of the trigger pulse.
     * Depending on the camera setting, the argument can be use to specify exposure.
     * @param unit Units of time.
     * @param options A struct of type TriggerOptions. It has the following members:
     * * `wait`: If false, the method does not wait until the trigger pulse is finished.
     */
    void trigger(double pulseWidth, Units unit, const CameraTrigger::TriggerOptions& options);
    /**
     * Returns a string that represents the device.
     * @return A string that represents the device.
     */
    std::string toString() const;
    /**
     * The device whose digital output triggers the camera.
     */
    Device getDevice() const;
    /**
     * The digital output channel that triggers the camera.
     */
    int getChannel() const;
protected:
    Device _device;
    int _channel;
};


}  // Namespace microscopy
}  // Namespace motion
}  // Namespace zaber
