// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Denotes type of the response message.
 * For more information refer to:
 * [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_message_format).
 */
enum class MessageType {
    /* A direct response to a command sent to the device. */
    REPLY = 0,
    /* An additional data message supplementing a reply. */
    INFO = 1,
    /* An unsolicited message from the device reporting a status change. */
    ALERT = 2,
};

/**
 * Returns string representation of MessageType value
 */
std::string MessageType_toString(MessageType value);


} // namespace ascii
} // namespace motion
} // namespace zaber
