// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/binary/reply_only_event.h"

namespace zaber {
namespace motion {
namespace requests {

class BinaryReplyOnlyEventWrapper: public Serializable {
public:
    int interfaceId {0};
    int sessionId {0};
    binary::ReplyOnlyEvent reply;

    BinaryReplyOnlyEventWrapper();

    BinaryReplyOnlyEventWrapper(
        int p_interfaceId,
        int p_sessionId,
        binary::ReplyOnlyEvent p_reply
    );

    bool operator==(const BinaryReplyOnlyEventWrapper& other) const;

    bool operator!=(const BinaryReplyOnlyEventWrapper& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    /**
     * The id of the connection session.
     */
    int getSessionId() const;
    void setSessionId(int p_sessionId);

    binary::ReplyOnlyEvent const& getReply() const;
    void setReply(binary::ReplyOnlyEvent p_reply);

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
