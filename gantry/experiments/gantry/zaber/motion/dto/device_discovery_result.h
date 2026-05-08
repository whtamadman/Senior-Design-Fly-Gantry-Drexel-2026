// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/device_port_type.h"

namespace zaber {
namespace motion {

/**
 * Represents result of mDNS discovery for devices connected to network.
 */
class DeviceDiscoveryResult: public Serializable {
public:
    std::string hostname;
    std::string address;
    int port {0};
    DevicePortType portType {0};
    int deviceId {0};
    int serialNumber {0};

    DeviceDiscoveryResult();

    DeviceDiscoveryResult(
        std::string p_hostname,
        std::string p_address,
        int p_port,
        DevicePortType p_portType,
        int p_deviceId,
        int p_serialNumber
    );

    bool operator==(const DeviceDiscoveryResult& other) const;

    bool operator!=(const DeviceDiscoveryResult& other) const {
        return !(*this == other);
    }

    /**
     * Host name of the discoverd device.
     */
    std::string const& getHostname() const;
    void setHostname(std::string p_hostname);

    /**
     * IP address of the discoverd device.
     */
    std::string const& getAddress() const;
    void setAddress(std::string p_address);

    /**
     * Port number of the discovered device.
     */
    int getPort() const;
    void setPort(int p_port);

    /**
     * Indicates if discovery result represents a single device or a device chain.
     */
    DevicePortType const& getPortType() const;
    void setPortType(DevicePortType p_portType);

    /**
     * Device id of discovered device or head of discovered device chain.
     */
    int getDeviceId() const;
    void setDeviceId(int p_deviceId);

    /**
     * Serial number of discovered device or head of discovered device chain.
     */
    int getSerialNumber() const;
    void setSerialNumber(int p_serialNumber);

    /**
     * Convert object to human-readable string format
     */
    std::string toString() const;

#ifdef ZML_SERIALIZATION_PUBLIC
public:
#else
private:
#endif

    std::string toByteArray() const override;
    void populateFromByteArray(const std::string& buffer) override;

};

} // namespace motion
} // namespace zaber
