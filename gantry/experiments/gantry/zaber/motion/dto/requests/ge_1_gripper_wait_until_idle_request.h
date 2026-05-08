// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperWaitUntilIdleRequest: public Serializable {
public:
    int connectionId {0};
    bool waitUntilIdle {false};

    Ge1GripperWaitUntilIdleRequest();

    Ge1GripperWaitUntilIdleRequest(
        int p_connectionId,
        bool p_waitUntilIdle
    );

    bool operator==(const Ge1GripperWaitUntilIdleRequest& other) const;

    bool operator!=(const Ge1GripperWaitUntilIdleRequest& other) const {
        return !(*this == other);
    }

    int getConnectionId() const;
    void setConnectionId(int p_connectionId);

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
