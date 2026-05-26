// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace microscopy {

/**
 * Status of the autofocus.
 */
class AutofocusStatus: public Serializable {
public:
    bool inFocus {false};
    bool inRange {false};

    AutofocusStatus();

    AutofocusStatus(
        bool p_inFocus,
        bool p_inRange
    );

    bool operator==(const AutofocusStatus& other) const;

    bool operator!=(const AutofocusStatus& other) const {
        return !(*this == other);
    }

    /**
     * Indicates whether the autofocus is in focus.
     */
    bool getInFocus() const;
    void setInFocus(bool p_inFocus);

    /**
     * Indicates whether the autofocus is in range.
     */
    bool getInRange() const;
    void setInRange(bool p_inRange);

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

} // namespace microscopy
} // namespace motion
} // namespace zaber
