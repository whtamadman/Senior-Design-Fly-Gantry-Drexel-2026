// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <initializer_list>
#include <optional>
#include <string>
#include <utility>
#include <vector>
#include "zaber/motion/ascii/connection.h"
#include "zaber/motion/dto/ascii/can_set_state_device_response.h"
#include "zaber/motion/dto/ascii/device_identity.h"
#include "zaber/motion/dto/ascii/response.h"
#include "zaber/motion/dto/ascii/set_state_device_response.h"
#include "zaber/motion/dto/firmware_version.h"
#include "zaber/motion/dto/measurement.h"
#include "zaber/motion/dto/unit_conversion_descriptor.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {

/* Forward Declarations */
class Axis;
class Lockstep;
class DeviceSettings;
class DeviceStorage;
class DeviceIO;
class AllAxes;
class Warnings;
class Oscilloscope;
class Pvt;
class Triggers;
class Streams;


/**
 * Represents the controller part of one device - may be either a standalone controller or an integrated controller.
 */
class Device {
public:
    struct IdentifyOptions {
        // The identification assumes the specified firmware version
        // instead of the version queried from the device.
        // Providing this argument can lead to unexpected compatibility issues.
        std::optional<FirmwareVersion> assumeVersion {};
    };

    struct GenericCommandOptions {
        // Optional axis number to send the command to.
        int axis {0};
        // Controls whether to throw an exception when the device rejects the command.
        bool checkErrors {true};
        // The timeout, in milliseconds, for a device to respond to the command.
        // Overrides the connection default request timeout.
        int timeout {0};
    };

    struct GenericCommandMultiResponseOptions {
        // Optional axis number to send the command to.
        int axis {0};
        // Controls whether to throw an exception when a device rejects the command.
        bool checkErrors {true};
        // The timeout, in milliseconds, for a device to respond to the command.
        // Overrides the connection default request timeout.
        int timeout {0};
    };

    struct GenericCommandNoResponseOptions {
        // Optional axis number to send the command to.
        // Specifying -1 omits the number completely.
        int axis {0};
    };

    struct SetStateOptions {
        // If true, only device scope settings and features will be set.
        bool deviceOnly {false};
    };

    struct CanSetStateOptions {
        // The firmware version of the device to apply the state to.
        // Use this to ensure the state will still be compatible after an update.
        std::optional<FirmwareVersion> firmwareVersion {};
    };

    Device(BaseConnection connection, int deviceAddress);

    Device();

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
     * Sends a generic ASCII command to this device.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param axis Optional axis number to send the command to.
     * @param checkErrors Controls whether to throw an exception when the device rejects the command.
     * @param timeout The timeout, in milliseconds, for a device to respond to the command.
     * Overrides the connection default request timeout.
     * @return A response to the command.
     */
    Response genericCommand(const std::string& command, int axis = 0, bool checkErrors = true, int timeout = 0);

    /**
     * Sends a generic ASCII command to this device.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param options A struct of type GenericCommandOptions. It has the following members:
     * * `axis`: Optional axis number to send the command to.
     * * `checkErrors`: Controls whether to throw an exception when the device rejects the command.
     * * `timeout`: The timeout, in milliseconds, for a device to respond to the command.
     *   Overrides the connection default request timeout.
     * @return A response to the command.
     */
    Response genericCommand(const std::string& command, const Device::GenericCommandOptions& options);
    /**
     * Sends a generic ASCII command to this device and expect multiple responses.
     * Responses are returned in order of arrival.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param axis Optional axis number to send the command to.
     * @param checkErrors Controls whether to throw an exception when a device rejects the command.
     * @param timeout The timeout, in milliseconds, for a device to respond to the command.
     * Overrides the connection default request timeout.
     * @return All responses to the command.
     */
    std::vector<Response> genericCommandMultiResponse(const std::string& command, int axis = 0, bool checkErrors = true, int timeout = 0);

    /**
     * Sends a generic ASCII command to this device and expect multiple responses.
     * Responses are returned in order of arrival.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param options A struct of type GenericCommandMultiResponseOptions. It has the following members:
     * * `axis`: Optional axis number to send the command to.
     * * `checkErrors`: Controls whether to throw an exception when a device rejects the command.
     * * `timeout`: The timeout, in milliseconds, for a device to respond to the command.
     *   Overrides the connection default request timeout.
     * @return All responses to the command.
     */
    std::vector<Response> genericCommandMultiResponse(const std::string& command, const Device::GenericCommandMultiResponseOptions& options);
    /**
     * Sends a generic ASCII command to this device without expecting a response and without adding a message ID
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param axis Optional axis number to send the command to.
     * Specifying -1 omits the number completely.
     */
    void genericCommandNoResponse(const std::string& command, int axis = 0);

    /**
     * Sends a generic ASCII command to this device without expecting a response and without adding a message ID
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param options A struct of type GenericCommandNoResponseOptions. It has the following members:
     * * `axis`: Optional axis number to send the command to.
     *   Specifying -1 omits the number completely.
     */
    void genericCommandNoResponse(const std::string& command, const Device::GenericCommandNoResponseOptions& options);
    /**
     * Gets an Axis class instance which allows you to control a particular axis on this device.
     * Axes are numbered from 1.
     * @param axisNumber Number of axis intended to control.
     * @return Axis instance.
     */
    Axis getAxis(int axisNumber);
    /**
     * Gets a Lockstep class instance which allows you to control a particular lockstep group on the device.
     * Requires at least Firmware 6.15 or 7.11.
     * @param lockstepGroupId The ID of the lockstep group to control. Lockstep group IDs start at one.
     * @return Lockstep instance.
     */
    Lockstep getLockstep(int lockstepGroupId);
    /**
     * Formats parameters into a command and performs unit conversions.
     * Parameters in the command template are denoted by a question mark.
     * Command returned is only valid for this device.
     * Unit conversion is not supported for commands where axes can be remapped, such as stream and PVT commands.
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
     * Sets the user-assigned device label.
     * The label is stored on the controller and recognized by other software.
     * @param label Label to set.
     */
    void setLabel(const std::string& label);
    /**
     * Returns a string that represents the device.
     * @return A string that represents the device.
     */
    std::string toString() const;
    /**
     * Returns a serialization of the current device state that can be saved and reapplied.
     * @return A serialization of the current state of the device.
     */
    std::string getState();
    /**
     * Applies a saved state to this device.
     * @param state The state object to apply to this device.
     * @param deviceOnly If true, only device scope settings and features will be set.
     * @return Reports of any issues that were handled, but caused the state to not be exactly restored.
     */
    SetStateDeviceResponse setState(const std::string& state, bool deviceOnly = false);

    /**
     * Applies a saved state to this device.
     * @param state The state object to apply to this device.
     * @param options A struct of type SetStateOptions. It has the following members:
     * * `deviceOnly`: If true, only device scope settings and features will be set.
     * @return Reports of any issues that were handled, but caused the state to not be exactly restored.
     */
    SetStateDeviceResponse setState(const std::string& state, const Device::SetStateOptions& options);
    /**
     * Checks if a state can be applied to this device.
     * This only covers exceptions that can be determined statically such as mismatches of ID or version,
     * the process of applying the state can still fail when running.
     * @param state The state object to check against.
     * @param firmwareVersion The firmware version of the device to apply the state to.
     * Use this to ensure the state will still be compatible after an update.
     * @return An object listing errors that come up when trying to set the state.
     */
    CanSetStateDeviceResponse canSetState(const std::string& state, const std::optional<FirmwareVersion>& firmwareVersion = {});

    /**
     * Checks if a state can be applied to this device.
     * This only covers exceptions that can be determined statically such as mismatches of ID or version,
     * the process of applying the state can still fail when running.
     * @param state The state object to check against.
     * @param options A struct of type CanSetStateOptions. It has the following members:
     * * `firmwareVersion`: The firmware version of the device to apply the state to.
     *   Use this to ensure the state will still be compatible after an update.
     * @return An object listing errors that come up when trying to set the state.
     */
    CanSetStateDeviceResponse canSetState(const std::string& state, const Device::CanSetStateOptions& options);
    /**
     * Waits for the device to start responding to messages.
     * Useful to call after resetting the device.
     * Throws RequestTimeoutException upon timeout.
     * @param timeout For how long to wait in milliseconds for the device to start responding.
     */
    void waitToRespond(double timeout);
    /**
     * Changes the address of this device.
     * After the address is successfully changed, the existing device class instance no longer represents the device.
     * Instead, use the new device instance returned by this method.
     * @param address The new address to assign to the device.
     * @return New device instance with the new address.
     */
    Device renumber(int address);
    /**
     * Restores most of the settings to their default values.
     * Deletes all triggers, stream and PVT buffers, servo tunings.
     * Deletes all zaber storage keys.
     * Disables locksteps, unparks axes.
     * Preserves storage, communication settings, peripherals (unless hard is specified).
     * The device needs to be identified again after the restore.
     * @param hard If true, completely erases device's memory. The device also resets.
     */
    void restore(bool hard = false);
    /**
     * Connection of this device.
     */
    BaseConnection getConnection() const;
    /**
     * The device address uniquely identifies the device on the connection.
     * It can be configured or automatically assigned by the renumber command.
     */
    int getDeviceAddress() const;
    /**
     * Settings and properties of this device.
     */
    DeviceSettings getSettings() const;
    /**
     * Key-value storage of this device.
     */
    DeviceStorage getStorage() const;
    /**
     * I/O channels of this device.
     */
    DeviceIO getIO() const;
    /**
     * Virtual axis which allows you to target all axes of this device.
     */
    AllAxes getAllAxes() const;
    /**
     * Warnings and faults of this device and all its axes.
     */
    Warnings getWarnings() const;
    /**
     * Identity of the device.
     */
    DeviceIdentity getIdentity() const;
    /**
     * Indicates whether or not the device has been identified.
     */
    bool getIsIdentified() const;
    /**
     * Oscilloscope recording helper for this device.
     * Requires at least Firmware 7.00.
     */
    Oscilloscope getOscilloscope() const;
    /**
     * Unique ID of the device hardware.
     */
    int getDeviceId() const;
    /**
     * Serial number of the device.
     */
    unsigned int getSerialNumber() const;
    /**
     * Name of the product.
     */
    std::string getName() const;
    /**
     * Number of axes this device has.
     */
    int getAxisCount() const;
    /**
     * Version of the firmware.
     */
    FirmwareVersion getFirmwareVersion() const;
    /**
     * The device is an integrated product.
     */
    bool getIsIntegrated() const;
    /**
     * User-assigned label of the device.
     */
    std::string getLabel() const;
    /**
     * Triggers for this device.
     * Requires at least Firmware 7.06.
     */
    Triggers getTriggers() const;
    /**
     * Gets an object that provides access to Streams on this device.
     * Requires at least Firmware 7.05.
     */
    Streams getStreams() const;
    /**
     * Gets an object that provides access to PVT functions of this device.
     * Note that as of ZML v5.0.0, this returns a Pvt object and NOT a PvtSequence object.
     * The PvtSequence can now be obtained from the Pvt object.
     * Requires at least Firmware 7.33.
     */
    Pvt getPvt() const;
protected:
    /**
     * Gets the device name.
     * @return The label.
     */
    std::string retrieveLabel() const;
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


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
