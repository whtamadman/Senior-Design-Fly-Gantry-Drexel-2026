// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperReadRegisterRequest: public Serializable {
public:
    int connectionId {0};
    int registerAddress {0};

    Ge1GripperReadRegisterRequest();

    Ge1GripperReadRegisterRequest(
        int p_connectionId,
        int p_registerAddress
    );

    bool operator==(const Ge1GripperReadRegisterRequest& other) const;

    bool operator!=(const Ge1GripperReadRegisterRequest& other) const {
        return !(*this == other);
    }

    int getConnectionId() const;
    void setConnectionId(int p_connectionId);

    int getRegisterAddress() const;
    void setRegisterAddress(int p_registerAddress);

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
