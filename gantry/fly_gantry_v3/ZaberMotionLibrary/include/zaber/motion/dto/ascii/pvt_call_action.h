// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Represents a buffer call in a PVT sequence or buffer.
 */
class PvtCallAction: public Serializable {
public:
    int bufferNumber {0};

    PvtCallAction();

    PvtCallAction(
        int p_bufferNumber
    );

    bool operator==(const PvtCallAction& other) const;

    bool operator!=(const PvtCallAction& other) const {
        return !(*this == other);
    }

    /**
     * The number of the buffer to call. A buffer with this number must exist on the device when the call is made.
     */
    int getBufferNumber() const;
    void setBufferNumber(int p_bufferNumber);

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

} // namespace ascii
} // namespace motion
} // namespace zaber
