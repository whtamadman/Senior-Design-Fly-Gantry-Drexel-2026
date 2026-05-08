// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <functional>
#include "zaber/motion/gateway/event_handler.h"
#include "zaber/motion/dto/ascii/response.h"
#include "zaber/motion/dto/ascii/alert_event.h"
#include "zaber/motion/dto/ascii/mock_device.h"
#include "zaber/motion/dto/ascii/unknown_response_event.h"
#include "zaber/motion/exceptions/motion_lib_exception.h"

namespace zaber {
namespace motion {
namespace ascii {

/* Forward Declarations */
class Device;
class Transport;

/**
 * Default baud rate for serial connections.
 */
constexpr int DEFAULT_BAUD_RATE = 115200;
/**
 * Commands sent over this port are forwarded to the device chain.
 * The bandwidth may be limited as the commands are forwarded over a serial connection.
 */
constexpr int TCP_PORT_CHAIN = 55550;
/**
 * Local area network share port.
 */
constexpr int NETWORK_SHARE_PORT = 11421;
/**
 * Commands send over this port are processed only by the device
 * and not forwarded to the rest of the chain.
 * Using this port typically makes the communication faster.
 */
constexpr int TCP_PORT_DEVICE_ONLY = 55551;

/**
 * Class representing access to particular connection (serial port, TCP connection).
 * Unlike Connection, BaseConnection instances are copyable.
 * Additionally, BaseConnection instance does not close the connection upon destruction.
 */
class BaseConnection {
public:
    struct GenericCommandOptions {
        // Optional device address to send the command to.
        int device {0};
        // Optional axis number to send the command to.
        int axis {0};
        // Controls whether to throw an exception when the device rejects the command.
        bool checkErrors {true};
        // The timeout, in milliseconds, for a device to respond to the command.
        // Overrides the connection default request timeout.
        int timeout {0};
    };

    struct GenericCommandNoResponseOptions {
        // Optional device address to send the command to.
        // Specifying -1 omits the number completely.
        int device {0};
        // Optional axis number to send the command to.
        // Specifying -1 omits the number completely.
        int axis {0};
    };

    struct GenericCommandMultiResponseOptions {
        // Optional device address to send the command to.
        int device {0};
        // Optional axis number to send the command to.
        int axis {0};
        // Controls whether to throw an exception when a device rejects the command.
        bool checkErrors {true};
        // The timeout, in milliseconds, for a device to respond to the command.
        // Overrides the connection default request timeout.
        int timeout {0};
    };

    struct RenumberDevicesOptions {
        // This is the address that the device closest to the computer is given.
        // Remaining devices are numbered consecutively.
        int firstAddress {1};
    };

    struct DetectDevicesOptions {
        // Determines whether device identification should be performed as well.
        bool identifyDevices {true};
    };

    struct StopAllOptions {
        // Determines whether the function should return immediately
        // or wait until the devices are stopped.
        bool waitUntilIdle {true};
    };

    struct HomeAllOptions {
        // Determines whether the function should return immediately
        // or wait until the devices are homed.
        bool waitUntilIdle {true};
    };

    /**
     * Creates an instance of BaseConnection.
     */
    BaseConnection(int interfaceId);

    /**
     * Sends a generic ASCII command to this connection.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param device Optional device address to send the command to.
     * @param axis Optional axis number to send the command to.
     * @param checkErrors Controls whether to throw an exception when the device rejects the command.
     * @param timeout The timeout, in milliseconds, for a device to respond to the command.
     * Overrides the connection default request timeout.
     * @return A response to the command.
     */
    Response genericCommand(const std::string& command, int device = 0, int axis = 0, bool checkErrors = true, int timeout = 0);

    /**
     * Sends a generic ASCII command to this connection.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param options A struct of type GenericCommandOptions. It has the following members:
     * * `device`: Optional device address to send the command to.
     * * `axis`: Optional axis number to send the command to.
     * * `checkErrors`: Controls whether to throw an exception when the device rejects the command.
     * * `timeout`: The timeout, in milliseconds, for a device to respond to the command.
     *   Overrides the connection default request timeout.
     * @return A response to the command.
     */
    Response genericCommand(const std::string& command, const BaseConnection::GenericCommandOptions& options);
    /**
     * Sends a generic ASCII command to this connection without expecting a response and without adding a message ID.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param device Optional device address to send the command to.
     * Specifying -1 omits the number completely.
     * @param axis Optional axis number to send the command to.
     * Specifying -1 omits the number completely.
     */
    void genericCommandNoResponse(const std::string& command, int device = 0, int axis = 0);

    /**
     * Sends a generic ASCII command to this connection without expecting a response and without adding a message ID.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param options A struct of type GenericCommandNoResponseOptions. It has the following members:
     * * `device`: Optional device address to send the command to.
     *   Specifying -1 omits the number completely.
     * * `axis`: Optional axis number to send the command to.
     *   Specifying -1 omits the number completely.
     */
    void genericCommandNoResponse(const std::string& command, const BaseConnection::GenericCommandNoResponseOptions& options);
    /**
     * Sends a generic ASCII command to this connection and expect multiple responses,
     * either from one device or from many devices.
     * Responses are returned in order of arrival.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param device Optional device address to send the command to.
     * @param axis Optional axis number to send the command to.
     * @param checkErrors Controls whether to throw an exception when a device rejects the command.
     * @param timeout The timeout, in milliseconds, for a device to respond to the command.
     * Overrides the connection default request timeout.
     * @return All responses to the command.
     */
    std::vector<Response> genericCommandMultiResponse(const std::string& command, int device = 0, int axis = 0, bool checkErrors = true, int timeout = 0);

    /**
     * Sends a generic ASCII command to this connection and expect multiple responses,
     * either from one device or from many devices.
     * Responses are returned in order of arrival.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_commands).
     * @param command Command and its parameters.
     * @param options A struct of type GenericCommandMultiResponseOptions. It has the following members:
     * * `device`: Optional device address to send the command to.
     * * `axis`: Optional axis number to send the command to.
     * * `checkErrors`: Controls whether to throw an exception when a device rejects the command.
     * * `timeout`: The timeout, in milliseconds, for a device to respond to the command.
     *   Overrides the connection default request timeout.
     * @return All responses to the command.
     */
    std::vector<Response> genericCommandMultiResponse(const std::string& command, const BaseConnection::GenericCommandMultiResponseOptions& options);
    /**
     * Enables alerts for all devices on the connection.
     * This will change the "comm.alert" setting to 1 on all supported devices.
     */
    void enableAlerts();
    /**
     * Disables alerts for all devices on the connection.
     * This will change the "comm.alert" setting to 0 on all supported devices.
     */
    void disableAlerts();
    /**
     * Resets ASCII protocol message IDs. Only for testing purposes.
     */
    void resetIds();
    /**
     * Gets a Device class instance which allows you to control a particular device on this connection.
     * Devices are numbered from 1.
     * @param deviceAddress Address of device intended to control. Address is configured for each device.
     * @return Device instance.
     */
    Device getDevice(int deviceAddress);
    /**
     * Renumbers devices present on this connection. After renumbering, devices need to be identified again.
     * @param firstAddress This is the address that the device closest to the computer is given.
     * Remaining devices are numbered consecutively.
     * @return Total number of devices that responded to the renumber.
     */
    int renumberDevices(int firstAddress = 1);

    /**
     * Renumbers devices present on this connection. After renumbering, devices need to be identified again.
     * @param options A struct of type RenumberDevicesOptions. It has the following members:
     * * `firstAddress`: This is the address that the device closest to the computer is given.
     *   Remaining devices are numbered consecutively.
     * @return Total number of devices that responded to the renumber.
     */
    int renumberDevices(const BaseConnection::RenumberDevicesOptions& options);
    /**
     * Attempts to detect any devices present on this connection.
     * @param identifyDevices Determines whether device identification should be performed as well.
     * @return Array of detected devices.
     */
    std::vector<Device> detectDevices(bool identifyDevices = true);

    /**
     * Attempts to detect any devices present on this connection.
     * @param options A struct of type DetectDevicesOptions. It has the following members:
     * * `identifyDevices`: Determines whether device identification should be performed as well.
     * @return Array of detected devices.
     */
    std::vector<Device> detectDevices(const BaseConnection::DetectDevicesOptions& options);
    /**
     * Forgets all the information associated with devices on the connection.
     * Useful when devices are removed from the chain indefinitely.
     * @param exceptDevices Addresses of devices that should not be forgotten.
     */
    void forgetDevices(const std::vector<int>& exceptDevices = {});
    /**
     * Stops all of the devices on this connection.
     * @param waitUntilIdle Determines whether the function should return immediately
     * or wait until the devices are stopped.
     * @return The addresses of the devices that were stopped by this command.
     */
    std::vector<int> stopAll(bool waitUntilIdle = true);

    /**
     * Stops all of the devices on this connection.
     * @param options A struct of type StopAllOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether the function should return immediately
     *   or wait until the devices are stopped.
     * @return The addresses of the devices that were stopped by this command.
     */
    std::vector<int> stopAll(const BaseConnection::StopAllOptions& options);
    /**
     * Homes all of the devices on this connection.
     * @param waitUntilIdle Determines whether the function should return immediately
     * or wait until the devices are homed.
     * @return The addresses of the devices that were homed by this command.
     */
    std::vector<int> homeAll(bool waitUntilIdle = true);

    /**
     * Homes all of the devices on this connection.
     * @param options A struct of type HomeAllOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether the function should return immediately
     *   or wait until the devices are homed.
     * @return The addresses of the devices that were homed by this command.
     */
    std::vector<int> homeAll(const BaseConnection::HomeAllOptions& options);
    /**
     * Returns a string that represents the connection.
     * @return A string that represents the connection.
     */
    std::string toString() const;
    /**
     * The interface ID identifies this Connection instance with the underlying library.
     */
    int getInterfaceId() const;
    /**
     * The default timeout, in milliseconds, for a device to respond to a request.
     * Setting the timeout to a too low value may cause request timeout exceptions.
     * The initial value is 1000 (one second).
     */
    int getDefaultRequestTimeout() const;

    /**
     * The default timeout, in milliseconds, for a device to respond to a request.
     * Setting the timeout to a too low value may cause request timeout exceptions.
     * The initial value is 1000 (one second).
     */
    void setDefaultRequestTimeout(int value);
    /**
     * Controls whether outgoing messages contain checksum.
     */
    bool getChecksumEnabled() const;

    /**
     * Controls whether outgoing messages contain checksum.
     */
    void setChecksumEnabled(bool value);
    /**
     * Returns whether the connection is open.
     * Does not guarantee that subsequent requests will succeed.
     */
    bool getIsOpen() const;
protected:
    /**
     * Returns default request timeout.
     * @return Default request timeout.
     */
    int retrieveTimeout() const;
    /**
     * Sets default request timeout.
     * @param timeout Default request timeout.
     */
    void changeTimeout(int timeout) const;
    /**
     * Returns checksum enabled.
     * @return Checksum enabled.
     */
    bool retrieveChecksumEnabled() const;
    /**
     * Sets checksum enabled.
     * @param isEnabled Checksum enabled.
     */
    void changeChecksumEnabled(bool isEnabled) const;
    /**
     * Returns is open.
     * @return Is open.
     */
    bool retrieveIsOpen() const;
    /**
     * Releases native resources of the connection.
     * @param interfaceId The ID of the connection.
     */
    static void free(int interfaceId);
    int _interfaceId;
public:
    BaseConnection(): _interfaceId(-1) {};
    virtual ~BaseConnection() = default;
};


/**
 * Class representing access to particular connection (serial port, TCP connection).
 */
class Connection : public BaseConnection {
public:
    struct OpenSerialPortOptions {
        // Optional baud rate (defaults to 115200).
        int baudRate {DEFAULT_BAUD_RATE};
        // If true will connect to the serial port directly,
        // failing if the connection is already opened by a message router instance.
        bool direct {false};
        // Some operating systems may allow opening a serial port that is not writable.
        // Tests if the serial port is writable, and throws an exception if it is not.
        bool testPort {false};
    };

    struct OpenIotOptions {
        // The token to authenticate with. By default the connection will be unauthenticated.
        std::string token {"unauthenticated"};
        // The name of the connection to open.
        // Can be left empty to default to the only connection present.
        // Otherwise, use serial port name for serial port connection or hostname:port for TCP connection.
        std::optional<std::string> connectionName {};
        // The realm to connect to.
        // Can be left empty for the default account realm.
        std::optional<std::string> realm {};
        // The URL of the API to receive connection info from.
        std::string api {"https://api.zaber.io"};
    };

    Connection(const Connection& other) = delete;
    Connection& operator=(const Connection& other) = delete;

    /**
     * Opens a serial port, if Zaber Launcher controls the port, the port will be opened through Zaber Launcher.
     * Zaber Launcher allows sharing of the port between multiple applications,
     * If port sharing is not desirable, use the `direct` parameter.
     * @param portName Name of the port to open.
     * @param baudRate Optional baud rate (defaults to 115200).
     * @param direct If true will connect to the serial port directly,
     * failing if the connection is already opened by a message router instance.
     * @param testPort Some operating systems may allow opening a serial port that is not writable.
     * Tests if the serial port is writable, and throws an exception if it is not.
     * @return An object representing the port.
     */
    static Connection openSerialPort(const std::string& portName, int baudRate = DEFAULT_BAUD_RATE, bool direct = false, bool testPort = false);

    /**
     * Opens a serial port, if Zaber Launcher controls the port, the port will be opened through Zaber Launcher.
     * Zaber Launcher allows sharing of the port between multiple applications,
     * If port sharing is not desirable, use the `direct` parameter.
     * @param portName Name of the port to open.
     * @param options A struct of type OpenSerialPortOptions. It has the following members:
     * * `baudRate`: Optional baud rate (defaults to 115200).
     * * `direct`: If true will connect to the serial port directly,
     *   failing if the connection is already opened by a message router instance.
     * * `testPort`: Some operating systems may allow opening a serial port that is not writable.
     *   Tests if the serial port is writable, and throws an exception if it is not.
     * @return An object representing the port.
     */
    static Connection openSerialPort(const std::string& portName, const Connection::OpenSerialPortOptions& options);
    /**
     * Opens a TCP connection.
     * @param hostName Hostname or IP address.
     * @param port Optional port number (defaults to 55550).
     * @return An object representing the connection.
     */
    static Connection openTcp(const std::string& hostName, int port = TCP_PORT_CHAIN);
    /**
     * Opens a connection using a custom transport.
     * @param transport The custom connection transport.
     * @return An object representing the connection.
     */
    static Connection openCustom(const Transport& transport);
    /**
     * Opens a secured connection to a cloud connected device chain.
     * Use this method to connect to devices on your account.
     * @param cloudId The cloud ID to connect to.
     * @param token The token to authenticate with. By default the connection will be unauthenticated.
     * @param connectionName The name of the connection to open.
     * Can be left empty to default to the only connection present.
     * Otherwise, use serial port name for serial port connection or hostname:port for TCP connection.
     * @param realm The realm to connect to.
     * Can be left empty for the default account realm.
     * @param api The URL of the API to receive connection info from.
     * @return An object representing the connection.
     */
    static Connection openIot(const std::string& cloudId, const std::string& token = "unauthenticated", const std::optional<std::string>& connectionName = {}, const std::optional<std::string>& realm = {}, const std::string& api = "https://api.zaber.io");

    /**
     * Opens a secured connection to a cloud connected device chain.
     * Use this method to connect to devices on your account.
     * @param cloudId The cloud ID to connect to.
     * @param options A struct of type OpenIotOptions. It has the following members:
     * * `token`: The token to authenticate with. By default the connection will be unauthenticated.
     * * `connectionName`: The name of the connection to open.
     *   Can be left empty to default to the only connection present.
     *   Otherwise, use serial port name for serial port connection or hostname:port for TCP connection.
     * * `realm`: The realm to connect to.
     *   Can be left empty for the default account realm.
     * * `api`: The URL of the API to receive connection info from.
     * @return An object representing the connection.
     */
    static Connection openIot(const std::string& cloudId, const Connection::OpenIotOptions& options);
    /**
     * Opens a connection to Zaber Launcher in your Local Area Network.
     * The connection is not secured.
     * @param hostName Hostname or IP address.
     * @param port Port number.
     * @param connectionName The name of the connection to open.
     * Can be left empty to default to the only connection present.
     * Otherwise, use serial port name for serial port connection or hostname:port for TCP connection.
     * @return An object representing the connection.
     */
    static Connection openNetworkShare(const std::string& hostName, int port = NETWORK_SHARE_PORT, const std::optional<std::string>& connectionName = {});
    /**
     * Opens a mock connection with mock devices for testing purposes.
     * The mock connection cannot be used for communication with mock devices.
     * @param devices List of mock devices.
     * @return An object representing the mock connection.
     */
    static Connection openMock(const std::vector<MockDevice>& devices);
    /**
     * Reopens the connection.
     * Throws an exception if the connection is already open.
     */
    void reopen();
    /**
     * Close the connection.
     */
    void close();
protected:

public:
    Connection() = default;
    Connection(int interfaceId);
    ~Connection();

    Connection(Connection&& other) noexcept;
    Connection& operator=(Connection&& other) noexcept;

    void setUnknownResponseCallback(std::function<void(const UnknownResponseEvent&)> callback);
    void setAlertCallback(std::function<void(const AlertEvent&)> callback);
    void setDisconnectedCallback(std::function<void(const std::shared_ptr<exceptions::MotionLibException>&)> callback);

private:
    std::shared_ptr<EventHandler<UnknownResponseEvent>> _unknownResponseHandler = nullptr;
    std::shared_ptr<EventHandler<AlertEvent>> _alertEventHandler = nullptr;
    std::shared_ptr<EventHandler<std::shared_ptr<exceptions::MotionLibException>>> _disconnectedHandler = nullptr;

    void resetEventHandlers();
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
