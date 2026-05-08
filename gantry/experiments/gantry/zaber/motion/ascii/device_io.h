// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/dto/ascii/device_io_info.h"
#include "zaber/motion/dto/ascii/digital_output_action.h"
#include "zaber/motion/dto/ascii/io_port_label.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {


/**
 * Class providing access to the I/O channels of the device.
 */
class DeviceIO {
public:
    DeviceIO(Device device);

    /**
     * Returns the number of I/O channels the device has.
     * @return An object containing the number of I/O channels the device has.
     */
    DeviceIOInfo getChannelsInfo();
    /**
     * Sets the label of the specified channel.
     * @param portType The type of channel to set the label of.
     * @param channelNumber Channel number starting at 1.
     * @param label The label to set for the specified channel.
     * If no value or an empty string is provided, this label is deleted.
     */
    void setLabel(IoPortType portType, int channelNumber, const std::optional<std::string>& label);
    /**
     * Returns the label of the specified channel.
     * @param portType The type of channel to get the label of.
     * @param channelNumber Channel number starting at 1.
     * @return The label of the specified channel.
     */
    std::string getLabel(IoPortType portType, int channelNumber);
    /**
     * Returns every label assigned to an IO port on this device.
     * @return The labels set for this device's IO.
     */
    std::vector<IoPortLabel> getAllLabels();
    /**
     * Returns the current value of the specified digital input channel.
     * @param channelNumber Channel number starting at 1.
     * @return True if voltage is present on the input channel and false otherwise.
     */
    bool getDigitalInput(int channelNumber);
    /**
     * Returns the current value of the specified digital output channel.
     * @param channelNumber Channel number starting at 1.
     * @return True if the output channel is conducting and false otherwise.
     */
    bool getDigitalOutput(int channelNumber);
    /**
     * Returns the current value of the specified analog input channel.
     * @param channelNumber Channel number starting at 1.
     * @return  A measurement of the voltage present on the input channel.
     */
    double getAnalogInput(int channelNumber);
    /**
     * Returns the current values of the specified analog output channel.
     * @param channelNumber Channel number starting at 1.
     * @return A measurement of voltage that the output channel is conducting.
     */
    double getAnalogOutput(int channelNumber);
    /**
     * Returns the current values of all digital input channels.
     * @return True if voltage is present on the input channel and false otherwise.
     */
    std::vector<bool> getAllDigitalInputs();
    /**
     * Returns the current values of all digital output channels.
     * @return True if the output channel is conducting and false otherwise.
     */
    std::vector<bool> getAllDigitalOutputs();
    /**
     * Returns the current values of all analog input channels.
     * @return Measurements of the voltages present on the input channels.
     */
    std::vector<double> getAllAnalogInputs();
    /**
     * Returns the current values of all analog output channels.
     * @return Measurements of voltage that the output channels are conducting.
     */
    std::vector<double> getAllAnalogOutputs();
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
     * Sets the cutoff frequency of the low-pass filter for the specified analog input channel.
     * Set the frequency to 0 to disable the filter.
     * @param channelNumber Channel number starting at 1.
     * @param cutoffFrequency Cutoff frequency of the low-pass filter.
     * @param unit Units of frequency.
     */
    void setAnalogInputLowpassFilter(int channelNumber, double cutoffFrequency, Units unit = Units::NATIVE);
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
protected:
    Device getDevice() const;
    Device _device;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
