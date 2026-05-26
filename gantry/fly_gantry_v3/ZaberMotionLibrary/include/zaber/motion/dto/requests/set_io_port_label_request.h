// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/io_port_type.h"

namespace zaber {
namespace motion {
namespace requests {

class SetIoPortLabelRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    ascii::IoPortType portType {0};
    int channelNumber {0};
    std::optional<std::string> label;

    SetIoPortLabelRequest();

    SetIoPortLabelRequest(
        int p_interfaceId,
        int p_device,
        ascii::IoPortType p_portType,
        int p_channelNumber,
        std::optional<std::string> p_label
    );

    SetIoPortLabelRequest(
        int p_interfaceId,
        int p_device,
        ascii::IoPortType p_portType,
        int p_channelNumber
    );

    bool operator==(const SetIoPortLabelRequest& other) const;

    bool operator!=(const SetIoPortLabelRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    ascii::IoPortType const& getPortType() const;
    void setPortType(ascii::IoPortType p_portType);

    int getChannelNumber() const;
    void setChannelNumber(int p_channelNumber);

    std::optional<std::string> const& getLabel() const;
    void setLabel(std::optional<std::string> p_label);

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
