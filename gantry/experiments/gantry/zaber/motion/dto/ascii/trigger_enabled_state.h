// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * The enabled state of a single trigger.
 * Returns whether the given trigger is enabled and the number of times it will fire.
 * This is a subset of the complete state, and is faster to query.
 */
class TriggerEnabledState: public Serializable {
public:
    bool enabled {false};
    int firesRemaining {0};

    TriggerEnabledState();

    TriggerEnabledState(
        bool p_enabled,
        int p_firesRemaining
    );

    bool operator==(const TriggerEnabledState& other) const;

    bool operator!=(const TriggerEnabledState& other) const {
        return !(*this == other);
    }

    /**
     * The enabled state for a trigger.
     */
    bool getEnabled() const;
    void setEnabled(bool p_enabled);

    /**
     * The number of remaining fires for this trigger.
     * A value of -1 indicates unlimited fires remaining.
     */
    int getFiresRemaining() const;
    void setFiresRemaining(int p_firesRemaining);

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
