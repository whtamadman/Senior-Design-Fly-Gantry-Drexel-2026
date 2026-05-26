// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * The complete state of a trigger.
 */
class TriggerState: public Serializable {
public:
    std::string condition;
    std::vector<std::string> actions;
    bool enabled {false};
    int firesTotal {0};
    int firesRemaining {0};

    TriggerState();

    TriggerState(
        std::string p_condition,
        std::vector<std::string> p_actions,
        bool p_enabled,
        int p_firesTotal,
        int p_firesRemaining
    );

    bool operator==(const TriggerState& other) const;

    bool operator!=(const TriggerState& other) const {
        return !(*this == other);
    }

    /**
     * The firing condition for a trigger.
     */
    std::string const& getCondition() const;
    void setCondition(std::string p_condition);

    /**
     * The actions for a trigger.
     */
    std::vector<std::string> const& getActions() const;
    void setActions(std::vector<std::string> p_actions);

    /**
     * The enabled state for a trigger.
     */
    bool getEnabled() const;
    void setEnabled(bool p_enabled);

    /**
     * The number of total fires for this trigger.
     * A value of -1 indicates unlimited fires.
     */
    int getFiresTotal() const;
    void setFiresTotal(int p_firesTotal);

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
