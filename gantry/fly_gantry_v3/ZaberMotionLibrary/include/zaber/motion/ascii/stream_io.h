// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/dto/ascii/digital_output_action.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {


/**
 * Class providing access to I/O for a stream.
 */
class StreamIo {
public:
    StreamIo(Device device, int streamId);

    /**
     * Sets value for the specified digital output channel.
     * @param channelNumber Channel number starting at 1.
     * @param value The type of action to perform on the channel.
     */
    void setDigitalOutput(int channelNumber, DigitalOutputAction value);
    /**
     * Sets values for all digital output channels.
     * @param values The type of action to perform on the channel.
     */
    void setAllDigitalOutputs(const std::vector<DigitalOutputAction>& values);
    /**
     * Sets current and future value for the specified digital output channel.
     * Requires at least Firmware 7.37.
     * @param channelNumber Channel number starting at 1.
     * @param value The type of action to perform immediately on the channel.
     * @param futureValue The type of action to perform in the future on the channel.
     * @param delay Delay between setting current value and setting future value.
     * @param unit Units of time.
     */
    void setDigitalOutputSchedule(int channelNumber, DigitalOutputAction value, DigitalOutputAction futureValue, double delay, Units unit = Units::NATIVE);
    /**
     * Sets current and future values for all digital output channels.
     * Requires at least Firmware 7.37.
     * @param values The type of actions to perform immediately on output channels.
     * @param futureValues The type of actions to perform in the future on output channels.
     * @param delay Delay between setting current values and setting future values.
     * @param unit Units of time.
     */
    void setAllDigitalOutputsSchedule(const std::vector<DigitalOutputAction>& values, const std::vector<DigitalOutputAction>& futureValues, double delay, Units unit = Units::NATIVE);
    /**
     * Sets value for the specified analog output channel.
     * @param channelNumber Channel number starting at 1.
     * @param value Value to set the output channel voltage to.
     */
    void setAnalogOutput(int channelNumber, double value);
    /**
     * Sets values for all analog output channels.
     * @param values Voltage values to set the output channels to.
     */
    void setAllAnalogOutputs(const std::vector<double>& values);
    /**
     * Sets current and future value for the specified analog output channel.
     * Requires at least Firmware 7.38.
     * @param channelNumber Channel number starting at 1.
     * @param value Value to set the output channel voltage to immediately.
     * @param futureValue Value to set the output channel voltage to in the future.
     * @param delay Delay between setting current value and setting future value.
     * @param unit Units of time.
     */
    void setAnalogOutputSchedule(int channelNumber, double value, double futureValue, double delay, Units unit = Units::NATIVE);
    /**
     * Sets current and future values for all analog output channels.
     * Requires at least Firmware 7.38.
     * @param values Voltage values to set the output channels to immediately.
     * @param futureValues Voltage values to set the output channels to in the future.
     * @param delay Delay between setting current values and setting future values.
     * @param unit Units of time.
     */
    void setAllAnalogOutputsSchedule(const std::vector<double>& values, const std::vector<double>& futureValues, double delay, Units unit = Units::NATIVE);
    /**
     * Cancels a scheduled digital output action.
     * Requires at least Firmware 7.37.
     * @param channelNumber Channel number starting at 1.
     */
    void cancelDigitalOutputSchedule(int channelNumber);
    /**
     * Cancel all scheduled digital output actions.
     * Requires at least Firmware 7.37.
     * @param channels Optionally specify which channels to cancel.
     * Array length must be empty or equal to the number of channels on device.
     * Specifying "True" for a channel will cancel the scheduled digital output action for that channel.
     */
    void cancelAllDigitalOutputsSchedule(const std::vector<bool>& channels = {});
    /**
     * Cancels a scheduled analog output value.
     * Requires at least Firmware 7.38.
     * @param channelNumber Channel number starting at 1.
     */
    void cancelAnalogOutputSchedule(int channelNumber);
    /**
     * Cancel all scheduled analog output actions.
     * Requires at least Firmware 7.38.
     * @param channels Optionally specify which channels to cancel.
     * Array length must be empty or equal to the number of channels on device.
     * Specifying "True" for a channel will cancel the scheduled analog output value for that channel.
     */
    void cancelAllAnalogOutputsSchedule(const std::vector<bool>& channels = {});
    /**
     * Wait for a digital input channel to reach a given value.
     * @param channelNumber The number of the digital input channel.
     * Channel numbers are numbered from one.
     * @param value The value that the stream should wait for.
     */
    void waitDigitalInput(int channelNumber, bool value);
    /**
     * Wait for the value of a analog input channel to reach a condition concerning a given value.
     * @param channelNumber The number of the analog input channel.
     * Channel numbers are numbered from one.
     * @param condition A condition (e.g. <, <=, ==, !=).
     * @param value The value that the condition concerns, in Volts.
     */
    void waitAnalogInput(int channelNumber, const std::string& condition, double value);
protected:
    Device getDevice() const;
    int getStreamId() const;
    Device _device;
    int _streamId;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
