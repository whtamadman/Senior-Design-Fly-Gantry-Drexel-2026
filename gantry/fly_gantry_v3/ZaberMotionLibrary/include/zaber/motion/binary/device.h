// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>
#include "zaber/motion/binary/connection.h"
#include "zaber/motion/dto/binary/binary_settings.h"
#include "zaber/motion/dto/binary/command_code.h"
#include "zaber/motion/dto/binary/device_identity.h"
#include "zaber/motion/dto/binary/device_type.h"
#include "zaber/motion/dto/binary/message.h"
#include "zaber/motion/dto/firmware_version.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace binary {

/* Forward Declarations */
class DeviceSettings;

/**
 * Default timeout for move commands in seconds.
 */
constexpr double DEFAULT_MOVEMENT_TIMEOUT = 60;


/**
 * Represents a device using the binary protocol.
 */
class Device {
public:
    struct GenericCommandOptions {
        // Number of seconds to wait for a response from the device. 0 or negative defaults to 0.5s.
        double timeout {0.0};
        // Controls whether to throw an exception when the device rejects the command.
        bool checkErrors {true};
    };

    struct GenericCommandWithUnitsOptions {
        // Number of seconds to wait for a response from the device. 0 or negative defaults to 0.5s.
        double timeout {0.0};
    };

    struct HomeOptions {
        // Unit to convert returned position to.
        Units unit {Units::NATIVE};
        // Number of seconds to wait for response from the device chain (defaults to 60s).
        double timeout {DEFAULT_MOVEMENT_TIMEOUT};
    };

    struct StopOptions {
        // Unit to convert returned position to.
        Units unit {Units::NATIVE};
        // Number of seconds to wait for response from the device chain (defaults to 60s).
        double timeout {DEFAULT_MOVEMENT_TIMEOUT};
    };

    struct MoveAbsoluteOptions {
        // Number of seconds to wait for response from the device chain (defaults to 60s).
        double timeout {DEFAULT_MOVEMENT_TIMEOUT};
    };

    struct MoveRelativeOptions {
        // Number of seconds to wait for response from the device chain (defaults to 60s).
        double timeout {DEFAULT_MOVEMENT_TIMEOUT};
    };

    struct IdentifyOptions {
        // The identification assumes the specified firmware version
        // instead of the version queried from the device.
        // Providing this argument can lead to unexpected compatibility issues.
        std::optional<FirmwareVersion> assumeVersion {};
    };

    Device(BaseConnection connection, int deviceAddress);

    Device();

    /**
     * Sends a generic Binary command to this device.
     * For more information please refer to the
     * [Binary Protocol Manual](https://www.zaber.com/protocol-manual?protocol=Binary#topic_quick_command_reference).
     * @param command Command to send.
     * @param data Optional data argument to the command. Defaults to zero.
     * @param timeout Number of seconds to wait for a response from the device. 0 or negative defaults to 0.5s.
     * @param checkErrors Controls whether to throw an exception when the device rejects the command.
     * @return A response to the command.
     */
    Message genericCommand(CommandCode command, int data = 0, double timeout = 0.0, bool checkErrors = true);

    /**
     * Sends a generic Binary command to this device.
     * For more information please refer to the
     * [Binary Protocol Manual](https://www.zaber.com/protocol-manual?protocol=Binary#topic_quick_command_reference).
     * @param command Command to send.
     * @param data Optional data argument to the command. Defaults to zero.
     * @param options A struct of type GenericCommandOptions. It has the following members:
     * * `timeout`: Number of seconds to wait for a response from the device. 0 or negative defaults to 0.5s.
     * * `checkErrors`: Controls whether to throw an exception when the device rejects the command.
     * @return A response to the command.
     */
    Message genericCommand(CommandCode command, int data, const Device::GenericCommandOptions& options);
    /**
     * Sends a generic Binary command to this device without expecting a response.
     * For more information please refer to the
     * [Binary Protocol Manual](https://www.zaber.com/protocol-manual?protocol=Binary#topic_quick_command_reference).
     * @param command Command to send.
     * @param data Optional data argument to the command. Defaults to zero.
     */
    void genericCommandNoResponse(CommandCode command, int data = 0);
    /**
     * Sends a generic Binary command to this device with unit conversions for both sent data and retrieved data.
     * @param command Command to send.
     * @param data Data argument to the command. Defaults to zero.
     * @param fromUnit Unit to convert sent data from.
     * @param toUnit Unit to convert retrieved data to.
     * @param timeout Number of seconds to wait for a response from the device. 0 or negative defaults to 0.5s.
     * @return Data that has been converted to the provided unit.
     */
    double genericCommandWithUnits(CommandCode command, double data = 0, Units fromUnit = Units::NATIVE, Units toUnit = Units::NATIVE, double timeout = 0.0);

    /**
     * Sends a generic Binary command to this device with unit conversions for both sent data and retrieved data.
     * @param command Command to send.
     * @param data Data argument to the command. Defaults to zero.
     * @param fromUnit Unit to convert sent data from.
     * @param toUnit Unit to convert retrieved data to.
     * @param options A struct of type GenericCommandWithUnitsOptions. It has the following members:
     * * `timeout`: Number of seconds to wait for a response from the device. 0 or negative defaults to 0.5s.
     * @return Data that has been converted to the provided unit.
     */
    double genericCommandWithUnits(CommandCode command, double data, Units fromUnit, Units toUnit, const Device::GenericCommandWithUnitsOptions& options);
    /**
     * Homes device. Device returns to its homing position.
     * @param unit Unit to convert returned position to.
     * @param timeout Number of seconds to wait for response from the device chain (defaults to 60s).
     * @return Current position that has been converted to the provided unit.
     */
    double home(Units unit = Units::NATIVE, double timeout = DEFAULT_MOVEMENT_TIMEOUT);

    /**
     * Homes device. Device returns to its homing position.
     * @param options A struct of type HomeOptions. It has the following members:
     * * `unit`: Unit to convert returned position to.
     * * `timeout`: Number of seconds to wait for response from the device chain (defaults to 60s).
     * @return Current position that has been converted to the provided unit.
     */
    double home(const Device::HomeOptions& options);
    /**
     * Stops ongoing device movement. Decelerates until zero speed.
     * @param unit Unit to convert returned position to.
     * @param timeout Number of seconds to wait for response from the device chain (defaults to 60s).
     * @return Current position that has been converted to the provided unit.
     */
    double stop(Units unit = Units::NATIVE, double timeout = DEFAULT_MOVEMENT_TIMEOUT);

    /**
     * Stops ongoing device movement. Decelerates until zero speed.
     * @param options A struct of type StopOptions. It has the following members:
     * * `unit`: Unit to convert returned position to.
     * * `timeout`: Number of seconds to wait for response from the device chain (defaults to 60s).
     * @return Current position that has been converted to the provided unit.
     */
    double stop(const Device::StopOptions& options);
    /**
     * Move device to absolute position.
     * @param position Absolute position.
     * @param unit Unit for the provided position as well as position returned by the device.
     * @param timeout Number of seconds to wait for response from the device chain (defaults to 60s).
     * @return Current position that has been converted to the provided unit.
     */
    double moveAbsolute(double position, Units unit = Units::NATIVE, double timeout = DEFAULT_MOVEMENT_TIMEOUT);

    /**
     * Move device to absolute position.
     * @param position Absolute position.
     * @param unit Unit for the provided position as well as position returned by the device.
     * @param options A struct of type MoveAbsoluteOptions. It has the following members:
     * * `timeout`: Number of seconds to wait for response from the device chain (defaults to 60s).
     * @return Current position that has been converted to the provided unit.
     */
    double moveAbsolute(double position, Units unit, const Device::MoveAbsoluteOptions& options);
    /**
     * Move device to position relative to current position.
     * @param position Relative position.
     * @param unit Unit for the provided position as well as position returned by the device.
     * @param timeout Number of seconds to wait for response from the device chain (defaults to 60s).
     * @return Current position that has been converted to the provided unit.
     */
    double moveRelative(double position, Units unit = Units::NATIVE, double timeout = DEFAULT_MOVEMENT_TIMEOUT);

    /**
     * Move device to position relative to current position.
     * @param position Relative position.
     * @param unit Unit for the provided position as well as position returned by the device.
     * @param options A struct of type MoveRelativeOptions. It has the following members:
     * * `timeout`: Number of seconds to wait for response from the device chain (defaults to 60s).
     * @return Current position that has been converted to the provided unit.
     */
    double moveRelative(double position, Units unit, const Device::MoveRelativeOptions& options);
    /**
     * Begins to move device at specified speed.
     * @param velocity Movement velocity.
     * @param unit Unit to convert returned velocity to.
     * @return Device velocity that has been converted to the provided unit.
     */
    double moveVelocity(double velocity, Units unit = Units::NATIVE);
    /**
     * Waits until device stops moving.
     */
    void waitUntilIdle();
    /**
     * Check whether the device is moving.
     * @return True if the device is currently executing a motion command.
     */
    bool isBusy();
    /**
     * Queries the device and the database, gathering information about the product.
     * Without this information features such as unit conversions will not work.
     * Usually, called automatically by detect devices method.
     * @param assumeVersion The identification assumes the specified firmware version
     * instead of the version queried from the device.
     * Providing this argument can lead to unexpected compatibility issues.
     * @return Device identification data.
     */
    DeviceIdentity identify(const std::optional<FirmwareVersion>& assumeVersion = {});

    /**
     * Queries the device and the database, gathering information about the product.
     * Without this information features such as unit conversions will not work.
     * Usually, called automatically by detect devices method.
     * @param options A struct of type IdentifyOptions. It has the following members:
     * * `assumeVersion`: The identification assumes the specified firmware version
     *   instead of the version queried from the device.
     *   Providing this argument can lead to unexpected compatibility issues.
     * @return Device identification data.
     */
    DeviceIdentity identify(const Device::IdentifyOptions& options);
    /**
     * Parks the axis.
     * Motor drivers remain enabled and hold current continues to be applied until the device is powered off.
     * It can later be unparked and moved without first having to home it.
     * Requires at least Firmware 6.06.
     */
    void park();
    /**
     * Unparks axis. Axis will now be able to move.
     * Requires at least Firmware 6.06.
     */
    void unpark();
    /**
     * Returns bool indicating whether the axis is parked or not.
     * Requires at least Firmware 6.06.
     * @return True if the axis is currently parked. False otherwise.
     */
    bool isParked();
    /**
     * Returns current device position.
     * @param unit Units of position.
     * @return Axis position.
     */
    double getPosition(Units unit = Units::NATIVE);
    /**
     * Returns a string that represents the device.
     * @return A string that represents the device.
     */
    std::string toString() const;
    /**
     * Connection of this device.
     */
    BaseConnection getConnection() const;
    /**
     * Settings and properties of this axis.
     */
    DeviceSettings getSettings() const;
    /**
     * The device address uniquely identifies the device on the connection.
     * It can be configured or automatically assigned by the renumber command.
     */
    int getDeviceAddress() const;
    /**
     * Identity of the device.
     */
    DeviceIdentity getIdentity() const;
    /**
     * Indicates whether or not the device has been identified.
     */
    bool getIsIdentified() const;
    /**
     * Unique ID of the device hardware.
     */
    int getDeviceId() const;
    /**
     * Serial number of the device.
     * Requires at least Firmware 6.15 for devices or 6.24 for peripherals.
     */
    unsigned int getSerialNumber() const;
    /**
     * Name of the product.
     */
    std::string getName() const;
    /**
     * Version of the firmware.
     */
    FirmwareVersion getFirmwareVersion() const;
    /**
     * Indicates whether the device is a peripheral or part of an integrated device.
     */
    bool getIsPeripheral() const;
    /**
     * Unique ID of the peripheral hardware.
     */
    int getPeripheralId() const;
    /**
     * Name of the peripheral hardware.
     */
    std::string getPeripheralName() const;
    /**
     * Determines the type of an device and units it accepts.
     */
    DeviceType getDeviceType() const;
protected:
    /**
     * Returns identity.
     * @return Device identity.
     */
    DeviceIdentity retrieveIdentity() const;
    /**
     * Returns whether or not the device have been identified.
     * @return True if the device has already been identified. False otherwise.
     */
    bool retrieveIsIdentified() const;
    BaseConnection _connection;
    int _deviceAddress;
};


}  // Namespace binary
}  // Namespace motion
}  // Namespace zaber
