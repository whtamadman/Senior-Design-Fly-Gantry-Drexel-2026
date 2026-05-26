// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Contains additional data for GCodeSyntaxException.
 */
class GCodeSyntaxExceptionData: public Serializable {
public:
    int fromBlock {0};
    int toBlock {0};

    GCodeSyntaxExceptionData();

    GCodeSyntaxExceptionData(
        int p_fromBlock,
        int p_toBlock
    );

    bool operator==(const GCodeSyntaxExceptionData& other) const;

    bool operator!=(const GCodeSyntaxExceptionData& other) const {
        return !(*this == other);
    }

    /**
     * The index in the block string that caused the exception.
     */
    int getFromBlock() const;
    void setFromBlock(int p_fromBlock);

    /**
     * The end index in the block string that caused the exception.
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

} // namespace exceptions
} // namespace motion
} // namespace zaber
