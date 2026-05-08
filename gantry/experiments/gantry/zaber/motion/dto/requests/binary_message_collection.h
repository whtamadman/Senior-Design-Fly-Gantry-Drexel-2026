// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/binary/message.h"

namespace zaber {
namespace motion {
namespace requests {

class BinaryMessageCollection: public Serializable {
public:
    std::vector<binary::Message> messages;

    BinaryMessageCollection();

    BinaryMessageCollection(
        std::vector<binary::Message> p_messages
    );

    bool operator==(const BinaryMessageCollection& other) const;

    bool operator!=(const BinaryMessageCollection& other) const {
        return !(*this == other);
    }

    std::vector<binary::Message> const& getMessages() const;
    void setMessages(std::vector<binary::Message> p_messages);

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
