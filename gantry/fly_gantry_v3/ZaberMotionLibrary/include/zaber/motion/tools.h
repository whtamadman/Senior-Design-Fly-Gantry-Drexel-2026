// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>
#include <vector>
#include "zaber/motion/dto/device_discovery_result.h"

namespace zaber {
namespace motion {


/**
 * Class providing various utility functions.
 */
class Tools {
public:
    struct DiscoverTCPDevicesOptions {
        // Optional time in ms to wait for mDNS discovery response (defaults to 3000).
        int duration {3000};
        // Specify which network interface to use by IP address.
        // If no value or an empty string is provided, mDNS query is sent to all compatible network interfaces.
        std::optional<std::string> interfaceIpAddress {};
    };

    Tools() = delete;

    /**
     * Lists all serial ports on the computer.
     * @return Array of serial port names.
     */
    static std::vector<std::string> listSerialPorts();
    /**
     * Returns path of message router named pipe on Windows
     * or file path of unix domain socket on UNIX.
     * @return Path of message router's named pipe or unix domain socket.
     */
    static std::string getMessageRouterPipePath();
    /**
     * Returns the path for communicating with a local device database service.
     * This will be a named pipe on Windows and the file path of a unix domain socket on UNIX.
     * @return Path of database service's named pipe or unix domain socket.
     */
    static std::string getDbServicePipePath();
    /**
     * Discover Zaber devices shared over local network over TCP/IP.
     * @param duration Optional time in ms to wait for mDNS discovery response (defaults to 3000).
     * @param interfaceIpAddress Specify which network interface to use by IP address.
     * If no value or an empty string is provided, mDNS query is sent to all compatible network interfaces.
     * @return Array of discovered devices.
     */
    static std::vector<DeviceDiscoveryResult> discoverTcpDevices(int duration = 3000, const std::optional<std::string>& interfaceIpAddress = {});

    /**
     * Discover Zaber devices shared over local network over TCP/IP.
     * @param options A struct of type DiscoverTCPDevicesOptions. It has the following members:
     * * `duration`: Optional time in ms to wait for mDNS discovery response (defaults to 3000).
     * * `interfaceIpAddress`: Specify which network interface to use by IP address.
     *   If no value or an empty string is provided, mDNS query is sent to all compatible network interfaces.
     * @return Array of discovered devices.
     */
    static std::vector<DeviceDiscoveryResult> discoverTcpDevices(const Tools::DiscoverTCPDevicesOptions& options);
protected:
};


}  // Namespace motion
}  // Namespace zaber
