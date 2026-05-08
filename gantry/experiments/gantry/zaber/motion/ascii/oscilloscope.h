// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/dto/ascii/io_port_type.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {

/* Forward Declarations */
class OscilloscopeData;


/**
 * Provides a convenient way to control the oscilloscope data recording feature of some devices.
 * The oscilloscope can record the values of some settings over time at high resolution.
 * Requires at least Firmware 7.00.
 */
class Oscilloscope {
public:
    Oscilloscope(Device device);

    /**
     * Select a setting to be recorded.
     * @param axis The 1-based index of the axis to record the value from.
     * @param setting The name of a setting to record.
     */
    void addChannel(int axis, const std::string& setting);
    /**
     * Select an I/O pin to be recorded.
     * Requires at least Firmware 7.33.
     * @param ioType The I/O port type to read data from.
     * @param ioChannel The 1-based index of the I/O pin to read from.
     */
    void addIoChannel(IoPortType ioType, int ioChannel);
    /**
     * Clear the list of channels to record.
     */
    void clear();
    /**
     * Get the current sampling interval.
     * @param unit Unit of measure to represent the timebase in.
     * @return The current sampling interval in the selected time units.
     */
    double getTimebase(Units unit = Units::NATIVE);
    /**
     * Set the sampling interval.
     * @param interval Sample interval for the next oscilloscope recording. Minimum value is 100µs.
     * @param unit Unit of measure the timebase is represented in.
     */
    void setTimebase(double interval, Units unit = Units::NATIVE);
    /**
     * Get the current sampling frequency.
     * The values is calculated as the inverse of the current sampling interval.
     * @param unit Unit of measure to represent the frequency in.
     * @return The inverse of current sampling interval in the selected units.
     */
    double getFrequency(Units unit = Units::NATIVE);
    /**
     * Set the sampling frequency (inverse of the sampling interval).
     * The value is quantized to the next closest value supported by the firmware.
     * @param frequency Sample frequency for the next oscilloscope recording.
     * @param unit Unit of measure the frequency is represented in.
     */
    void setFrequency(double frequency, Units unit = Units::NATIVE);
    /**
     * Get the delay before oscilloscope recording starts.
     * @param unit Unit of measure to represent the delay in.
     * @return The current start delay in the selected time units.
     */
    double getDelay(Units unit = Units::NATIVE);
    /**
     * Set the sampling start delay.
     * @param interval Delay time between triggering a recording and the first data point being recorded.
     * @param unit Unit of measure the delay is represented in.
     */
    void setDelay(double interval, Units unit = Units::NATIVE);
    /**
     * Get the maximum number of channels that can be recorded.
     * @return The maximum number of channels that can be added to an Oscilloscope recording.
     */
    int getMaxChannels();
    /**
     * Get the maximum number of samples that can be recorded per Oscilloscope channel.
     * @return The maximum number of samples that can be recorded per Oscilloscope channel.
     */
    int getMaxBufferSize();
    /**
     * Get the number of samples that can be recorded per channel given the current number of channels added.
     * @return Number of samples that will be recorded per channel with the current channels. Zero if none have been added.
     */
    int getBufferSize();
    /**
     * Trigger data recording.
     * @param captureLength Optional number of samples to record per channel.
     * If left empty, the device records samples until the buffer fills.
     * Requires at least Firmware 7.29.
     */
    void start(int captureLength = 0);
    /**
     * End data recording if currently in progress.
     */
    void stop();
    /**
     * Reads the last-recorded data from the oscilloscope. Will block until any in-progress recording completes.
     * @return Array of recorded channel data arrays, in the order added.
     */
    std::vector<OscilloscopeData> read();
    /**
     * Device that this Oscilloscope measures.
     */
    Device getDevice() const;
protected:
    Device _device;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
