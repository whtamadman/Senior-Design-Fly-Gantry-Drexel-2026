// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/io_port_type.h"

namespace zaber {
namespace motion {
namespace requests {

class GetIoPortLabelRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    ascii::IoPortType portType {0};
    int channelNumber {0};

    GetIoPortLabelRequest();

    GetIoPortLabelRequest(
        int p_interfaceId,
        int p_device,
        ascii::IoPortType p_portType,
        int p_channelNumber
    );

    bool operator==(const GetIoPortLabelRequest& other) const;

    bool operator!=(const GetIoPortLabelRequest& other) const {
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
