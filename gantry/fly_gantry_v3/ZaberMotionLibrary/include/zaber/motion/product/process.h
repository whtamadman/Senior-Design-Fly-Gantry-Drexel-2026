// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <initializer_list>
#include <string>
#include <utility>
#include <vector>
#include "zaber/motion/ascii/axis.h"
#include "zaber/motion/ascii/axis_settings.h"
#include "zaber/motion/ascii/axis_storage.h"
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/ascii/warnings.h"
#include "zaber/motion/dto/ascii/response.h"
#include "zaber/motion/dto/measurement.h"
#include "zaber/motion/dto/product/process_controller_mode.h"
#include "zaber/motion/dto/product/process_controller_source.h"
#include "zaber/motion/product/process_controller.h"
#include "zaber/motion/units.h"

namespace zaber { namespace motion { namespace ascii {
    class Axis;
    class AxisSettings;
    class AxisStorage;
    class Warnings;
}}}

namespace zaber {
namespace motion {
namespace product {


/**
 * Use to drive voltage for a process such as a heater, valve, Peltier device, etc.
 * Requires at least Firmware 7.35.
 */
class Process {
    using Axis = zaber::motion::ascii::Axis;
    using AxisSettings = zaber::motion::ascii::AxisSettings;
    using AxisStorage = zaber::motion::ascii::AxisStorage;
    using Response = zaber::motion::ascii::Response;
    using SetStateAxisResponse = zaber::motion::ascii::SetStateAxisResponse;
    using Warnings = zaber::motion::ascii::Warnings;

public:
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

    Process(ProcessController controller, int processNumber);

    /**
     * Sets the enabled state of the driver.
     * @param enabled If true (default) enables drive. If false disables.
     */
    void enable(bool enabled = true);
    /**
     * Turns this process on. In manual mode, this supplies voltage; in controlled mode, it starts the control loop.
     * @param duration How long to leave the process on.
     * @param unit Units of time.
     */
    void on(double duration = 0, Units unit = Units::NATIVE);
    /**
     * Turns this process off.
     */
    void off();
    /**
     * Sets the control mode of this process.
     * @param mode Mode to set this process to.
     */
    void setMode(ProcessControllerMode mode);
    /**
     * Gets the control mode of this process.
     * @return Control mode.
     */
    ProcessControllerMode getMode();
    /**
     * Gets the source used to control this process.
     * @return The source providing feedback for this process.
     */
    ProcessControllerSource getSource();
    /**
     * Sets the source used to control this process.
     * @param source Sets the source that should provide feedback for this process.
     */
    void setSource(const ProcessControllerSource& source);
    /**
     * Gets the current value of the source used to control this process.
     * @return The current value of this process's controlling source.
     */
    Measurement getInput();
    /**
     * Creates an H-bridge between this process and its neighbor. This method is only callable on axis 1 and 3.
     */
    void bridge();
    /**
     * Breaks the H-bridge between this process and its neighbor, allowing them to be independently controlled.
     * This method is only callable on axis 1 and 3.
     */
    void unbridge();
    /**
     * Detects if the given process is in bridging mode.
     * @return Whether this process is bridged with its neighbor.
     */
    bool isBridge();
    /**
     * Sends a generic ASCII command to this process' underlying axis.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param checkErrors Controls whether to throw an exception when the device rejects the command.
     * @param timeout The timeout, in milliseconds, for a device to respond to the command.
     * Overrides the connection default request timeout.
     * @return A response to the command.
     */
    Response genericCommand(const std::string& command, bool checkErrors = true, int timeout = 0);

    /**
     * Sends a generic ASCII command to this process' underlying axis.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param options A struct of type GenericCommandOptions. It has the following members:
     * * `checkErrors`: Controls whether to throw an exception when the device rejects the command.
     * * `timeout`: The timeout, in milliseconds, for a device to respond to the command.
     *   Overrides the connection default request timeout.
     * @return A response to the command.
     */
    Response genericCommand(const std::string& command, const Process::GenericCommandOptions& options);
    /**
     * Sends a generic ASCII command to this process and expect multiple responses.
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
     * Sends a generic ASCII command to this process and expect multiple responses.
     * Responses are returned in order of arrival.
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param options A struct of type GenericCommandMultiResponseOptions. It has the following members:
     * * `checkErrors`: Controls whether to throw an exception when a device rejects the command.
     * * `timeout`: The timeout, in milliseconds, for a device to respond to the command.
     *   Overrides the connection default request timeout.
     * @return All responses to the command.
     */
    std::vector<Response> genericCommandMultiResponse(const std::string& command, const Process::GenericCommandMultiResponseOptions& options);
    /**
     * Sends a generic ASCII command to this process without expecting a response and without adding a message ID
     * For more information refer to: [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     */
    void genericCommandNoResponse(const std::string& command);
    /**
     * Returns a serialization of the current process state that can be saved and reapplied.
     * @return A serialization of the current state of the process.
     */
    std::string getState();
    /**
     * Applies a saved state to this process.
     * @param state The state object to apply to this process.
     * @return Reports of any issues that were handled, but caused the state to not be exactly restored.
     */
    SetStateAxisResponse setState(const std::string& state);
    /**
     * Checks if a state can be applied to this process.
     * This only covers exceptions that can be determined statically such as mismatches of ID or version,
     * the process of applying the state can still fail when running.
     * @param state The state object to check against.
     * @param firmwareVersion The firmware version of the device to apply the state to.
     * Use this to ensure the state will still be compatible after an update.
     * @return An explanation of why this state cannot be set to this process.
     */
    std::optional<std::string> canSetState(const std::string& state, const std::optional<FirmwareVersion>& firmwareVersion = {});

    /**
     * Checks if a state can be applied to this process.
     * This only covers exceptions that can be determined statically such as mismatches of ID or version,
     * the process of applying the state can still fail when running.
     * @param state The state object to check against.
     * @param options A struct of type CanSetStateOptions. It has the following members:
     * * `firmwareVersion`: The firmware version of the device to apply the state to.
     *   Use this to ensure the state will still be compatible after an update.
     * @return An explanation of why this state cannot be set to this process.
     */
    std::optional<std::string> canSetState(const std::string& state, const Process::CanSetStateOptions& options);
    /**
     * Returns a string that represents the process.
     * @return A string that represents the process.
     */
    std::string toString() const;
    /**
     * Controller for this process.
     */
    ProcessController getController() const;
    /**
     * The process number identifies the process on the controller.
     */
    int getProcessNumber() const;
    /**
     * Settings and properties of this process.
     */
    AxisSettings getSettings() const;
    /**
     * Key-value storage of this process.
     */
    AxisStorage getStorage() const;
    /**
     * Warnings and faults of this process.
     */
    Warnings getWarnings() const;
protected:
    Axis getAxis() const;
    ProcessController _controller;
    int _processNumber;
    Axis _axis;
    AxisSettings _settings;
    AxisStorage _storage;
    Warnings _warnings;
};


}  // Namespace product
}  // Namespace motion
}  // Namespace zaber
