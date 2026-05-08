// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/requests/interface_type.h"

namespace zaber {
namespace motion {
namespace requests {

class OpenBinaryInterfaceRequest: public Serializable {
public:
    InterfaceType interfaceType {0};
    std::string portName;
    int baudRate {0};
    std::string hostName;
    int port {0};
    bool useMessageIds {false};

    OpenBinaryInterfaceRequest();

    OpenBinaryInterfaceRequest(
        InterfaceType p_interfaceType,
        std::string p_portName,
        int p_baudRate,
        std::string p_hostName,
        int p_port,
        bool p_useMessageIds
    );

    bool operator==(const OpenBinaryInterfaceRequest& other) const;

    bool operator!=(const OpenBinaryInterfaceRequest& other) const {
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

    bool getUseMessageIds() const;
    void setUseMessageIds(bool p_useMessageIds);

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
