// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace binary {

/**
 * Spontaneous message received from the device.
 */
class ReplyOnlyEvent: public Serializable {
public:
    int deviceAddress {0};
    int command {0};
    int data {0};

    ReplyOnlyEvent();

    ReplyOnlyEvent(
        int p_deviceAddress,
        int p_command,
        int p_data
    );

    bool operator==(const ReplyOnlyEvent& other) const;

    bool operator!=(const ReplyOnlyEvent& other) const {
        return !(*this == other);
    }

    /**
     * Number of the device that sent or should receive the message.
     */
    int getDeviceAddress() const;
    void setDeviceAddress(int p_deviceAddress);

    /**
     * The warning flag contains the highest priority warning currently active for the device or axis.
     */
    int getCommand() const;
    void setCommand(int p_command);

    /**
     * Data payload of the message, if applicable, or zero otherwise.
     */
    int getData() const;
    void setData(int p_data);

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

} // namespace binary
} // namespace motion
} // namespace zaber
