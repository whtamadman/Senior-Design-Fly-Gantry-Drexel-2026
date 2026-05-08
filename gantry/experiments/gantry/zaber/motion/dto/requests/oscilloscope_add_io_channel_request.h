// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/io_port_type.h"

namespace zaber {
namespace motion {
namespace requests {

class OscilloscopeAddIoChannelRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    ascii::IoPortType ioType {0};
    int ioChannel {0};

    OscilloscopeAddIoChannelRequest();

    OscilloscopeAddIoChannelRequest(
        int p_interfaceId,
        int p_device,
        ascii::IoPortType p_ioType,
        int p_ioChannel
    );

    bool operator==(const OscilloscopeAddIoChannelRequest& other) const;

    bool operator!=(const OscilloscopeAddIoChannelRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    ascii::IoPortType const& getIoType() const;
    void setIoType(ascii::IoPortType p_ioType);

    int getIoChannel() const;
    void setIoChannel(int p_ioChannel);

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
