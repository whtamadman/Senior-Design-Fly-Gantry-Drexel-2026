// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {

/**
 * Holds device address and IO channel number.
 */
class ChannelAddress: public Serializable {
public:
    int device {0};
    int channel {0};

    ChannelAddress();

    ChannelAddress(
        int p_device,
        int p_channel
    );

    bool operator==(const ChannelAddress& other) const;

    bool operator!=(const ChannelAddress& other) const {
        return !(*this == other);
    }

    /**
     * Device address.
     */
    int getDevice() const;
    void setDevice(int p_device);

    /**
     * IO channel number.
     */
    int getChannel() const;
    void setChannel(int p_channel);

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
