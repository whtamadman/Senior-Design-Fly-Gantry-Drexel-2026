// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperActivatePresetRequest: public Serializable {
public:
    int connectionId {0};
    int presetNumber {0};
    bool waitUntilIdle {false};

    Ge1GripperActivatePresetRequest();

    Ge1GripperActivatePresetRequest(
        int p_connectionId,
        int p_presetNumber,
        bool p_waitUntilIdle
    );

    bool operator==(const Ge1GripperActivatePresetRequest& other) const;

    bool operator!=(const Ge1GripperActivatePresetRequest& other) const {
        return !(*this == other);
    }

    int getConnectionId() const;
    void setConnectionId(int p_connectionId);

    int getPresetNumber() const;
    void setPresetNumber(int p_presetNumber);

    bool getWaitUntilIdle() const;
    void setWaitUntilIdle(bool p_waitUntilIdle);

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
