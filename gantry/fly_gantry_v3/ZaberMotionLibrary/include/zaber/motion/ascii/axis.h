// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <initializer_list>
#include <string>
#include <utility>
#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/ascii/warnings.h"
#include "zaber/motion/dto/ascii/axis_identity.h"
#include "zaber/motion/dto/ascii/axis_type.h"
#include "zaber/motion/dto/ascii/response.h"
#include "zaber/motion/dto/cyclic_direction.h"
#include "zaber/motion/dto/measurement.h"
#include "zaber/motion/dto/unit_conversion_descriptor.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {

/* Forward Declarations */
class AxisSettings;
class AxisStorage;
class Warnings;


/**
 * Represents an axis of motion associated with a device.
 */
class Axis {
public:
    struct HomeOptions {
        // Determines whether function should return after the movement is finished or just started.
        bool waitUntilIdle {true};
    };

    struct StopOptions {
        // Determines whether function should return after the movement is finished or just started.
        bool waitUntilIdle {true};
    };

    struct WaitUntilIdleOptions {
        // Determines whether to throw error when fault is observed.
        bool throwErrorOnFault {true};
    };

    struct MoveAbsoluteOptions {
        // Determines whether function should return after the movement is finished or just started.
        bool waitUntilIdle {true};
        // Movement velocity.
        // Default value of 0 indicates that the maxspeed setting is used instead.
        // Requires at least Firmware 7.25.
        double velocity {0};
        // Units of velocity.
        Units velocityUnit {Units::NATIVE};
        // Movement acceleration.
        // Default value of 0 indicates that the accel setting is used instead.
        // Requires at least Firmware 7.25.
        double acceleration {0};
        // Units of acceleration.
        Units accelerationUnit {Units::NATIVE};
        // Which direction a cyclic device should take to get to the target position.
        std::optional<CyclicDirection> cyclicDirection {};
        // Number of extra cycles to complete before stopping at the target.
        std::optional<int> extraCycles {};
    };

    struct MoveMaxOptions {
        // Determines whether function should return after the movement is finished or just started.
        bool waitUntilIdle {true};
        // Movement velocity.
        // Default value of 0 indicates that the maxspeed setting is used instead.
        // Requires at least Firmware 7.25.
        double velocity {0};
        // Units of velocity.
        Units velocityUnit {Units::NATIVE};
        // Movement acceleration.
        // Default value of 0 indicates that the accel setting is used instead.
        // Requires at least Firmware 7.25.
        double acceleration {0};
        // Units of acceleration.
        Units accelerationUnit {Units::NATIVE};
    };

    struct MoveMinOptions {
        // Determines whether function should return after the movement is finished or just started.
        bool waitUntilIdle {true};
        // Movement velocity.
        // Default value of 0 indicates that the maxspeed setting is used instead.
        // Requires at least Firmware 7.25.
        double velocity {0};
        // Units of velocity.
        Units velocityUnit {Units::NATIVE};
        // Movement acceleration.
        // Default value of 0 indicates that the accel setting is used instead.
        // Requires at least Firmware 7.25.
        double acceleration {0};
        // Units of acceleration.
        Units accelerationUnit {Units::NATIVE};
    };

    struct MoveRelativeOptions {
        // Determines whether function should return after the movement is finished or just started.
        bool waitUntilIdle {true};
        // Movement velocity.
        // Default value of 0 indicates that the maxspeed setting is used instead.
        // Requires at least Firmware 7.25.
        double velocity {0};
        // Units of velocity.
        Units velocityUnit {Units::NATIVE};
        // Movement acceleration.
        // Default value of 0 indicates that the accel setting is used instead.
        // Requires at least Firmware 7.25.
        double acceleration {0};
        // Units of acceleration.
        Units accelerationUnit {Units::NATIVE};
    };

    struct MoveVelocityOptions {
        // Movement acceleration.
        // Default value of 0 indicates that the accel setting is used instead.
        // Requires at least Firmware 7.25.
        double acceleration {0};
        // Units of acceleration.
        Units accelerationUnit {Units::NATIVE};
    };

    struct MoveIndexOptions {
        // Determines whether function should return after the movement is finished or just started.
        bool waitUntilIdle {true};
        // Movement velocity.
        // Default value of 0 indicates that the maxspeed setting is used instead.
        // Requires at least Firmware 7.25.
        double velocity {0};
        // Units of velocity.
        Units velocityUnit {Units::NATIVE};
        // Movement acceleration.
        // Default value of 0 indicates that the accel setting is used instead.
        // Requires at least Firmware 7.25.
        double acceleration {0};
        // Units of acceleration.
        Units accelerationUnit {Units::NATIVE};
    };

    struct GenericCommandOptions {
        // Controls whether to throw an exception when the device rejects the command.
        bool checkErrors {true};
        // The timeout, in milliseconds, for a device to respond to the command.
        // Overrides the connection default request timeout.
        int timeout {0};
    };

    struct GenericCommandMultiResponseOptions {
        // Controls whether to throw an exception when a device rejects the command.
        bool checkErrors {true};
        // The timeout, in milliseconds, for a device to respond to the command.
        // Overrides the connection default request timeout.
        int timeout {0};
    };

    struct CanSetStateOptions {
        // The firmware version of the device to apply the state to.
        // Use this to ensure the state will still be compatible after an update.
        std::optional<FirmwareVersion> firmwareVersion {};
    };

    struct DriverEnableOptions {
        // Timeout in seconds. Specify 0 to attempt to enable the driver once.
        double timeout {10};
    };

    struct MoveSinOptions {
        // Number of sinusoidal cycles to complete.
        // Must be a multiple of 0.5
        // If count is not specified or set to 0, the axis will move indefinitely.
        double count {0};
        // Determines whether function should return after the movement is finished or just started.
        bool waitUntilIdle {true};
    };

    struct MoveSinStopOptions {
        // Determines whether function should return after the movement is finished.
        bool waitUntilIdle {true};
    };

    Axis(Device device, int axisNumber);

    Axis();

    /**
     * Homes axis. Axis returns to its homing position.
     * @param waitUntilIdle Determines whether function should return after the movement is finished or just started.
     */
    void home(bool waitUntilIdle = true);

    /**
     * Homes axis. Axis returns to its homing position.
     * @param options A struct of type HomeOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished or just started.
     */
    void home(const Axis::HomeOptions& options);
    /**
     * Stops ongoing axis movement. Decelerates until zero speed.
     * @param waitUntilIdle Determines whether function should return after the movement is finished or just started.
     */
    void stop(bool waitUntilIdle = true);

    /**
     * Stops ongoing axis movement. Decelerates until zero speed.
     * @param options A struct of type StopOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished or just started.
     */
    void stop(const Axis::StopOptions& options);
    /**
     * Parks the axis in anticipation of turning the power off.
     * It can later be powered on, unparked, and moved without first having to home it.
     */
    void park();
    /**
     * Unparks axis. Axis will now be able to move.
     */
    void unpark();
    /**
     * Returns bool indicating whether the axis is parked or not.
     * @return True if the axis is currently parked. False otherwise.
     */
    bool isParked();
    /**
     * Waits until axis stops moving.
     * @param throwErrorOnFault Determines whether to throw error when fault is observed.
     */
    void waitUntilIdle(bool throwErrorOnFault = true);

    /**
     * Waits until axis stops moving.
     * @param options A struct of type WaitUntilIdleOptions. It has the following members:
     * * `throwErrorOnFault`: Determines whether to throw error when fault is observed.
     */
    void waitUntilIdle(const Axis::WaitUntilIdleOptions& options);
    /**
     * Returns bool indicating whether the axis is executing a motion command.
     * @return True if the axis is currently executing a motion command.
     */
    bool isBusy();
    /**
     * Returns bool indicating whether the axis has position reference and was homed.
     * @return True if the axis has position reference and was homed.
     */
    bool isHomed();
    /**
     * Move axis to absolute position.
     * @param position Absolute position.
     * @param unit Units of position.
     * @param waitUntilIdle Determines whether function should return after the movement is finished or just started.
     * @param velocity Movement velocity.
     * Default value of 0 indicates that the maxspeed setting is used instead.
     * Requires at least Firmware 7.25.
     * @param velocityUnit Units of velocity.
     * @param acceleration Movement acceleration.
     * Default value of 0 indicates that the accel setting is used instead.
     * Requires at least Firmware 7.25.
     * @param accelerationUnit Units of acceleration.
     * @param cyclicDirection Which direction a cyclic device should take to get to the target position.
     * @param extraCycles Number of extra cycles to complete before stopping at the target.
     */
    void moveAbsolute(double position, Units unit = Units::NATIVE, bool waitUntilIdle = true, double velocity = 0, Units velocityUnit = Units::NATIVE, double acceleration = 0, Units accelerationUnit = Units::NATIVE, const std::optional<CyclicDirection>& cyclicDirection = {}, const std::optional<int>& extraCycles = {});

    /**
     * Move axis to absolute position.
     * @param position Absolute position.
     * @param unit Units of position.
     * @param options A struct of type MoveAbsoluteOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished or just started.
     * * `velocity`: Movement velocity.
     *   Default value of 0 indicates that the maxspeed setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `velocityUnit`: Units of velocity.
     * * `acceleration`: Movement acceleration.
     *   Default value of 0 indicates that the accel setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `accelerationUnit`: Units of acceleration.
     * * `cyclicDirection`: Which direction a cyclic device should take to get to the target position.
     * * `extraCycles`: Number of extra cycles to complete before stopping at the target.
     */
    void moveAbsolute(double position, Units unit, const Axis::MoveAbsoluteOptions& options);
    /**
     * Moves the axis to the maximum position as specified by limit.max.
     * @param waitUntilIdle Determines whether function should return after the movement is finished or just started.
     * @param velocity Movement velocity.
     * Default value of 0 indicates that the maxspeed setting is used instead.
     * Requires at least Firmware 7.25.
     * @param velocityUnit Units of velocity.
     * @param acceleration Movement acceleration.
     * Default value of 0 indicates that the accel setting is used instead.
     * Requires at least Firmware 7.25.
     * @param accelerationUnit Units of acceleration.
     */
    void moveMax(bool waitUntilIdle = true, double velocity = 0, Units velocityUnit = Units::NATIVE, double acceleration = 0, Units accelerationUnit = Units::NATIVE);

    /**
     * Moves the axis to the maximum position as specified by limit.max.
     * @param options A struct of type MoveMaxOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished or just started.
     * * `velocity`: Movement velocity.
     *   Default value of 0 indicates that the maxspeed setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `velocityUnit`: Units of velocity.
     * * `acceleration`: Movement acceleration.
     *   Default value of 0 indicates that the accel setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `accelerationUnit`: Units of acceleration.
     */
    void moveMax(const Axis::MoveMaxOptions& options);
    /**
     * Moves the axis to the minimum position as specified by limit.min.
     * @param waitUntilIdle Determines whether function should return after the movement is finished or just started.
     * @param velocity Movement velocity.
     * Default value of 0 indicates that the maxspeed setting is used instead.
     * Requires at least Firmware 7.25.
     * @param velocityUnit Units of velocity.
     * @param acceleration Movement acceleration.
     * Default value of 0 indicates that the accel setting is used instead.
     * Requires at least Firmware 7.25.
     * @param accelerationUnit Units of acceleration.
     */
    void moveMin(bool waitUntilIdle = true, double velocity = 0, Units velocityUnit = Units::NATIVE, double acceleration = 0, Units accelerationUnit = Units::NATIVE);

    /**
     * Moves the axis to the minimum position as specified by limit.min.
     * @param options A struct of type MoveMinOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished or just started.
     * * `velocity`: Movement velocity.
     *   Default value of 0 indicates that the maxspeed setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `velocityUnit`: Units of velocity.
     * * `acceleration`: Movement acceleration.
     *   Default value of 0 indicates that the accel setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `accelerationUnit`: Units of acceleration.
     */
    void moveMin(const Axis::MoveMinOptions& options);
    /**
     * Move axis to position relative to current position.
     * @param position Relative position.
     * @param unit Units of position.
     * @param waitUntilIdle Determines whether function should return after the movement is finished or just started.
     * @param velocity Movement velocity.
     * Default value of 0 indicates that the maxspeed setting is used instead.
     * Requires at least Firmware 7.25.
     * @param velocityUnit Units of velocity.
     * @param acceleration Movement acceleration.
     * Default value of 0 indicates that the accel setting is used instead.
     * Requires at least Firmware 7.25.
     * @param accelerationUnit Units of acceleration.
     */
    void moveRelative(double position, Units unit = Units::NATIVE, bool waitUntilIdle = true, double velocity = 0, Units velocityUnit = Units::NATIVE, double acceleration = 0, Units accelerationUnit = Units::NATIVE);

    /**
     * Move axis to position relative to current position.
     * @param position Relative position.
     * @param unit Units of position.
     * @param options A struct of type MoveRelativeOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished or just started.
     * * `velocity`: Movement velocity.
     *   Default value of 0 indicates that the maxspeed setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `velocityUnit`: Units of velocity.
     * * `acceleration`: Movement acceleration.
     *   Default value of 0 indicates that the accel setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `accelerationUnit`: Units of acceleration.
     */
    void moveRelative(double position, Units unit, const Axis::MoveRelativeOptions& options);
    /**
     * Begins to move axis at specified speed.
     * @param velocity Movement velocity.
     * @param unit Units of velocity.
     * @param acceleration Movement acceleration.
     * Default value of 0 indicates that the accel setting is used instead.
     * Requires at least Firmware 7.25.
     * @param accelerationUnit Units of acceleration.
     */
    void moveVelocity(double velocity, Units unit = Units::NATIVE, double acceleration = 0, Units accelerationUnit = Units::NATIVE);

    /**
     * Begins to move axis at specified speed.
     * @param velocity Movement velocity.
     * @param unit Units of velocity.
     * @param options A struct of type MoveVelocityOptions. It has the following members:
     * * `acceleration`: Movement acceleration.
     *   Default value of 0 indicates that the accel setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `accelerationUnit`: Units of acceleration.
     */
    void moveVelocity(double velocity, Units unit, const Axis::MoveVelocityOptions& options);
    /**
     * Returns current axis position.
     * @param unit Units of position.
     * @return Axis position.
     */
    double getPosition(Units unit = Units::NATIVE);
    /**
     * Gets number of index positions of the axis.
     * @return Number of index positions.
     */
    int getNumberOfIndexPositions();
    /**
     * Returns current axis index position.
     * @return Index position starting from 1 or 0 if the position is not an index position.
     */
    int getIndexPosition();
    /**
     * Moves the axis to index position.
     * @param index Index position. Index positions are numbered from 1.
     * @param waitUntilIdle Determines whether function should return after the movement is finished or just started.
     * @param velocity Movement velocity.
     * Default value of 0 indicates that the maxspeed setting is used instead.
     * Requires at least Firmware 7.25.
     * @param velocityUnit Units of velocity.
     * @param acceleration Movement acceleration.
     * Default value of 0 indicates that the accel setting is used instead.
     * Requires at least Firmware 7.25.
     * @param accelerationUnit Units of acceleration.
     */
    void moveIndex(int index, bool waitUntilIdle = true, double velocity = 0, Units velocityUnit = Units::NATIVE, double acceleration = 0, Units accelerationUnit = Units::NATIVE);

    /**
     * Moves the axis to index position.
     * @param index Index position. Index positions are numbered from 1.
     * @param options A struct of type MoveIndexOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished or just started.
     * * `velocity`: Movement velocity.
     *   Default value of 0 indicates that the maxspeed setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `velocityUnit`: Units of velocity.
     * * `acceleration`: Movement acceleration.
     *   Default value of 0 indicates that the accel setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `accelerationUnit`: Units of acceleration.
     */
    void moveIndex(int index, const Axis::MoveIndexOptions& options);
    /**
     * Sends a generic ASCII command to this axis.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param checkErrors Controls whether to throw an exception when the device rejects the command.
     * @param timeout The timeout, in milliseconds, for a device to respond to the command.
     * Overrides the connection default request timeout.
     * @return A response to the command.
     */
    Response genericCommand(const std::string& command, bool checkErrors = true, int timeout = 0);

    /**
     * Sends a generic ASCII command to this axis.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param options A struct of type GenericCommandOptions. It has the following members:
     * * `checkErrors`: Controls whether to throw an exception when the device rejects the command.
     * * `timeout`: The timeout, in milliseconds, for a device to respond to the command.
     *   Overrides the connection default request timeout.
     * @return A response to the command.
     */
    Response genericCommand(const std::string& command, const Axis::GenericCommandOptions& options);
    /**
     * Sends a generic ASCII command to this axis and expect multiple responses.
     * Responses are returned in order of arrival.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param checkErrors Controls whether to throw an exception when a device rejects the command.
     * @param timeout The timeout, in milliseconds, for a device to respond to the command.
     * Overrides the connection default request timeout.
     * @return All responses to the command.
     */
    std::vector<Response> genericCommandMultiResponse(const std::string& command, bool checkErrors = true, int timeout = 0);

    /**
     * Sends a generic ASCII command to this axis and expect multiple responses.
     * Responses are returned in order of arrival.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param options A struct of type GenericCommandMultiResponseOptions. It has the following members:
     * * `checkErrors`: Controls whether to throw an exception when a device rejects the command.
     * * `timeout`: The timeout, in milliseconds, for a device to respond to the command.
     *   Overrides the connection default request timeout.
     * @return All responses to the command.
     */
    std::vector<Response> genericCommandMultiResponse(const std::string& command, const Axis::GenericCommandMultiResponseOptions& options);
    /**
     * Sends a generic ASCII command to this axis without expecting a response and without adding a message ID
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     */
    void genericCommandNoResponse(const std::string& command);
    /**
     * Formats parameters into a command and performs unit conversions.
     * Parameters in the command template are denoted by a question mark.
     * Command returned is only valid for this axis and this device.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param commandTemplate Template of a command to prepare. Parameters are denoted by question marks.
     * @param parameters Variable number of command parameters.
     * @return Command with converted parameters.
     */
    std::string prepareCommand(const std::string& commandTemplate, const std::vector<Measurement>& parameters);

    std::string prepareCommand(const std::string& commandTemplate, std::initializer_list<Measurement> parameters);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    std::string prepareCommand(const std::string& commandTemplate, TIterator begin, TIterator end) {
        return prepareCommand(commandTemplate, std::vector<Measurement>(begin,end));
    }

    template<typename... T>
    std::string prepareCommand(const std::string& commandTemplate, T&&... parameters) {
        return prepareCommand(commandTemplate, {std::forward<T>(parameters)...});
    }
    /**
     * Retrieves unit conversion descriptors for a command, allowing unit conversion without a device.
     * The descriptors can be used with the ConvertTo/FromNativeUnits methods of the UnitTable class.
     * Parameters in the command template are denoted by a question mark.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param commandTemplate Template of the command. Parameters are denoted by question marks.
     * @return Unit conversion descriptor for each parameter in the command. Nil if a parameter does not have conversion.
     */
    std::vector<std::optional<UnitConversionDescriptor>> getCommandUnitConversionDescriptors(const std::string& commandTemplate);
    /**
     * Sets the user-assigned peripheral label.
     * The label is stored on the controller and recognized by other software.
     * @param label Label to set.
     */
    void setLabel(const std::string& label);
    /**
     * Returns a string that represents the axis.
     * @return A string that represents the axis.
     */
    std::string toString() const;
    /**
     * Returns a serialization of the current axis state that can be saved and reapplied.
     * @return A serialization of the current state of the axis.
     */
    std::string getState();
    /**
     * Applies a saved state to this axis.
     * @param state The state object to apply to this axis.
     * @return Reports of any issues that were handled, but caused the state to not be exactly restored.
     */
    SetStateAxisResponse setState(const std::string& state);
    /**
     * Checks if a state can be applied to this axis.
     * This only covers exceptions that can be determined statically such as mismatches of ID or version,
     * the process of applying the state can still fail when running.
     * @param state The state object to check against.
     * @param firmwareVersion The firmware version of the device to apply the state to.
     * Use this to ensure the state will still be compatible after an update.
     * @return An explanation of why this state cannot be set to this axis.
     */
    std::optional<std::string> canSetState(const std::string& state, const std::optional<FirmwareVersion>& firmwareVersion = {});

    /**
     * Checks if a state can be applied to this axis.
     * This only covers exceptions that can be determined statically such as mismatches of ID or version,
     * the process of applying the state can still fail when running.
     * @param state The state object to check against.
     * @param options A struct of type CanSetStateOptions. It has the following members:
     * * `firmwareVersion`: The firmware version of the device to apply the state to.
     *   Use this to ensure the state will still be compatible after an update.
     * @return An explanation of why this state cannot be set to this axis.
     */
    std::optional<std::string> canSetState(const std::string& state, const Axis::CanSetStateOptions& options);
    /**
     * Disables the driver, which prevents current from being sent to the motor or load.
     * If the driver is already disabled, the driver remains disabled.
     */
    void driverDisable();
    /**
     * Attempts to enable the driver repeatedly for the specified timeout.
     * If the driver is already enabled, the driver remains enabled.
     * @param timeout Timeout in seconds. Specify 0 to attempt to enable the driver once.
     */
    void driverEnable(double timeout = 10);

    /**
     * Attempts to enable the driver repeatedly for the specified timeout.
     * If the driver is already enabled, the driver remains enabled.
     * @param options A struct of type DriverEnableOptions. It has the following members:
     * * `timeout`: Timeout in seconds. Specify 0 to attempt to enable the driver once.
     */
    void driverEnable(const Axis::DriverEnableOptions& options);
    /**
     * Activates a peripheral on this axis.
     * Removes all identity information for the device.
     * Run the identify method on the device after activating to refresh the information.
     */
    void activate();
    /**
     * Restores all axis settings to their default values.
     * Deletes all zaber axis storage keys.
     * Disables lockstep if the axis is part of one. Unparks the axis.
     * Preserves storage.
     * The device needs to be identified again after the restore.
     */
    void restore();
    /**
     * Moves the axis in a sinusoidal trajectory.
     * @param amplitude Amplitude of the sinusoidal motion (half of the motion's peak-to-peak range).
     * @param amplitudeUnits Units of position.
     * @param period Period of the sinusoidal motion in milliseconds.
     * @param periodUnits Units of time.
     * @param count Number of sinusoidal cycles to complete.
     * Must be a multiple of 0.5
     * If count is not specified or set to 0, the axis will move indefinitely.
     * @param waitUntilIdle Determines whether function should return after the movement is finished or just started.
     */
    void moveSin(double amplitude, Units amplitudeUnits, double period, Units periodUnits, double count = 0, bool waitUntilIdle = true);

    /**
     * Moves the axis in a sinusoidal trajectory.
     * @param amplitude Amplitude of the sinusoidal motion (half of the motion's peak-to-peak range).
     * @param amplitudeUnits Units of position.
     * @param period Period of the sinusoidal motion in milliseconds.
     * @param periodUnits Units of time.
     * @param options A struct of type MoveSinOptions. It has the following members:
     * * `count`: Number of sinusoidal cycles to complete.
     *   Must be a multiple of 0.5
     *   If count is not specified or set to 0, the axis will move indefinitely.
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished or just started.
     */
    void moveSin(double amplitude, Units amplitudeUnits, double period, Units periodUnits, const Axis::MoveSinOptions& options);
    /**
     * Stops the axis at the end of the sinusoidal trajectory.
     * If the sinusoidal motion was started with an integer-plus-half cycle count,
     * the motion ends at the half-way point of the sinusoidal trajectory.
     * @param waitUntilIdle Determines whether function should return after the movement is finished.
     */
    void moveSinStop(bool waitUntilIdle = true);

    /**
     * Stops the axis at the end of the sinusoidal trajectory.
     * If the sinusoidal motion was started with an integer-plus-half cycle count,
     * the motion ends at the half-way point of the sinusoidal trajectory.
     * @param options A struct of type MoveSinStopOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished.
     */
    void moveSinStop(const Axis::MoveSinStopOptions& options);
    /**
     * Device that controls this axis.
     */
    Device getDevice() const;
    /**
     * The axis number identifies the axis on the device.
     * The first axis has the number one.
     */
    int getAxisNumber() const;
    /**
     * Settings and properties of this axis.
     */
    AxisSettings getSettings() const;
    /**
     * Key-value storage of this axis.
     * Requires at least Firmware 7.30.
     */
    AxisStorage getStorage() const;
    /**
     * Warnings and faults of this axis.
     */
    Warnings getWarnings() const;
    /**
     * Identity of the axis.
     */
    AxisIdentity getIdentity() const;
    /**
     * Unique ID of the peripheral hardware.
     */
    int getPeripheralId() const;
    /**
     * Name of the peripheral.
     */
    std::string getPeripheralName() const;
    /**
     * Serial number of the peripheral, or 0 when not applicable.
     */
    unsigned int getPeripheralSerialNumber() const;
    /**
     * Indicates whether the axis is a peripheral or part of an integrated device.
     */
    bool getIsPeripheral() const;
    /**
     * Determines the type of an axis and units it accepts.
     */
    AxisType getAxisType() const;
    /**
     * The number of microsteps per full step for motion axes. Always equal to 0 for non-motion axes.
     */
    unsigned int getResolution() const;
    /**
     * User-assigned label of the peripheral.
     */
    std::string getLabel() const;
protected:
    /**
     * Gets the peripheral name.
     * @return The label.
     */
    std::string retrieveLabel() const;
    /**
     * Returns identity.
     * @return Axis identity.
     */
    AxisIdentity retrieveIdentity() const;
    Device _device;
    int _axisNumber;
    Warnings _warnings;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
