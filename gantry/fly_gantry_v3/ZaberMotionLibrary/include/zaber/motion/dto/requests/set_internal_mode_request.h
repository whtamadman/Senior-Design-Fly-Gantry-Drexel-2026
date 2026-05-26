// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class SetInternalModeRequest: public Serializable {
public:
    bool mode {false};

    SetInternalModeRequest();

    SetInternalModeRequest(
        bool p_mode
    );

    bool operator==(const SetInternalModeRequest& other) const;

    bool operator!=(const SetInternalModeRequest& other) const {
        return !(*this == other);
    }

    bool getMode() const;
    void setMode(bool p_mode);

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
