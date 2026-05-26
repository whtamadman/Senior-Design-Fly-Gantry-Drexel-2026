// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Information describing why the command could not fit.
 */
class CommandTooLongExceptionData: public Serializable {
public:
    std::string fit;
    std::string remainder;
    int packetSize {0};
    int packetsMax {0};

    CommandTooLongExceptionData();

    CommandTooLongExceptionData(
        std::string p_fit,
        std::string p_remainder,
        int p_packetSize,
        int p_packetsMax
    );

    bool operator==(const CommandTooLongExceptionData& other) const;

    bool operator!=(const CommandTooLongExceptionData& other) const {
        return !(*this == other);
    }

    /**
     * The part of the command that could be successfully fit in the space provided by the protocol.
     */
    std::string const& getFit() const;
    void setFit(std::string p_fit);

    /**
     * The part of the command that could not fit within the space provided.
     */
    std::string const& getRemainder() const;
    void setRemainder(std::string p_remainder);

    /**
     * The length of the ascii string that can be written to a single line.
     */
    int getPacketSize() const;
    void setPacketSize(int p_packetSize);

    /**
     * The number of lines a command can be split over using continuations.
     */
    int getPacketsMax() const;
    void setPacketsMax(int p_packetsMax);

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
