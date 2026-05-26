// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace gcode {

/**
 * Represents a message from translator regarding a block translation.
 */
class TranslateMessage: public Serializable {
public:
    std::string message;
    int fromBlock {0};
    int toBlock {0};

    TranslateMessage();

    TranslateMessage(
        std::string p_message,
        int p_fromBlock,
        int p_toBlock
    );

    bool operator==(const TranslateMessage& other) const;

    bool operator!=(const TranslateMessage& other) const {
        return !(*this == other);
    }

    /**
     * The message describing an occurrence.
     */
    std::string const& getMessage() const;
    void setMessage(std::string p_message);

    /**
     * The index in the block string that the message regards to.
     */
    int getFromBlock() const;
    void setFromBlock(int p_fromBlock);

    /**
     * The end index in the block string that the message regards to.
     * The end index is exclusive.
     */
    int getToBlock() const;
    void setToBlock(int p_toBlock);

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

} // namespace gcode
} // namespace motion
} // namespace zaber
