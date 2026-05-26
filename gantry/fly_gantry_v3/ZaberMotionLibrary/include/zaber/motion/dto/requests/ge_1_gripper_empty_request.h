// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperEmptyRequest: public Serializable {
public:
    int connectionId {0};

    Ge1GripperEmptyRequest();

    Ge1GripperEmptyRequest(
        int p_connectionId
    );

    bool operator==(const Ge1GripperEmptyRequest& other) const;

    bool operator!=(const Ge1GripperEmptyRequest& other) const {
        return !(*this == other);
    }

    int getConnectionId() const;
    void setConnectionId(int p_connectionId);

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
