// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/ascii/stream_io.h"
#include "zaber/motion/dto/ascii/stream_axis_definition.h"
#include "zaber/motion/dto/ascii/stream_mode.h"
#include "zaber/motion/dto/measurement.h"
#include "zaber/motion/dto/rotation_direction.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {

/* Forward Declarations */
class StreamBuffer;


/**
 * A handle for a stream with this number on the device.
 * Streams provide a way to execute or store a sequence of actions.
 * Stream methods append actions to a queue which executes or stores actions in a first in, first out order.
 */
class Stream {
public:
    struct WaitUntilIdleOptions {
        // Determines whether to throw error when fault is observed.
        bool throwErrorOnFault {true};
    };

    Stream(Device device, int streamId);

    Stream();

    /**
     * Setup the stream to control the specified axes and to queue actions on the device.
     * Allows use of lockstep axes in a stream.
     * @param axes Definition of the stream axes.
     */
    void setupLiveComposite(const std::vector<StreamAxisDefinition>& axes);

    void setupLiveComposite(std::initializer_list<StreamAxisDefinition> axes);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void setupLiveComposite(TIterator begin, TIterator end) {
        return setupLiveComposite(std::vector<StreamAxisDefinition>(begin,end));
    }

    template<typename... T>
    void setupLiveComposite(T&&... axes) {
        return setupLiveComposite({std::forward<T>(axes)...});
    }
    /**
     * Setup the stream to control the specified axes and to queue actions on the device.
     * @param axes Numbers of physical axes to setup the stream on.
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
     * Setup the stream to control the specified axes and queue actions into a stream buffer.
     * Allows use of lockstep axes in a stream.
     * @param streamBuffer The stream buffer to queue actions in.
     * @param axes Definition of the stream axes.
     */
    void setupStoreComposite(const StreamBuffer& streamBuffer, const std::vector<StreamAxisDefinition>& axes);

    void setupStoreComposite(const StreamBuffer& streamBuffer, std::initializer_list<StreamAxisDefinition> axes);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void setupStoreComposite(const StreamBuffer& streamBuffer, TIterator begin, TIterator end) {
        return setupStoreComposite(streamBuffer, std::vector<StreamAxisDefinition>(begin,end));
    }

    template<typename... T>
    void setupStoreComposite(const StreamBuffer& streamBuffer, T&&... axes) {
        return setupStoreComposite(streamBuffer, {std::forward<T>(axes)...});
    }
    /**
     * Setup the stream to control the specified axes and queue actions into a stream buffer.
     * @param streamBuffer The stream buffer to queue actions in.
     * @param axes The axis numbers of the physical axes to setup the stream on.
     */
    void setupStore(const StreamBuffer& streamBuffer, const std::vector<int>& axes);

    void setupStore(const StreamBuffer& streamBuffer, std::initializer_list<int> axes);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void setupStore(const StreamBuffer& streamBuffer, TIterator begin, TIterator end) {
        return setupStore(streamBuffer, std::vector<int>(begin,end));
    }

    template<typename... T>
    void setupStore(const StreamBuffer& streamBuffer, T&&... axes) {
        return setupStore(streamBuffer, {std::forward<T>(axes)...});
    }
    /**
     * Setup the stream to use a specified number of axes, and to queue actions in a stream buffer.
     * Afterwards, you may call the resulting stream buffer on arbitrary axes.
     * This mode does not allow for unit conversions.
     * @param streamBuffer The stream buffer to queue actions in.
     * @param axesCount The number of axes in the stream.
     */
    void setupStoreArbitraryAxes(const StreamBuffer& streamBuffer, int axesCount);
    /**
     * Append the actions in a stream buffer to the queue.
     * @param streamBuffer The stream buffer to call.
     */
    void call(const StreamBuffer& streamBuffer);
    /**
     * Queue an absolute line movement in the stream.
     * @param endpoint Positions for the axes to move to, relative to their home positions.
     */
    void lineAbsolute(const std::vector<Measurement>& endpoint);

    void lineAbsolute(std::initializer_list<Measurement> endpoint);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void lineAbsolute(TIterator begin, TIterator end) {
        return lineAbsolute(std::vector<Measurement>(begin,end));
    }

    template<typename... T>
    void lineAbsolute(T&&... endpoint) {
        return lineAbsolute({std::forward<T>(endpoint)...});
    }
    /**
     * Queue a relative line movement in the stream.
     * @param endpoint Positions for the axes to move to, relative to their positions before movement.
     */
    void lineRelative(const std::vector<Measurement>& endpoint);

    void lineRelative(std::initializer_list<Measurement> endpoint);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void lineRelative(TIterator begin, TIterator end) {
        return lineRelative(std::vector<Measurement>(begin,end));
    }

    template<typename... T>
    void lineRelative(T&&... endpoint) {
        return lineRelative({std::forward<T>(endpoint)...});
    }
    /**
     * Queue an absolute line movement in the stream, targeting a subset of the stream axes.
     * Requires at least Firmware 7.11.
     * @param targetAxesIndices Indices of the axes in the stream the movement targets.
     * Refers to the axes provided during the stream setup or further execution.
     * Indices are zero-based.
     * @param endpoint Positions for the axes to move to, relative to their home positions.
     */
    void lineAbsoluteOn(const std::vector<int>& targetAxesIndices, const std::vector<Measurement>& endpoint);
    /**
     * Queue a relative line movement in the stream, targeting a subset of the stream axes.
     * Requires at least Firmware 7.11.
     * @param targetAxesIndices Indices of the axes in the stream the movement targets.
     * Refers to the axes provided during the stream setup or further execution.
     * Indices are zero-based.
     * @param endpoint Positions for the axes to move to, relative to their positions before movement.
     */
    void lineRelativeOn(const std::vector<int>& targetAxesIndices, const std::vector<Measurement>& endpoint);
    /**
     * Queue an absolute arc movement on the first two axes of the stream.
     * Absolute meaning that the home positions of the axes is treated as the origin.
     * @param rotationDirection The direction of the rotation.
     * @param centerX The first dimension of the position of the center of the circle on which the arc exists.
     * @param centerY The second dimension of the position of the center of the circle on which the arc exists.
     * @param endX The first dimension of the end position of the arc.
     * @param endY The second dimension of the end position of the arc.
     */
    void arcAbsolute(RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY);
    /**
     * Queue a relative arc movement on the first two axes of the stream.
     * Relative meaning that the current position of the axes is treated as the origin.
     * @param rotationDirection The direction of the rotation.
     * @param centerX The first dimension of the position of the center of the circle on which the arc exists.
     * @param centerY The second dimension of the position of the center of the circle on which the arc exists.
     * @param endX The first dimension of the end position of the arc.
     * @param endY The second dimension of the end position of the arc.
     */
    void arcRelative(RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY);
    /**
     * Queue an absolute arc movement in the stream.
     * The movement will only target the specified subset of axes in the stream.
     * Requires at least Firmware 7.11.
     * @param targetAxesIndices Indices of the axes in the stream the movement targets.
     * Refers to the axes provided during the stream setup or further execution.
     * Indices are zero-based.
     * @param rotationDirection The direction of the rotation.
     * @param centerX The first dimension of the position of the center of the circle on which the arc exists.
     * @param centerY The second dimension of the position of the center of the circle on which the arc exists.
     * @param endX The first dimension of the end position of the arc.
     * @param endY The second dimension of the end position of the arc.
     */
    void arcAbsoluteOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY);
    /**
     * Queue a relative arc movement in the stream.
     * The movement will only target the specified subset of axes in the stream.
     * Requires at least Firmware 7.11.
     * @param targetAxesIndices Indices of the axes in the stream the movement targets.
     * Refers to the axes provided during the stream setup or further execution.
     * Indices are zero-based.
     * @param rotationDirection The direction of the rotation.
     * @param centerX The first dimension of the position of the center of the circle on which the arc exists.
     * @param centerY The second dimension of the position of the center of the circle on which the arc exists.
     * @param endX The first dimension of the end position of the arc.
     * @param endY The second dimension of the end position of the arc.
     */
    void arcRelativeOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY);
    /**
     * Queue an absolute helix movement in the stream.
     * Requires at least Firmware 7.28.
     * @param targetAxesIndices Indices of the axes in the stream the movement targets.
     * Refers to the axes provided during the stream setup or further execution.
     * Indices are zero-based.
     * The first two axes refer to the helix's arc component,
     * while the rest refers to the helix's line component.
     * @param rotationDirection The direction of the rotation.
     * @param centerX The first dimension of the position of the center of the circle on which the helix projects.
     * @param centerY The second dimension of the position of the center of the circle on which the helix projects.
     * @param endX The first dimension of the end position of the helix's arc component.
     * @param endY The second dimension of the end position of the helix's arc component.
     * @param endpoint Positions for the helix's line component axes, relative to their home positions.
     */
    void helixAbsoluteOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY, const std::vector<Measurement>& endpoint);

    void helixAbsoluteOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY, std::initializer_list<Measurement> endpoint);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void helixAbsoluteOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY, TIterator begin, TIterator end) {
        return helixAbsoluteOn(targetAxesIndices, rotationDirection, centerX, centerY, endX, endY, std::vector<Measurement>(begin,end));
    }

    template<typename... T>
    void helixAbsoluteOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY, T&&... endpoint) {
        return helixAbsoluteOn(targetAxesIndices, rotationDirection, centerX, centerY, endX, endY, {std::forward<T>(endpoint)...});
    }
    /**
     * Queue a relative helix movement in the stream.
     * Requires at least Firmware 7.28.
     * @param targetAxesIndices Indices of the axes in the stream the movement targets.
     * Refers to the axes provided during the stream setup or further execution.
     * Indices are zero-based.
     * The first two axes refer to the helix's arc component,
     * while the rest refers to the helix's line component.
     * @param rotationDirection The direction of the rotation.
     * @param centerX The first dimension of the position of the center of the circle on which the helix projects.
     * @param centerY The second dimension of the position of the center of the circle on which the helix projects.
     * @param endX The first dimension of the end position of the helix's arc component.
     * @param endY The second dimension of the end position of the helix's arc component.
     * @param endpoint Positions for the helix's line component axes, relative to their positions before movement.
     */
    void helixRelativeOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY, const std::vector<Measurement>& endpoint);

    void helixRelativeOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY, std::initializer_list<Measurement> endpoint);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void helixRelativeOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY, TIterator begin, TIterator end) {
        return helixRelativeOn(targetAxesIndices, rotationDirection, centerX, centerY, endX, endY, std::vector<Measurement>(begin,end));
    }

    template<typename... T>
    void helixRelativeOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY, const Measurement& endX, const Measurement& endY, T&&... endpoint) {
        return helixRelativeOn(targetAxesIndices, rotationDirection, centerX, centerY, endX, endY, {std::forward<T>(endpoint)...});
    }
    /**
     * Queue an absolute circle movement on the first two axes of the stream.
     * Absolute meaning that the home positions of the axes are treated as the origin.
     * @param rotationDirection The direction of the rotation.
     * @param centerX The first dimension of the position of the center of the circle.
     * @param centerY The second dimension of the position of the center of the circle.
     */
    void circleAbsolute(RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY);
    /**
     * Queue a relative circle movement on the first two axes of the stream.
     * Relative meaning that the current position of the axes is treated as the origin.
     * @param rotationDirection The direction of the rotation.
     * @param centerX The first dimension of the position of the center of the circle.
     * @param centerY The second dimension of the position of the center of the circle.
     */
    void circleRelative(RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY);
    /**
     * Queue an absolute circle movement in the stream.
     * The movement will only target the specified subset of axes in the stream.
     * Requires at least Firmware 7.11.
     * @param targetAxesIndices Indices of the axes in the stream the movement targets.
     * Refers to the axes provided during the stream setup or further execution.
     * Indices are zero-based.
     * @param rotationDirection The direction of the rotation.
     * @param centerX The first dimension of the position of the center of the circle.
     * @param centerY The second dimension of the position of the center of the circle.
     */
    void circleAbsoluteOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY);
    /**
     * Queue a relative circle movement in the stream.
     * The movement will only target the specified subset of axes in the stream.
     * Requires at least Firmware 7.11.
     * @param targetAxesIndices Indices of the axes in the stream the movement targets.
     * Refers to the axes provided during the stream setup or further execution.
     * Indices are zero-based.
     * @param rotationDirection The direction of the rotation.
     * @param centerX The first dimension of the position of the center of the circle.
     * @param centerY The second dimension of the position of the center of the circle.
     */
    void circleRelativeOn(const std::vector<int>& targetAxesIndices, RotationDirection rotationDirection, const Measurement& centerX, const Measurement& centerY);
    /**
     * Wait a specified time.
     * @param time Amount of time to wait.
     * @param unit Units of time.
     */
    void wait(double time, Units unit = Units::NATIVE);
    /**
     * Waits until the live stream executes all queued actions.
     * @param throwErrorOnFault Determines whether to throw error when fault is observed.
     */
    void waitUntilIdle(bool throwErrorOnFault = true);

    /**
     * Waits until the live stream executes all queued actions.
     * @param options A struct of type WaitUntilIdleOptions. It has the following members:
     * * `throwErrorOnFault`: Determines whether to throw error when fault is observed.
     */
    void waitUntilIdle(const Stream::WaitUntilIdleOptions& options);
    /**
     * Cork the front of the stream's action queue, blocking execution.
     * Execution resumes upon uncorking the queue, or when the number of queued actions reaches its limit.
     * Corking eliminates discontinuities in motion due to subsequent stream commands reaching the device late.
     * You can only cork an idle live stream.
     */
    void cork();
    /**
     * Uncork the front of the queue, unblocking command execution.
     * You can only uncork an idle live stream that is corked.
     */
    void uncork();
    /**
     * Pauses or resumes execution of the stream in live mode.
     * The hold only takes effect during execution of motion segments.
     * @param hold True to pause execution, false to resume.
     */
    void setHold(bool hold);
    /**
     * Returns a boolean value indicating whether the live stream is executing a queued action.
     * @return True if the stream is executing a queued action.
     */
    bool isBusy();
    /**
     * Gets the maximum speed of the live stream.
     * Converts the units using the first axis of the stream.
     * @param unit Units of velocity.
     * @return The maximum speed of the stream.
     */
    double getMaxSpeed(Units unit = Units::NATIVE);
    /**
     * Sets the maximum speed of the live stream.
     * Converts the units using the first axis of the stream.
     * @param maxSpeed Maximum speed at which any stream action is executed.
     * @param unit Units of velocity.
     */
    void setMaxSpeed(double maxSpeed, Units unit = Units::NATIVE);
    /**
     * Gets the maximum tangential acceleration of the live stream.
     * Converts the units using the first axis of the stream.
     * @param unit Units of acceleration.
     * @return The maximum tangential acceleration of the live stream.
     */
    double getMaxTangentialAcceleration(Units unit = Units::NATIVE);
    /**
     * Sets the maximum tangential acceleration of the live stream.
     * Converts the units using the first axis of the stream.
     * @param maxTangentialAcceleration Maximum tangential acceleration at which any stream action is executed.
     * @param unit Units of acceleration.
     */
    void setMaxTangentialAcceleration(double maxTangentialAcceleration, Units unit = Units::NATIVE);
    /**
     * Gets the maximum centripetal acceleration of the live stream.
     * Converts the units using the first axis of the stream.
     * @param unit Units of acceleration.
     * @return The maximum centripetal acceleration of the live stream.
     */
    double getMaxCentripetalAcceleration(Units unit = Units::NATIVE);
    /**
     * Sets the maximum centripetal acceleration of the live stream.
     * Converts the units using the first axis of the stream.
     * @param maxCentripetalAcceleration Maximum centripetal acceleration at which any stream action is executed.
     * @param unit Units of acceleration.
     */
    void setMaxCentripetalAcceleration(double maxCentripetalAcceleration, Units unit = Units::NATIVE);
    /**
     * Returns a string which represents the stream.
     * @return String which represents the stream.
     */
    std::string toString() const;
    /**
     * Disables the stream.
     * If the stream is not setup, this command does nothing.
     * Once disabled, the stream will no longer accept stream commands.
     * The stream will process the rest of the commands in the queue until it is empty.
     */
    void disable();
    /**
     * Sends a generic ASCII command to the stream.
     * Keeps resending the command while the device rejects with AGAIN reason.
     * @param command Command and its parameters.
     */
    void genericCommand(const std::string& command);
    /**
     * Sends a batch of generic ASCII commands to the stream.
     * Keeps resending command while the device rejects with AGAIN reason.
     * The batch is atomic in terms of thread safety.
     * @param batch Array of commands.
     */
    void genericCommandBatch(const std::vector<std::string>& batch);
    /**
     * Queries the stream status from the device
     * and returns boolean indicating whether the stream is disabled.
     * Useful to determine if streaming was interrupted by other movements.
     * @return True if the stream is disabled.
     */
    bool checkDisabled();
    /**
     * Makes the stream throw StreamDiscontinuityException when it encounters discontinuities (ND warning flag).
     */
    void treatDiscontinuitiesAsError();
    /**
     * Prevents StreamDiscontinuityException as a result of expected discontinuity when resuming streaming.
     */
    void ignoreCurrentDiscontinuity();
    /**
     * Device that controls this stream.
     */
    Device getDevice() const;
    /**
     * The number that identifies the stream on the device.
     */
    int getStreamId() const;
    /**
     * Current mode of the stream.
     */
    StreamMode getMode() const;
    /**
     * An array of axes definitions the stream is set up to control.
     */
    std::vector<StreamAxisDefinition> getAxes() const;
    /**
     * Gets an object that provides access to I/O for this stream.
     */
    StreamIo getIo() const;
protected:
    /**
     * Gets the axes of the stream.
     * @return An array of axis numbers of the axes the stream is set up to control.
     */
    std::vector<StreamAxisDefinition> retrieveAxes() const;
    /**
     * Get the mode of the stream.
     * @return Mode of the stream.
     */
    StreamMode retrieveMode() const;
    Device _device;
    int _streamId;
    StreamIo _io;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
