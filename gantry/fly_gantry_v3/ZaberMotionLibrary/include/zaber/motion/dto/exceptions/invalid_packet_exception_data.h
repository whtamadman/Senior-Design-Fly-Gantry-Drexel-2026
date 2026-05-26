// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Contains additional data for the InvalidPacketException.
 */
class InvalidPacketExceptionData: public Serializable {
public:
    std::string packet;
    std::string reason;

    InvalidPacketExceptionData();

    InvalidPacketExceptionData(
        std::string p_packet,
        std::string p_reason
    );

    bool operator==(const InvalidPacketExceptionData& other) const;

    bool operator!=(const InvalidPacketExceptionData& other) const {
        return !(*this == other);
    }

    /**
     * The invalid packet that caused the exception.
     */
    std::string const& getPacket() const;
    void setPacket(std::string p_packet);

    /**
     * The reason for the exception.
     */
    std::string const& getReason() const;
    void setReason(std::string p_reason);

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

} // namespace exceptions
} // namespace motion
} // namespace zaber
