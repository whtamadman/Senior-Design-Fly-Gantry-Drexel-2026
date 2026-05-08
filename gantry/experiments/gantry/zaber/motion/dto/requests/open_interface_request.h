// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <optional>
#include <vector>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/requests/interface_type.h"
#include "zaber/motion/dto/ascii/mock_device.h"

namespace zaber {
namespace motion {
namespace requests {

class OpenInterfaceRequest: public Serializable {
public:
    InterfaceType interfaceType {0};
    std::string portName;
    int baudRate {0};
    std::string hostName;
    int port {0};
    int transport {0};
    bool rejectRoutedConnection {false};
    std::string cloudId;
    std::optional<std::string> connectionName;
    std::optional<std::string> realm;
    std::string token;
    std::string api;
    bool testPort {false};
    std::vector<ascii::MockDevice> mockDevices;

    OpenInterfaceRequest();

    OpenInterfaceRequest(
        InterfaceType p_interfaceType,
        std::string p_portName,
        int p_baudRate,
        std::string p_hostName,
        int p_port,
        int p_transport,
        bool p_rejectRoutedConnection,
        std::string p_cloudId,
        std::optional<std::string> p_connectionName,
        std::optional<std::string> p_realm,
        std::string p_token,
        std::string p_api,
        bool p_testPort,
        std::vector<ascii::MockDevice> p_mockDevices
    );

    OpenInterfaceRequest(
        InterfaceType p_interfaceType,
        std::string p_portName,
        int p_baudRate,
        std::string p_hostName,
        int p_port,
        int p_transport,
        bool p_rejectRoutedConnection,
        std::string p_cloudId,
        std::string p_token,
        std::string p_api,
        bool p_testPort
    );

    bool operator==(const OpenInterfaceRequest& other) const;

    bool operator!=(const OpenInterfaceRequest& other) const {
        return !(*this == other);
    }

    InterfaceType const& getInterfaceType() const;
    void setInterfaceType(InterfaceType p_interfaceType);

    std::string const& getPortName() const;
    void setPortName(std::string p_portName);

    int getBaudRate() const;
    void setBaudRate(int p_baudRate);

    std::string const& getHostName() const;
    void setHostName(std::string p_hostName);

    int getPort() const;
    void setPort(int p_port);

    int getTransport() const;
    void setTransport(int p_transport);

    bool getRejectRoutedConnection() const;
    void setRejectRoutedConnection(bool p_rejectRoutedConnection);

    std::string const& getCloudId() const;
    void setCloudId(std::string p_cloudId);

    std::optional<std::string> const& getConnectionName() const;
    void setConnectionName(std::optional<std::string> p_connectionName);

    std::optional<std::string> const& getRealm() const;
    void setRealm(std::optional<std::string> p_realm);

    std::string const& getToken() const;
    void setToken(std::string p_token);

    std::string const& getApi() const;
    void setApi(std::string p_api);

    bool getTestPort() const;
    void setTestPort(bool p_testPort);

    std::vector<ascii::MockDevice> const& getMockDevices() const;
    void setMockDevices(std::vector<ascii::MockDevice> p_mockDevices);

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

} // namespace requests
} // namespace motion
} // namespace zaber
