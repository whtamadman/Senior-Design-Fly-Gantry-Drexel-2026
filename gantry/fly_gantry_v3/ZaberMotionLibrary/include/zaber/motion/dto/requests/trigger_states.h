// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/trigger_state.h"

namespace zaber {
namespace motion {
namespace requests {

class TriggerStates: public Serializable {
public:
    std::vector<ascii::TriggerState> states;

    TriggerStates();

    TriggerStates(
        std::vector<ascii::TriggerState> p_states
    );

    bool operator==(const TriggerStates& other) const;

    bool operator!=(const TriggerStates& other) const {
        return !(*this == other);
    }

    std::vector<ascii::TriggerState> const& getStates() const;
    void setStates(std::vector<ascii::TriggerState> p_states);

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
