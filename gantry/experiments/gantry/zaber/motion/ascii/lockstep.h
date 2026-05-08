// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {


/**
 * Represents a lockstep group with this ID on a device.
 * A lockstep group is a movement synchronized pair of axes on a device.
 * Requires at least Firmware 6.15 or 7.11.
 */
class Lockstep {
public:
    struct StopOptions {
        // Determines whether function should return after the movement is finished or just started.
        bool waitUntilIdle {true};
    };

    struct HomeOptions {
        // Determines whether function should return after the movement is finished or just started.
        bool waitUntilIdle {true};
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

    struct WaitUntilIdleOptions {
        // Determines whether to throw error when fault is observed.
        bool throwErrorOnFault {true};
    };

    struct SetToleranceOptions {
        // Optional index of a secondary axis to set the tolerance for.
        // If left empty or set to 0, the tolerance is set to all the secondary axes.
        int axisIndex {0};
    };

    Lockstep(Device device, int lockstepGroupId);

    /**
     * Activate the lockstep group on the axes specified.
     * @param axes The numbers of axes in the lockstep group.
     */
    void enable(const std::vector<int>& axes);

    void enable(std::initializer_list<int> axes);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    void enable(TIterator begin, TIterator end) {
        return enable(std::vector<int>(begin,end));
    }

    template<typename... T>
    void enable(T&&... axes) {
        return enable({std::forward<T>(axes)...});
    }
    /**
     * Disable the lockstep group.
     */
    void disable();
    /**
     * Stops ongoing lockstep group movement. Decelerates until zero speed.
     * @param waitUntilIdle Determines whether function should return after the movement is finished or just started.
     */
    void stop(bool waitUntilIdle = true);

    /**
     * Stops ongoing lockstep group movement. Decelerates until zero speed.
     * @param options A struct of type StopOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished or just started.
     */
    void stop(const Lockstep::StopOptions& options);
    /**
     * Retracts the axes of the lockstep group until a home associated with an individual axis is detected.
     * @param waitUntilIdle Determines whether function should return after the movement is finished or just started.
     */
    void home(bool waitUntilIdle = true);

    /**
     * Retracts the axes of the lockstep group until a home associated with an individual axis is detected.
     * @param options A struct of type HomeOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished or just started.
     */
    void home(const Lockstep::HomeOptions& options);
    /**
     * Move the first axis of the lockstep group to an absolute position.
     * The other axes in the lockstep group maintain their offsets throughout movement.
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
     */
    void moveAbsolute(double position, Units unit = Units::NATIVE, bool waitUntilIdle = true, double velocity = 0, Units velocityUnit = Units::NATIVE, double acceleration = 0, Units accelerationUnit = Units::NATIVE);

    /**
     * Move the first axis of the lockstep group to an absolute position.
     * The other axes in the lockstep group maintain their offsets throughout movement.
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
     */
    void moveAbsolute(double position, Units unit, const Lockstep::MoveAbsoluteOptions& options);
    /**
     * Move the first axis of the lockstep group to a position relative to its current position.
     * The other axes in the lockstep group maintain their offsets throughout movement.
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
     * Move the first axis of the lockstep group to a position relative to its current position.
     * The other axes in the lockstep group maintain their offsets throughout movement.
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
    void moveRelative(double position, Units unit, const Lockstep::MoveRelativeOptions& options);
    /**
     * Moves the first axis of the lockstep group at the specified speed.
     * The other axes in the lockstep group maintain their offsets throughout movement.
     * @param velocity Movement velocity.
     * @param unit Units of velocity.
     * @param acceleration Movement acceleration.
     * Default value of 0 indicates that the accel setting is used instead.
     * Requires at least Firmware 7.25.
     * @param accelerationUnit Units of acceleration.
     */
    void moveVelocity(double velocity, Units unit = Units::NATIVE, double acceleration = 0, Units accelerationUnit = Units::NATIVE);

    /**
     * Moves the first axis of the lockstep group at the specified speed.
     * The other axes in the lockstep group maintain their offsets throughout movement.
     * @param velocity Movement velocity.
     * @param unit Units of velocity.
     * @param options A struct of type MoveVelocityOptions. It has the following members:
     * * `acceleration`: Movement acceleration.
     *   Default value of 0 indicates that the accel setting is used instead.
     *   Requires at least Firmware 7.25.
     * * `accelerationUnit`: Units of acceleration.
     */
    void moveVelocity(double velocity, Units unit, const Lockstep::MoveVelocityOptions& options);
    /**
     * Moves the first axis of the lockstep group in a sinusoidal trajectory.
     * The other axes in the lockstep group maintain their offsets throughout movement.
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
     * Moves the first axis of the lockstep group in a sinusoidal trajectory.
     * The other axes in the lockstep group maintain their offsets throughout movement.
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
    void moveSin(double amplitude, Units amplitudeUnits, double period, Units periodUnits, const Lockstep::MoveSinOptions& options);
    /**
     * Stops the lockstep group at the end of the sinusoidal trajectory for the first axis.
     * If the sinusoidal motion was started with an integer-plus-half cycle count,
     * the motion ends at the half-way point of the sinusoidal trajectory.
     * @param waitUntilIdle Determines whether function should return after the movement is finished.
     */
    void moveSinStop(bool waitUntilIdle = true);

    /**
     * Stops the lockstep group at the end of the sinusoidal trajectory for the first axis.
     * If the sinusoidal motion was started with an integer-plus-half cycle count,
     * the motion ends at the half-way point of the sinusoidal trajectory.
     * @param options A struct of type MoveSinStopOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether function should return after the movement is finished.
     */
    void moveSinStop(const Lockstep::MoveSinStopOptions& options);
    /**
     * Moves the axes to the maximum valid position.
     * The axes in the lockstep group maintain their offsets throughout movement.
     * Respects lim.max for all axes in the group.
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
     * Moves the axes to the maximum valid position.
     * The axes in the lockstep group maintain their offsets throughout movement.
     * Respects lim.max for all axes in the group.
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
    void moveMax(const Lockstep::MoveMaxOptions& options);
    /**
     * Moves the axes to the minimum valid position.
     * The axes in the lockstep group maintain their offsets throughout movement.
     * Respects lim.min for all axes in the group.
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
     * Moves the axes to the minimum valid position.
     * The axes in the lockstep group maintain their offsets throughout movement.
     * Respects lim.min for all axes in the group.
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
    void moveMin(const Lockstep::MoveMinOptions& options);
    /**
     * Waits until the lockstep group stops moving.
     * @param throwErrorOnFault Determines whether to throw error when fault is observed.
     */
    void waitUntilIdle(bool throwErrorOnFault = true);

    /**
     * Waits until the lockstep group stops moving.
     * @param options A struct of type WaitUntilIdleOptions. It has the following members:
     * * `throwErrorOnFault`: Determines whether to throw error when fault is observed.
     */
    void waitUntilIdle(const Lockstep::WaitUntilIdleOptions& options);
    /**
     * Returns bool indicating whether the lockstep group is executing a motion command.
     * @return True if the axes are currently executing a motion command.
     */
    bool isBusy();
    /**
     * Gets the axis numbers of the lockstep group.
     * @return Axis numbers in order specified when enabling lockstep.
     */
    std::vector<int> getAxisNumbers();
    /**
     * Gets the initial offsets of secondary axes of an enabled lockstep group.
     * @param unit Units of position.
     * Uses primary axis unit conversion.
     * @return Initial offset for each axis of the lockstep group.
     */
    std::vector<double> getOffsets(Units unit = Units::NATIVE);
    /**
     * Gets the twists of secondary axes of an enabled lockstep group.
     * @param unit Units of position.
     * Uses primary axis unit conversion.
     * @return Difference between the initial offset and the actual offset for each axis of the lockstep group.
     */
    std::vector<double> getTwists(Units unit = Units::NATIVE);
    /**
     * Returns current position of the primary axis.
     * @param unit Units of the position.
     * @return Primary axis position.
     */
    double getPosition(Units unit = Units::NATIVE);
    /**
     * Sets lockstep twist tolerance.
     * Twist tolerances that do not match the system configuration can reduce performance or damage the system.
     * @param tolerance Twist tolerance.
     * @param unit Units of the tolerance.
     * Uses primary axis unit conversion when setting to all axes,
     * otherwise uses specified secondary axis unit conversion.
     * @param axisIndex Optional index of a secondary axis to set the tolerance for.
     * If left empty or set to 0, the tolerance is set to all the secondary axes.
     */
    void setTolerance(double tolerance, Units unit = Units::NATIVE, int axisIndex = 0);

    /**
     * Sets lockstep twist tolerance.
     * Twist tolerances that do not match the system configuration can reduce performance or damage the system.
     * @param tolerance Twist tolerance.
     * @param unit Units of the tolerance.
     * Uses primary axis unit conversion when setting to all axes,
     * otherwise uses specified secondary axis unit conversion.
     * @param options A struct of type SetToleranceOptions. It has the following members:
     * * `axisIndex`: Optional index of a secondary axis to set the tolerance for.
     *   If left empty or set to 0, the tolerance is set to all the secondary axes.
     */
    void setTolerance(double tolerance, Units unit, const Lockstep::SetToleranceOptions& options);
    /**
     * Checks if the lockstep group is currently enabled on the device.
     * @return True if a lockstep group with this ID is enabled on the device.
     */
    bool isEnabled();
    /**
     * Returns a string which represents the enabled lockstep group.
     * @return String which represents the enabled lockstep group.
     */
    std::string toString() const;
    /**
     * Parks lockstep group in anticipation of turning the power off.
     * It can later be powered on, unparked, and moved without first having to home it.
     */
    void park();
    /**
     * Unparks lockstep group. Lockstep group will now be able to move.
     */
    void unpark();
    /**
     * Returns bool indicating whether the axis is parked or not.
     * @return True if lockstep group is parked.
     */
    bool isParked();
    /**
     * Device that controls this lockstep group.
     */
    Device getDevice() const;
    /**
     * The number that identifies the lockstep group on the device.
     */
    int getLockstepGroupId() const;
protected:
    Device _device;
    int _lockstepGroupId;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
