// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/trigger_enabled_state.h"

namespace zaber {
namespace motion {
namespace requests {

class TriggerEnabledStates: public Serializable {
public:
    std::vector<ascii::TriggerEnabledState> states;

    TriggerEnabledStates();

    TriggerEnabledStates(
        std::vector<ascii::TriggerEnabledState> p_states
    );

    bool operator==(const TriggerEnabledStates& other) const;

    bool operator!=(const TriggerEnabledStates& other) const {
        return !(*this == other);
    }

    std::vector<ascii::TriggerEnabledState> const& getStates() const;
    void setStates(std::vector<ascii::TriggerEnabledState> p_states);

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
