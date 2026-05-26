// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "zaber/motion/dto/binary/command_code.h"
#include "zaber/motion/dto/binary/message.h"
#include "zaber/motion/dto/binary/reply_only_event.h"
#include "zaber/motion/dto/binary/unknown_response_event.h"
#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/gateway/event_handler.h"

namespace zaber {
namespace motion {
namespace binary {

/* Forward Declarations */
class Device;

/**
 * Default baud rate for serial connections.
 */
constexpr int DEFAULT_BAUD_RATE = 9600;
/**
 * Commands sent over this port are forwarded to the device chain.
 * The bandwidth may be limited as the commands are forwarded over a serial connection.
 */
constexpr int TCP_PORT_CHAIN = 55550;
/**
 * Commands send over this port are processed only by the device
 * and not forwarded to the rest of the chain.
 * Using this port typically makes the communication faster.
 */
constexpr int TCP_PORT_DEVICE_ONLY = 55551;

/**
 * Class representing access to particular connection (serial port, TCP connection) using the legacy Binary protocol.
 * Unlike Connection, BaseConnection instances are copyable.
 * Additionally, BaseConnection instance does not close the connection upon destruction.
 */
class BaseConnection {
public:
    struct GenericCommandOptions {
        // Number of seconds to wait for a response from the device. 0 or negative defaults to 0.5s.
        double timeout {0.0};
        // Controls whether to throw an exception when the device rejects the command.
        bool checkErrors {true};
    };

    struct GenericCommandMultiResponseOptions {
        // Number of seconds to wait for all responses from the device chain. 0 or negative defaults to 0.5s.
        double timeout {0.0};
        // Controls whether to throw an exception when any device rejects the command.
        bool checkErrors {true};
    };

    struct DetectDevicesOptions {
        // Determines whether device identification should be performed as well.
        bool identifyDevices {true};
    };

    /**
     * Creates an instance of BaseConnection.
     */
    BaseConnection(int interfaceId);

    /**
     * Sends a generic Binary command to this connection.
     * For more information please refer to the
     * [Binary Protocol Manual](https://www.zaber.com/protocol-manual?protocol=Binary#topic_quick_command_reference).
     * @param device Device address to send the command to. Use zero for broadcast.
     * @param command Command to send.
     * @param data Optional data argument to the command. Defaults to zero.
     * @param timeout Number of seconds to wait for a response from the device. 0 or negative defaults to 0.5s.
     * @param checkErrors Controls whether to throw an exception when the device rejects the command.
     * @return A response to the command.
     */
    Message genericCommand(int device, CommandCode command, int data = 0, double timeout = 0.0, bool checkErrors = true);

    /**
     * Sends a generic Binary command to this connection.
     * For more information please refer to the
     * [Binary Protocol Manual](https://www.zaber.com/protocol-manual?protocol=Binary#topic_quick_command_reference).
     * @param device Device address to send the command to. Use zero for broadcast.
     * @param command Command to send.
     * @param data Optional data argument to the command. Defaults to zero.
     * @param options A struct of type GenericCommandOptions. It has the following members:
     * * `timeout`: Number of seconds to wait for a response from the device. 0 or negative defaults to 0.5s.
     * * `checkErrors`: Controls whether to throw an exception when the device rejects the command.
     * @return A response to the command.
     */
    Message genericCommand(int device, CommandCode command, int data, const BaseConnection::GenericCommandOptions& options);
    /**
     * Sends a generic Binary command to this connection without expecting a response.
     * For more information please refer to the
     * [Binary Protocol Manual](https://www.zaber.com/protocol-manual?protocol=Binary#topic_quick_command_reference).
     * @param device Device address to send the command to. Use zero for broadcast.
     * @param command Command to send.
     * @param data Optional data argument to the command. Defaults to zero.
     */
    void genericCommandNoResponse(int device, CommandCode command, int data = 0);
    /**
     * Sends a generic Binary command to this connection and expects responses from one or more devices.
     * Responses are returned in order of arrival.
     * For more information please refer to the
     * [Binary Protocol Manual](https://www.zaber.com/protocol-manual?protocol=Binary#topic_quick_command_reference).
     * @param command Command to send.
     * @param data Optional data argument to the command. Defaults to zero.
     * @param timeout Number of seconds to wait for all responses from the device chain. 0 or negative defaults to 0.5s.
     * @param checkErrors Controls whether to throw an exception when any device rejects the command.
     * @return All responses to the command.
     */
    std::vector<Message> genericCommandMultiResponse(CommandCode command, int data = 0, double timeout = 0.0, bool checkErrors = true);

    /**
     * Sends a generic Binary command to this connection and expects responses from one or more devices.
     * Responses are returned in order of arrival.
     * For more information please refer to the
     * [Binary Protocol Manual](https://www.zaber.com/protocol-manual?protocol=Binary#topic_quick_command_reference).
     * @param command Command to send.
     * @param data Optional data argument to the command. Defaults to zero.
     * @param options A struct of type GenericCommandMultiResponseOptions. It has the following members:
     * * `timeout`: Number of seconds to wait for all responses from the device chain. 0 or negative defaults to 0.5s.
     * * `checkErrors`: Controls whether to throw an exception when any device rejects the command.
     * @return All responses to the command.
     */
    std::vector<Message> genericCommandMultiResponse(CommandCode command, int data, const BaseConnection::GenericCommandMultiResponseOptions& options);
    /**
     * Renumbers devices present on this connection. After renumbering, you must identify devices again.
     * @return Total number of devices that responded to the renumber.
     */
    int renumberDevices();
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
     * Gets a Device class instance which allows you to control a particular device on this connection.
     * Devices are numbered from 1.
     * @param deviceAddress Address of device intended to control. Address is configured for each device.
     * @return Device instance.
     */
    Device getDevice(int deviceAddress);
    /**
     * Returns a string that represents the connection.
     * @return A string that represents the connection.
     */
    std::string toString() const;
    /**
     * The interface ID identifies thisConnection instance with the underlying library.
     */
    int getInterfaceId() const;
    /**
     * Returns whether the connection is open.
     * Does not guarantee that the subsequent requests will succeed.
     */
    bool getIsOpen() const;
protected:
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
 * Class representing access to particular connection (serial port, TCP connection) using the legacy Binary protocol.
 */
class Connection : public BaseConnection {
public:
    struct OpenSerialPortOptions {
        // Optional baud rate (defaults to 9600).
        int baudRate {DEFAULT_BAUD_RATE};
        // Enable use of message IDs (defaults to disabled).
        // All your devices must be pre-configured to match.
        bool useMessageIds {false};
    };

    struct OpenTcpOptions {
        // Optional port number (defaults to 55550).
        int port {TCP_PORT_CHAIN};
        // Enable use of message IDs (defaults to disabled).
        // All your devices must be pre-configured to match.
        bool useMessageIds {false};
    };

    Connection(const Connection& other) = delete;
    Connection& operator=(const Connection& other) = delete;

    /**
     * Opens a serial port.
     * @param portName Name of the port to open.
     * @param baudRate Optional baud rate (defaults to 9600).
     * @param useMessageIds Enable use of message IDs (defaults to disabled).
     * All your devices must be pre-configured to match.
     * @return An object representing the port.
     */
    static Connection openSerialPort(const std::string& portName, int baudRate = DEFAULT_BAUD_RATE, bool useMessageIds = false);

    /**
     * Opens a serial port.
     * @param portName Name of the port to open.
     * @param options A struct of type OpenSerialPortOptions. It has the following members:
     * * `baudRate`: Optional baud rate (defaults to 9600).
     * * `useMessageIds`: Enable use of message IDs (defaults to disabled).
     *   All your devices must be pre-configured to match.
     * @return An object representing the port.
     */
    static Connection openSerialPort(const std::string& portName, const Connection::OpenSerialPortOptions& options);
    /**
     * Opens a TCP connection.
     * @param hostName Hostname or IP address.
     * @param port Optional port number (defaults to 55550).
     * @param useMessageIds Enable use of message IDs (defaults to disabled).
     * All your devices must be pre-configured to match.
     * @return An object representing the connection.
     */
    static Connection openTcp(const std::string& hostName, int port = TCP_PORT_CHAIN, bool useMessageIds = false);

    /**
     * Opens a TCP connection.
     * @param hostName Hostname or IP address.
     * @param options A struct of type OpenTcpOptions. It has the following members:
     * * `port`: Optional port number (defaults to 55550).
     * * `useMessageIds`: Enable use of message IDs (defaults to disabled).
     *   All your devices must be pre-configured to match.
     * @return An object representing the connection.
     */
    static Connection openTcp(const std::string& hostName, const Connection::OpenTcpOptions& options);
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
    void setReplyOnlyCallback(std::function<void(const ReplyOnlyEvent&)> callback);
    void setDisconnectedCallback(std::function<void(const  std::shared_ptr<exceptions::MotionLibException>&)> callback);

private:
    std::shared_ptr<EventHandler<UnknownResponseEvent>> _unknownResponseHandler;
    std::shared_ptr<EventHandler<ReplyOnlyEvent>> _replyOnlyEventHandler;
    std::shared_ptr<EventHandler<std::shared_ptr<exceptions::MotionLibException>>> _disconnectedHandler;

    void resetEventHandlers();
};

}  // Namespace binary
}  // Namespace motion
}  // Namespace zaber
