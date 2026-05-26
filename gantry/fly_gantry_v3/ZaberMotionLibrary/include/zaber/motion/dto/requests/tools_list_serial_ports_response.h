// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class ToolsListSerialPortsResponse: public Serializable {
public:
    std::vector<std::string> ports;

    ToolsListSerialPortsResponse();

    ToolsListSerialPortsResponse(
        std::vector<std::string> p_ports
    );

    bool operator==(const ToolsListSerialPortsResponse& other) const;

    bool operator!=(const ToolsListSerialPortsResponse& other) const {
        return !(*this == other);
    }

    std::vector<std::string> const& getPorts() const;
    void setPorts(std::vector<std::string> p_ports);

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
