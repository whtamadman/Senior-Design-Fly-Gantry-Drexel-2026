// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include "zaber/motion/dto/product/ge_1_gripper_error.h"
#include "zaber/motion/dto/product/ge_1_gripper_state.h"
#include "zaber/motion/dto/product/ge_1_gripper_direction.h"

namespace zaber {
namespace motion {
namespace product {

/**
 * The default device address for GE1 series grippers.
 */
constexpr int DEFAULT_DEVICE_ADDRESS = 1;


/**
 * Class representing a GE1 series gripper.
 */
class GE1Gripper {
public:
    struct OpenConnectionOptions {
        // The address of the gripper to connect to.
        int deviceAddress {DEFAULT_DEVICE_ADDRESS};
        // The timeout in milliseconds for any request sent using this connection.
        int timeout {500};
    };

    struct HomeOptions {
        // Wait until homing has completed before returning.
        bool waitUntilIdle {true};
    };

    struct MoveOptions {
        // Wait until the move has completed before returning.
        bool waitUntilIdle {true};
    };

    struct MoveOpenOptions {
        // Wait until the move has completed before returning.
        bool waitUntilIdle {true};
    };

    struct MoveCloseOptions {
        // Wait until the move has completed before returning.
        bool waitUntilIdle {true};
    };

    struct StopOptions {
        // Wait until the gripper has stopped before returning.
        bool waitUntilIdle {true};
    };

    struct CalibrateOptions {
        // Save the calibration results to flash memory so they are retained on power cycle.
        bool saveToFlash {true};
    };

    struct SetHomeDirectionOptions {
        // Save the home direction setting to flash memory so it is retained on power cycle.
        bool saveToFlash {true};
    };

    struct SetAutoHomeOptions {
        // Save the auto home setting to flash memory so it is retained on power cycle.
        bool saveToFlash {true};
    };

    struct SetIoEnabledOptions {
        // Save the IO enabled setting to flash memory so it is retained on power cycle.
        bool saveToFlash {true};
    };

    struct SetIoInputFilterOptions {
        // Save the IO input filter setting to flash memory so it is retained on power cycle.
        bool saveToFlash {true};
    };

    struct SetPresetOptions {
        // The gripping force for the preset as a percentage from 20 to 100.
        int force {100};
        // The maximum speed for the preset as a percentage from 1 to 100.
        int speed {100};
        // Save the preset to flash memory so it is retained on power cycle.
        bool saveToFlash {true};
    };

    struct ActivatePresetOptions {
        // Wait until the move has completed before returning.
        bool waitUntilIdle {true};
    };

    GE1Gripper(int connectionId);

    GE1Gripper(const GE1Gripper& other) = delete;
    GE1Gripper& operator=(const GE1Gripper& other) = delete;

    /**
     * Opens a serial connection to a GE1 series gripper.
     * @param portName The name of the serial port to connect to.
     * @param deviceAddress The address of the gripper to connect to.
     * @param timeout The timeout in milliseconds for any request sent using this connection.
     * @return A GE1Gripper instance representing the connection to the gripper.
     */
    static GE1Gripper openConnection(const std::string& portName, int deviceAddress = DEFAULT_DEVICE_ADDRESS, int timeout = 500);

    /**
     * Opens a serial connection to a GE1 series gripper.
     * @param portName The name of the serial port to connect to.
     * @param options A struct of type OpenConnectionOptions. It has the following members:
     * * `deviceAddress`: The address of the gripper to connect to.
     * * `timeout`: The timeout in milliseconds for any request sent using this connection.
     * @return A GE1Gripper instance representing the connection to the gripper.
     */
    static GE1Gripper openConnection(const std::string& portName, const GE1Gripper::OpenConnectionOptions& options);
    /**
     * Closes the connection to the gripper.
     */
    void close();
    /**
     * Reads a single register value from the gripper.
     * @param registerAddress The address of the register to read.
     * @return The data at the specified register address.
     */
    int readRegister(int registerAddress);
    /**
     * Writes a single register value to the gripper.
     * @param registerAddress The address of the register to write.
     * @param data The data to write to the specified register address.
     */
    void writeRegister(int registerAddress, int data);
    /**
     * Homes gripper by moving it to its homing position.
     * @param waitUntilIdle Wait until homing has completed before returning.
     */
    void home(bool waitUntilIdle = true);

    /**
     * Homes gripper by moving it to its homing position.
     * @param options A struct of type HomeOptions. It has the following members:
     * * `waitUntilIdle`: Wait until homing has completed before returning.
     */
    void home(const GE1Gripper::HomeOptions& options);
    /**
     * Waits until the gripper has stopped moving.
     */
    void waitUntilIdle();
    /**
     * Moves the gripper to a specified position.
     * @param position The target position for the gripper as a percentage, where 0 is closed and 100 is open.
     * @param waitUntilIdle Wait until the move has completed before returning.
     */
    void move(double position, bool waitUntilIdle = true);

    /**
     * Moves the gripper to a specified position.
     * @param position The target position for the gripper as a percentage, where 0 is closed and 100 is open.
     * @param options A struct of type MoveOptions. It has the following members:
     * * `waitUntilIdle`: Wait until the move has completed before returning.
     */
    void move(double position, const GE1Gripper::MoveOptions& options);
    /**
     * Moves the gripper to the open position.
     * @param waitUntilIdle Wait until the move has completed before returning.
     */
    void moveOpen(bool waitUntilIdle = true);

    /**
     * Moves the gripper to the open position.
     * @param options A struct of type MoveOpenOptions. It has the following members:
     * * `waitUntilIdle`: Wait until the move has completed before returning.
     */
    void moveOpen(const GE1Gripper::MoveOpenOptions& options);
    /**
     * Moves the gripper to the closed position.
     * @param waitUntilIdle Wait until the move has completed before returning.
     */
    void moveClose(bool waitUntilIdle = true);

    /**
     * Moves the gripper to the closed position.
     * @param options A struct of type MoveCloseOptions. It has the following members:
     * * `waitUntilIdle`: Wait until the move has completed before returning.
     */
    void moveClose(const GE1Gripper::MoveCloseOptions& options);
    /**
     * Stops the gripper from moving.
     * @param waitUntilIdle Wait until the gripper has stopped before returning.
     */
    void stop(bool waitUntilIdle = true);

    /**
     * Stops the gripper from moving.
     * @param options A struct of type StopOptions. It has the following members:
     * * `waitUntilIdle`: Wait until the gripper has stopped before returning.
     */
    void stop(const GE1Gripper::StopOptions& options);
    /**
     * Sets the gripping force of the gripper.
     * @param force The gripping force as a percentage from 20 to 100.
     */
    void setForce(int force);
    /**
     * Sets the maximum speed of the gripper.
     * @param speed The maximum speed as a percentage from 1 to 100.
     */
    void setSpeed(int speed);
    /**
     * Enables the gripper driver.
     */
    void driverEnable();
    /**
     * Disables the gripper driver.
     */
    void driverDisable();
    /**
     * Performs a calibration of the travel range by moving to the fully open and fully closed positions.
     * @param saveToFlash Save the calibration results to flash memory so they are retained on power cycle.
     */
    void calibrate(bool saveToFlash = true);

    /**
     * Performs a calibration of the travel range by moving to the fully open and fully closed positions.
     * @param options A struct of type CalibrateOptions. It has the following members:
     * * `saveToFlash`: Save the calibration results to flash memory so they are retained on power cycle.
     */
    void calibrate(const GE1Gripper::CalibrateOptions& options);
    /**
     * Gets the current state of the gripper.
     * @return The current state of the gripper.
     */
    Ge1GripperState getState();
    /**
     * Gets the current error of the gripper.
     * @return The current error of the gripper.
     */
    Ge1GripperError getError();
    /**
     * Clears the current error of the gripper.
     */
    void clearError();
    /**
     * Checks if the gripper has been homed.
     * @return True if the gripper is homed, false otherwise.
     */
    bool isHomed();
    /**
     * Gets the current position of the gripper.
     * @return The current position of the gripper as a percentage, where 0 is closed and 100 is open.
     */
    double getPosition();
    /**
     * Gets the current current of the gripper.
     * @return The current current of the gripper in milliamps.
     */
    int getCurrent();
    /**
     * Sets the home direction for the gripper.
     * @param direction The home direction to set.
     * @param saveToFlash Save the home direction setting to flash memory so it is retained on power cycle.
     */
    void setHomeDirection(Ge1GripperDirection direction, bool saveToFlash = true);

    /**
     * Sets the home direction for the gripper.
     * @param direction The home direction to set.
     * @param options A struct of type SetHomeDirectionOptions. It has the following members:
     * * `saveToFlash`: Save the home direction setting to flash memory so it is retained on power cycle.
     */
    void setHomeDirection(Ge1GripperDirection direction, const GE1Gripper::SetHomeDirectionOptions& options);
    /**
     * Enables or disables automatic homing on power up.
     * @param enabled True to enable automatic homing on power up, false to disable.
     * @param saveToFlash Save the auto home setting to flash memory so it is retained on power cycle.
     */
    void setAutoHome(bool enabled, bool saveToFlash = true);

    /**
     * Enables or disables automatic homing on power up.
     * @param enabled True to enable automatic homing on power up, false to disable.
     * @param options A struct of type SetAutoHomeOptions. It has the following members:
     * * `saveToFlash`: Save the auto home setting to flash memory so it is retained on power cycle.
     */
    void setAutoHome(bool enabled, const GE1Gripper::SetAutoHomeOptions& options);
    /**
     * Enables or disables IO control for the gripper.
     * @param enabled True to enable IO control, false to disable.
     * @param saveToFlash Save the IO enabled setting to flash memory so it is retained on power cycle.
     */
    void setIoEnabled(bool enabled, bool saveToFlash = true);

    /**
     * Enables or disables IO control for the gripper.
     * @param enabled True to enable IO control, false to disable.
     * @param options A struct of type SetIoEnabledOptions. It has the following members:
     * * `saveToFlash`: Save the IO enabled setting to flash memory so it is retained on power cycle.
     */
    void setIoEnabled(bool enabled, const GE1Gripper::SetIoEnabledOptions& options);
    /**
     * Sets the debounce filter time for the gripper IO input to suppress noise.
     * @param duration The IO input filter time in milliseconds.
     * @param saveToFlash Save the IO input filter setting to flash memory so it is retained on power cycle.
     */
    void setIoInputFilter(int duration, bool saveToFlash = true);

    /**
     * Sets the debounce filter time for the gripper IO input to suppress noise.
     * @param duration The IO input filter time in milliseconds.
     * @param options A struct of type SetIoInputFilterOptions. It has the following members:
     * * `saveToFlash`: Save the IO input filter setting to flash memory so it is retained on power cycle.
     */
    void setIoInputFilter(int duration, const GE1Gripper::SetIoInputFilterOptions& options);
    /**
     * Saves a position, force, and speed as a preset.
     * @param presetNumber The preset number to save the preset to, from 1 to 4.
     * @param position The target position for the preset as a percentage, where 0 is closed and 100 is open.
     * @param force The gripping force for the preset as a percentage from 20 to 100.
     * @param speed The maximum speed for the preset as a percentage from 1 to 100.
     * @param saveToFlash Save the preset to flash memory so it is retained on power cycle.
     */
    void setPreset(int presetNumber, double position, int force = 100, int speed = 100, bool saveToFlash = true);

    /**
     * Saves a position, force, and speed as a preset.
     * @param presetNumber The preset number to save the preset to, from 1 to 4.
     * @param position The target position for the preset as a percentage, where 0 is closed and 100 is open.
     * @param options A struct of type SetPresetOptions. It has the following members:
     * * `force`: The gripping force for the preset as a percentage from 20 to 100.
     * * `speed`: The maximum speed for the preset as a percentage from 1 to 100.
     * * `saveToFlash`: Save the preset to flash memory so it is retained on power cycle.
     */
    void setPreset(int presetNumber, double position, const GE1Gripper::SetPresetOptions& options);
    /**
     * Activates a preset, causing the gripper to move to the preset position using the preset force and speed.
     * @param presetNumber The preset number to activate, from 1 to 4.
     * @param waitUntilIdle Wait until the move has completed before returning.
     */
    void activatePreset(int presetNumber, bool waitUntilIdle = true);

    /**
     * Activates a preset, causing the gripper to move to the preset position using the preset force and speed.
     * @param presetNumber The preset number to activate, from 1 to 4.
     * @param options A struct of type ActivatePresetOptions. It has the following members:
     * * `waitUntilIdle`: Wait until the move has completed before returning.
     */
    void activatePreset(int presetNumber, const GE1Gripper::ActivatePresetOptions& options);
    /**
     * Gets the preset number currently activated by the gripper IO input.
     * @return The current preset number activated by the gripper IO input.
     */
    int getIoInputPresetNumber();
    /**
     * The identifier for the connection.
     */
    int getConnectionId() const;
protected:
    /**
     * Frees the connection instance.
     * @param connectionId Connection ID to be freed.
     */
    static void free(int connectionId);
    int _connectionId;
public:
    GE1Gripper(): _connectionId(-1) {}
    ~GE1Gripper();
    GE1Gripper(GE1Gripper&& other) noexcept;
    GE1Gripper& operator=(GE1Gripper&& other) noexcept;
};


}  // Namespace product
}  // Namespace motion
}  // Namespace zaber
