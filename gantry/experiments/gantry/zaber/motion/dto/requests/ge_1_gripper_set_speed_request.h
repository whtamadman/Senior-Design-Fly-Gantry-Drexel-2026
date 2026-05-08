// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperSetSpeedRequest: public Serializable {
public:
    int connectionId {0};
    int speed {0};

    Ge1GripperSetSpeedRequest();

    Ge1GripperSetSpeedRequest(
        int p_connectionId,
        int p_speed
    );

    bool operator==(const Ge1GripperSetSpeedRequest& other) const;

    bool operator!=(const Ge1GripperSetSpeedRequest& other) const {
        return !(*this == other);
    }

    int getConnectionId() const;
    void setConnectionId(int p_connectionId);

    int getSpeed() const;
    void setSpeed(int p_speed);

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
