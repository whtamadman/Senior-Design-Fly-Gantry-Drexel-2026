// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/dto/ascii/io_port_type.h"
#include "zaber/motion/dto/ascii/oscilloscope_capture_properties.h"
#include "zaber/motion/dto/ascii/oscilloscope_data_source.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {


/**
 * Contains a block of contiguous recorded data for one channel of the device's oscilloscope.
 */
class OscilloscopeData {
public:
    OscilloscopeData(int dataId);

    OscilloscopeData(const OscilloscopeData& other) = delete;
    OscilloscopeData& operator=(const OscilloscopeData& other) = delete;

    /**
     * Get the sample interval that this data was recorded with.
     * @param unit Unit of measure to represent the timebase in.
     * @return The timebase setting at the time the data was recorded.
     */
    double getTimebase(Units unit = Units::NATIVE);
    /**
     * Get the sampling frequency that this data was recorded with.
     * @param unit Unit of measure to represent the frequency in.
     * @return The frequency (inverse of the timebase setting) at the time the data was recorded.
     */
    double getFrequency(Units unit = Units::NATIVE);
    /**
     * Get the user-specified time period between receipt of the start command and the first data point.
     * Under some circumstances, the actual delay may be different - call GetSampleTime(0) to get the effective delay.
     * @param unit Unit of measure to represent the delay in.
     * @return The delay setting at the time the data was recorded.
     */
    double getDelay(Units unit = Units::NATIVE);
    /**
     * Calculate the time a sample was recorded, relative to when the recording was triggered.
     * @param index 0-based index of the sample to calculate the time of.
     * @param unit Unit of measure to represent the calculated time in.
     * @return The calculated time offset of the data sample at the given index.
     */
    double getSampleTime(int index, Units unit = Units::NATIVE);
    /**
     * Calculate the time for all samples, relative to when the recording was triggered.
     * @param unit Unit of measure to represent the calculated time in.
     * @return The calculated time offsets of all data samples.
     */
    std::vector<double> getSampleTimes(Units unit = Units::NATIVE);
    /**
     * Get the recorded data as an array of doubles, with optional unit conversion.
     * Note that not all quantities can be unit converted.
     * For example, digital I/O channels and pure numbers such as device mode settings have no units.
     * @param unit Unit of measure to convert the data to.
     * @return The recorded data for one oscilloscope channel, converted to the units specified.
     */
    std::vector<double> getData(Units unit = Units::NATIVE);
    /**
     * Unique ID for this block of recorded data.
     */
    int getDataId() const;
    /**
     * Indicates whether the data came from a setting or an I/O pin.
     */
    OscilloscopeDataSource getDataSource() const;
    /**
     * The name of the recorded setting.
     */
    std::string getSetting() const;
    /**
     * The number of the axis the data was recorded from, or 0 for the controller.
     */
    int getAxisNumber() const;
    /**
     * Which kind of I/O port data was recorded from.
     */
    IoPortType getIoType() const;
    /**
     * Which I/O pin within the port was recorded.
     */
    int getIoChannel() const;
protected:
    /**
     * Releases native resources of an oscilloscope data buffer.
     * @param dataId The ID of the data buffer to delete.
     */
    static void free(int dataId);
    /**
     * Returns recording properties.
     * @return Capture properties.
     */
    OscilloscopeCaptureProperties retrieveProperties() const;
    int _dataId;
public:
    OscilloscopeData(): _dataId(-1) {}
    ~OscilloscopeData();
    OscilloscopeData(OscilloscopeData&& other) noexcept;
    OscilloscopeData& operator=(OscilloscopeData&& other) noexcept;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
