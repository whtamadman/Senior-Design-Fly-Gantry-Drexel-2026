// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>
#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/ascii/pvt_io.h"
#include "zaber/motion/dto/ascii/measurement_sequence.h"
#include "zaber/motion/dto/ascii/pvt_axis_definition.h"
#include "zaber/motion/dto/ascii/pvt_csv_data.h"
#include "zaber/motion/dto/ascii/pvt_mode.h"
#include "zaber/motion/dto/ascii/pvt_partial_csv_data.h"
#include "zaber/motion/dto/ascii/pvt_partial_sequence_item.h"
#include "zaber/motion/dto/ascii/pvt_sequence_item.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace ascii {

/* Forward Declarations */
class PvtBuffer;


/**
 * A handle for a PVT sequence with this number on the device.
 * PVT sequences provide a way execute or store trajectory
 * consisting of points with defined position, velocity, and time.
 * PVT sequence methods append actions to a queue which executes
 * or stores actions in a first in, first out order.
 */
class PvtSequence {
public:
    struct WaitUntilIdleOptions {
        // Determines whether to throw error when fault is observed.
        bool throwErrorOnFault {true};
    };

    PvtSequence(Device device, int pvtId);

    PvtSequence();

    /**
     * Setup the PVT sequence to control the specified axes and to queue actions on the device.
     * Allows use of lockstep axes in a PVT sequence.
     * @param pvtAxes Definition of the PVT sequence axes.
     */
    void setupLiveComposite(const std::vector<PvtAxisDefinition>& pvtAxes);

    void setupLiveComposite(std::initializer_list<PvtAxisDefinition> pvtAxes);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void setupLiveComposite(TIterator begin, TIterator end) {
        return setupLiveComposite(std::vector<PvtAxisDefinition>(begin,end));
    }

    template<typename... T>
    void setupLiveComposite(T&&... pvtAxes) {
        return setupLiveComposite({std::forward<T>(pvtAxes)...});
    }
    /**
     * Setup the PVT sequence to control the specified axes and to queue actions on the device.
     * @param axes Numbers of physical axes to setup the PVT sequence on.
     */
    void setupLive(const std::vector<int>& axes);

    void setupLive(std::initializer_list<int> axes);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void setupLive(TIterator begin, TIterator end) {
        return setupLive(std::vector<int>(begin,end));
    }

    template<typename... T>
    void setupLive(T&&... axes) {
        return setupLive({std::forward<T>(axes)...});
    }
    /**
     * Setup the PVT sequence to use the specified axes and queue actions into a PVT buffer.
     * Allows use of lockstep axes in a PVT sequence.
     * @param pvtBuffer The PVT buffer to queue actions in.
     * @param pvtAxes Definition of the PVT sequence axes.
     */
    void setupStoreComposite(const PvtBuffer& pvtBuffer, const std::vector<PvtAxisDefinition>& pvtAxes);

    void setupStoreComposite(const PvtBuffer& pvtBuffer, std::initializer_list<PvtAxisDefinition> pvtAxes);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void setupStoreComposite(const PvtBuffer& pvtBuffer, TIterator begin, TIterator end) {
        return setupStoreComposite(pvtBuffer, std::vector<PvtAxisDefinition>(begin,end));
    }

    template<typename... T>
    void setupStoreComposite(const PvtBuffer& pvtBuffer, T&&... pvtAxes) {
        return setupStoreComposite(pvtBuffer, {std::forward<T>(pvtAxes)...});
    }
    /**
     * Setup the PVT sequence to use the specified axes and queue actions into a PVT buffer.
     * @param pvtBuffer The PVT buffer to queue actions in.
     * @param axes The axis numbers of the physical axes to setup the PVT sequence on.
     */
    void setupStore(const PvtBuffer& pvtBuffer, const std::vector<int>& axes);

    void setupStore(const PvtBuffer& pvtBuffer, std::initializer_list<int> axes);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void setupStore(const PvtBuffer& pvtBuffer, TIterator begin, TIterator end) {
        return setupStore(pvtBuffer, std::vector<int>(begin,end));
    }

    template<typename... T>
    void setupStore(const PvtBuffer& pvtBuffer, T&&... axes) {
        return setupStore(pvtBuffer, {std::forward<T>(axes)...});
    }
    /**
     * Append the actions in a PVT buffer to the sequence's queue.
     * @param pvtBuffer The PVT buffer to call.
     */
    void call(const PvtBuffer& pvtBuffer);
    /**
     * Queues a point with absolute coordinates in the PVT sequence.
     * If some or all velocities are not provided, the sequence calculates the velocities
     * from surrounding points using finite difference.
     * If time value is zero, the device must already be idle at the specified position
     * and the specified velocity must be zero.
     * The last point of the sequence must have defined velocity (likely zero).
     * @param positions Positions for the axes to move through, relative to their home positions.
     * @param velocities The axes velocities at the given point.
     * Specify an empty array or null for specific axes to make the sequence calculate the velocity.
     * @param time The duration between the previous point in the sequence and this one.
     */
    void point(const std::vector<Measurement>& positions, const std::vector<std::optional<Measurement>>& velocities, const Measurement& time);
    /**
     * Deprecated: This method is being replaced by the new SubmitSequenceData method.
     *
     * Queues points with absolute coordinates in the PVT sequence.
     * Each point must have its time value measured relative to the previous point
     * or unexpected behavior will result.
     *
     * Note that if the first time value is zero, the device must already be idle at
     * the position of the first point and the velocity of that point must be zero.
     * All other time values must be greater than zero.
     * @param positions Per-axis sequences of positions.
     * @param velocities Per-axis sequences of velocities.
     * For velocities [v0, v1, ...] and positions [p0, p1, ...], v1 is the target velocity at point p1.
     * @param times Segment times from one point to another.
     * For times [t0, t1, ...] and positions [p0, p1, ...], t1 is the time it takes to move from p0 to p1.
     */
    void points(const std::vector<MeasurementSequence>& positions, const std::vector<MeasurementSequence>& velocities, const MeasurementSequence& times);
    /**
     * Queues a point with coordinates relative to the previous point in the PVT sequence.
     * If some or all velocities are not provided, the sequence calculates the velocities
     * from surrounding points using finite difference.
     *
     * The time value must be greater than zero, and each point must have its time value
     * measured relative to the previous point or unexpected behavior will result.
     *
     * The last point of the sequence must have defined velocity (likely zero).
     * @param positions Positions for the axes to move through, relative to the previous point.
     * @param velocities The axes velocities at the given point.
     * Specify an empty array or null for specific axes to make the sequence calculate the velocity.
     * @param time The duration between the previous point in the sequence and this one.
     */
    void pointRelative(const std::vector<Measurement>& positions, const std::vector<std::optional<Measurement>>& velocities, const Measurement& time);
    /**
     * Deprecated: This method is being replaced by the new SubmitSequenceData method.
     *
     * Queues points with coordinates relative to the previous point in the PVT sequence.
     * All time values must be greater than zero and each point must have its time value
     * measured relative to the previous point or unexpected behavior will result.
     * @param positions Per-axis sequences of positions.
     * @param velocities Per-axis sequences of velocities.
     * For velocities [v0, v1, ...] and positions [p0, p1, ...], v1 is the target velocity at point p1.
     * @param times Segment times from one point to another.
     * For times [t0, t1, ...] and positions [p0, p1, ...], t1 is the time it takes to move from p0 to p1.
     */
    void pointsRelative(const std::vector<MeasurementSequence>& positions, const std::vector<MeasurementSequence>& velocities, const MeasurementSequence& times);
    /**
     * Generates velocities for a sequence of positions and times, and (optionally) a partially defined sequence
     * of velocities. Note that if some velocities are defined, the solver will NOT modify them in any way.
     * If all velocities are defined, the solver will simply return the same velocities.
     * This function calculates velocities by enforcing that acceleration be continuous at each segment transition.
     * The function does not modify the input positions or times.
     *
     * Also note that if the first position is relative, all following points must be relative.
     * If the start position is absolute, then the sequence can include a mix of relative and absolute positions.
     * Additionally, all times must be relative to the previous point.
     * Please see the ConvertTimeAbsoluteToRelativePartial function for conversions.
     *
     * Does not support native units.
     * @param sequenceItems Partial PVT points defining the positions, optional velocities, and times for the sequence.
     * Each point should have positions defined for each axis. Velocities are optional.
     * Times must be defined for each point.
     * @return Array of points and actions containing the generated PVT sequence. Note returned times are always relative.
     */
    static std::vector<PvtSequenceItem> generateVelocities(const std::vector<PvtPartialSequenceItem>& sequenceItems);
    /**
     * Generates positions for a sequence of velocities and times. This function calculates
     * positions by enforcing that acceleration be continuous at each segment transition.
     *
     * This function does not modify the input velocities or times, and outputs absolute
     * positions. If your initial point has a time of zero, it will be considered a starting
     * position when submitted to the device, and you must already have moved the device
     * to that position. Additionally, all times must be relative to the previous point.
     * Please see the ConvertTimeAbsoluteToRelativePartial function for conversions.
     *
     * Does not support native units.
     * @param sequenceItems Partial PVT points defining the velocities and times for the sequence.
     * Each point should have velocities defined for each axis.
     * Times must be defined for each point.
     * @return Array of points and actions containing the generated PVT sequence. Note returned times are always relative.
     */
    static std::vector<PvtSequenceItem> generatePositions(const std::vector<PvtPartialSequenceItem>& sequenceItems);
    /**
     * Generates sequences of velocities and times for a sequence of positions.
     * This function fits a geometric spline (not-a-knot cubic for sequences of >3 points,
     * natural cubic for 3, and a straight line for 2) over the position sequence
     * and then calculates the velocity and time information by traversing it using a
     * trapezoidal motion profile.
     *
     * This generation scheme attempts to keep speed and acceleration less than the
     * specified target values, but does not guarantee it. Generally speaking, a higher
     * resample number will bring the generated trajectory closer to respecting these
     * limits.
     *
     * Note that consecutive duplicate points will be automatically removed as they
     * have no geometric significance without additional time information. Also note that
     * for multi-dimensional paths this function expects axes to be linear and orthogonal,
     * however for paths of a single dimension rotary units are accepted.
     * Additionally, if the first positions of the input sequence is relative,
     * all following positions must also be relative. If the first position is absolute,
     * the sequence may contain a mix of relative and absolute positions.
     * Resampling a sequence which contains relative positions is not allowed.
     *
     * This function outputs points with absolute positions and relative times, with the
     * first time equal to zero, meaning it will be treated as a start position when
     * executing on a device. You must move the device to that position before submitting
     * the sequence, or change the first point's time to a value greater than zero.
     *
     * Does not support native units.
     * @param sequenceItems Partial PVT points defining the positions for the sequence.
     * Each point should have positions defined for each axis.
     * @param targetSpeed The target speed used to generate positions and times.
     * @param targetAcceleration The target acceleration used to generate positions and times.
     * @param resampleNumber The number of points to resample the sequence by.
     * Leave undefined to use the specified points.
     * @return Array of points and actions containing the generated PVT sequence. Note returned times are always relative.
     */
    static std::vector<PvtSequenceItem> generateVelocitiesAndTimes(const std::vector<PvtPartialSequenceItem>& sequenceItems, const Measurement& targetSpeed, const Measurement& targetAcceleration, const std::optional<int>& resampleNumber = {});
    /**
     * Waits until the live PVT sequence executes all queued actions.
     * @param throwErrorOnFault Determines whether to throw error when fault is observed.
     */
    void waitUntilIdle(bool throwErrorOnFault = true);

    /**
     * Waits until the live PVT sequence executes all queued actions.
     * @param options A struct of type WaitUntilIdleOptions. It has the following members:
     * * `throwErrorOnFault`: Determines whether to throw error when fault is observed.
     */
    void waitUntilIdle(const PvtSequence::WaitUntilIdleOptions& options);
    /**
     * Cork the front of the PVT sequences's action queue, blocking execution.
     * Execution resumes upon uncorking the queue, or when the number of queued actions reaches its limit.
     * Corking eliminates discontinuities in motion due to subsequent PVT commands reaching the device late.
     * You can only cork an idle live PVT sequence.
     */
    void cork();
    /**
     * Uncork the front of the queue, unblocking command execution.
     * You can only uncork an idle live PVT sequence that is corked.
     */
    void uncork();
    /**
     * Returns a boolean value indicating whether the live PVT sequence is executing a queued action.
     * @return True if the PVT sequence is executing a queued action.
     */
    bool isBusy();
    /**
     * Returns a string which represents the PVT sequence.
     * @return String which represents the PVT sequence.
     */
    std::string toString() const;
    /**
     * Disables the PVT sequence.
     * If the PVT sequence is not setup, this command does nothing.
     * Once disabled, the PVT sequence will no longer accept PVT commands.
     * The PVT sequence will process the rest of the commands in the queue until it is empty.
     */
    void disable();
    /**
     * Sends a generic ASCII command to the PVT sequence.
     * Keeps resending the command while the device rejects with AGAIN reason.
     * @param command Command and its parameters.
     */
    void genericCommand(const std::string& command);
    /**
     * Sends a batch of generic ASCII commands to the PVT sequence.
     * Keeps resending command while the device rejects with AGAIN reason.
     * The batch is atomic in terms of thread safety.
     * @param batch Array of commands.
     */
    void genericCommandBatch(const std::vector<std::string>& batch);
    /**
     * Queries the PVT sequence status from the device
     * and returns boolean indicating whether the PVT sequence is disabled.
     * Useful to determine if execution was interrupted by other movements.
     * @return True if the PVT sequence is disabled.
     */
    bool checkDisabled();
    /**
     * Makes the PVT sequence throw PvtDiscontinuityException when it encounters discontinuities (ND warning flag).
     */
    void treatDiscontinuitiesAsError();
    /**
     * Prevents PvtDiscontinuityException as a result of expected discontinuity when resuming the sequence.
     */
    void ignoreCurrentDiscontinuity();
    /**
     * Saves PvtSequenceItem array as a csv file.
     * Save format is compatible with Zaber Launcher PVT Editor App.
     *
     * Normally a sequence in memory should have relative time values on the points.
     * If you want to store absolute times instead, you can use the
     * ConvertTimeRelativeToAbsolute function to convert before saving.
     *
     * Throws InvalidArgumentException if fields are undefined or inconsistent.
     * For example, position and velocity arrays must have the same dimensions.
     * Sequence lengths must be consistent for positions, velocities and times.
     * @param sequenceData The PVT sequence data to save.
     * @param path The path to save the file to.
     * @param dimensionNames Optional csv column names for each series.
     * If not provided, the default names will be used: Series 1, Series 2, etc..
     * Length of this array must be equal to number of dimensions in sequence data.
     */
    static void saveSequenceData(const std::vector<PvtSequenceItem>& sequenceData, const std::string& path, const std::vector<std::string>& dimensionNames = {});
    /**
     * Load PVT Sequence data from CSV file.
     * This function expects complete data in the CSV files (a time column and
     * both position and velocity columns for each series).
     * If your CSV file has partial data, use LoadPartialSequenceData instead.
     *
     * The CSV data can include a header (recommended).
     * There are two possible header formats:
     *
     * 1. A time column with named position and velocity columns.
     * For example, "Time (ms),X Position (cm),X Velocity (cm/s),...".
     * In this case, position, velocity and time columns are all optional.
     * Also, order does not matter, but position and velocity names must be consistent.
     * This is our recommended CSV format.
     *
     * 2. A time column with alternating position and velocity columns.
     * For example, "Time (ms),Position (cm),Velocity (cm/s),...".
     * In this case, only the time column is optional and order does matter.
     *
     * Units must be wrapped in parens or square braces: ie. (µm/s), [µm/s].
     * Additionally, native units are the default if no units are specified.
     * Time values default to milliseconds if no units are provided.
     * If no header is included, then column order is assumed to be "T,P1,V1,P2,V2,...".
     * In this case the number of columns must be odd.
     *
     * Users can add a column named "Relative" with true/false values to
     * indicate whether each point's position is relative or absolute.
     * If this column is not included, all points will be assumed to be absolute.
     *
     * If the first point has time = zero, it is considered the start position
     * and treated specially. It must have an absolute position, and the device
     * must already be idle at that position when the sequence is submitted.
     * The velocity of the start position is ignored, and should normally be zero.
     * Sequences with nonzero time for the first point do not have these constraints.
     *
     * Buffer calls and I/O actions can be added into the CSV file by
     * adding a column titled "Actions", containing the ASCII protocol command(s)
     * shortened by everything up to the PVT stream number, for example
     * "call 2" or "io set do 1 1". If you want to insert multiple actions
     * after a point, put them in the same cell separated by a semicolon.
     * See the ASCII Protocol Manual
     * [PVT command reference](https://www.zaber.com/protocol-manual?protocol=ASCII#topic_command_pvt)
     * section for the list of available commands. Unit symbols are not supported;
     * analog output voltages are always in volts and schedule delay times are
     * always in milliseconds.
     *
     * Note that the Relative and Actions columns are not automatically
     * detected, so if you include them you must include a header row.
     *
     * Time values should always be relative when sent to a device or to the
     * various Generate... functions on this class. If you want to store
     * absolute times in a CSV file, you can use the ConvertTimeRelativeToAbsolute
     * function to convert after loading the file.
     * @param path The path to the csv file to load.
     * @return The PVT csv data loaded from the file.
     */
    static PvtCsvData loadSequenceData(const std::string& path);
    /**
     * Load PVT Sequence data from CSV file, allowing for some combinations of incomplete data.
     * Output from this function cannot be enqueued on a device until the missing data has
     * been filled in using the GenerateVelocities, GeneratePositions or
     * GenerateVelocitiesAndTimes functions.
     *
     * The CSV data can include a header (recommended).
     * There are two possible header formats:
     *
     * 1. A time column with named position and velocity columns.
     * For example, "Time (ms),X Position (cm),X Velocity (cm/s),...".
     * In this case, position, velocity and time columns are all optional.
     * Also, order does not matter, but position and velocity names must be consistent.
     * This is our recommended CSV format.
     *
     * 2. A time column with alternating position and velocity columns.
     * For example, "Time (ms),Position (cm),Velocity (cm/s),...".
     * In this case, only the time column is optional and order does matter.
     *
     * Units must be wrapped in parens or square braces: ie. (µm/s), [µm/s].
     * Additionally, native units are the default if no units are specified.
     * Time values default to milliseconds if no units are provided.
     * If no header is included, then column order is assumed to be "T,P1,V1,P2,V2,...".
     * In this case the number of columns must be odd.
     *
     * Users can add a column named "Relative" with true/false values to
     * indicate whether each point's position is relative or absolute.
     * If this column is not included, all points will be assumed to be absolute.
     *
     * If the first point has time = zero, it is considered the start position
     * and treated specially. It must have an absolute position, and the device
     * must already be idle at that position when the sequence is submitted.
     * The velocity of the start position is ignored, and should normally be zero.
     * Sequences with nonzero time for the first point do not have these constraints.
     *
     * Buffer calls and I/O actions can be added into the CSV file by
     * adding a column titled "Actions", containing the ASCII protocol command(s)
     * shortened by everything up to the PVT stream number, for example
     * "call 2" or "io set do 1 1". If you want to insert multiple actions
     * after a point, put them in the same cell separated by a semicolon.
     * See the ASCII Protocol Manual
     * [PVT command reference](https://www.zaber.com/protocol-manual?protocol=ASCII#topic_command_pvt)
     * section for the list of available commands. Unit symbols are not supported;
     * analog output voltages are always in volts and schedule delay times are
     * always in milliseconds.
     *
     * Note that the Relative and Actions columns are not automatically
     * detected, so if you include them you must include a header row.
     *
     * Time values should always be relative when sent to a device or to the
     * various Generate... functions on this class. If you want to store
     * absolute times in a CSV file, you can use the ConvertTimeRelativeToAbsolute
     * function to convert after loading the file.
     * @param path The path to the csv file to load.
     * @return The PVT csv data loaded from the file.
     */
    static PvtPartialCsvData loadPartialSequenceData(const std::string& path);
    /**
     * Writes the contents of a PvtSequenceItem array to the sequence.
     * Each point must have its time value measured relative to the previous point
     * or unexpected behavior will result. If your point times are absolute (measured
     * from the start of the sequence), use the ConvertTimeAbsoluteToRelative
     * function to convert them before submitting.
     *
     * If the first point in the sequence has a time value of zero, it is
     * considered the starting position. It must have an absolute position,
     * zero velocity, and the device must already be idle at the specified position.
     * @param sequenceData The PVT sequence data to submit.
     */
    void submitSequenceData(const std::vector<PvtSequenceItem>& sequenceData);
    /**
     * Converts the time values in a PvtSequenceItem array from absolute to relative.
     * Points passed to the Generate functions or sent to devices must have relative time values.
     * @param sequenceData The sequence data for which to convert times from absolute to relative.
     * Point times must all be in the same units.
     * @return The sequence data with times converted from absolute to relative.
     */
    static std::vector<PvtSequenceItem> convertTimeAbsoluteToRelative(const std::vector<PvtSequenceItem>& sequenceData);
    /**
     * Converts the time values in a PvtSequenceItem array from relative to absolute.
     * @param sequenceData The sequence data for which to convert times from relative to absolute.
     * Point times must all be in the same units.
     * @return The sequence data with times converted from relative to absolute.
     */
    static std::vector<PvtSequenceItem> convertTimeRelativeToAbsolute(const std::vector<PvtSequenceItem>& sequenceData);
    /**
     * Converts the time values in a PvtPartialSequenceItem array from absolute to relative.
     * Points passed to the Generate functions or sent to devices must have relative time values.
     * @param sequenceData The sequence data for which to convert times from absolute to relative.
     * Point times must all be in the same units.
     * @return The sequence data with times converted from absolute to relative.
     */
    static std::vector<PvtPartialSequenceItem> convertTimeAbsoluteToRelativePartial(const std::vector<PvtPartialSequenceItem>& sequenceData);
    /**
     * Converts the time values in a PvtPartialSequenceItem array from relative to absolute.
     * @param sequenceData The sequence data for which to convert times from relative to absolute.
     * Point times must all be in the same units.
     * @return The sequence data with times converted from relative to absolute.
     */
    static std::vector<PvtPartialSequenceItem> convertTimeRelativeToAbsolutePartial(const std::vector<PvtPartialSequenceItem>& sequenceData);
    /**
     * Device that controls this PVT sequence.
     */
    Device getDevice() const;
    /**
     * The number that identifies the PVT sequence on the device.
     */
    int getPvtId() const;
    /**
     * Current mode of the PVT sequence.
     */
    PvtMode getMode() const;
    /**
     * An array of axes definitions the PVT sequence is set up to control.
     */
    std::vector<PvtAxisDefinition> getAxes() const;
    /**
     * Gets an object that provides access to I/O for this sequence.
     */
    PvtIo getIo() const;
protected:
    /**
     * Gets the axes of the PVT sequence.
     * @return An array of axis numbers of the axes the PVT sequence is set up to control.
     */
    std::vector<PvtAxisDefinition> retrieveAxes() const;
    /**
     * Get the mode of the PVT sequence.
     * @return Mode of the PVT sequence.
     */
    PvtMode retrieveMode() const;
    Device _device;
    int _pvtId;
    PvtIo _io;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
