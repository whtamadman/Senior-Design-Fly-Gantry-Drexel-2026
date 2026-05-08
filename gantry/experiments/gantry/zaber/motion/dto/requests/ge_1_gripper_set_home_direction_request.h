// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/product/ge_1_gripper_direction.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperSetHomeDirectionRequest: public Serializable {
public:
    int connectionId {0};
    product::Ge1GripperDirection direction {0};
    bool saveToFlash {false};

    Ge1GripperSetHomeDirectionRequest();

    Ge1GripperSetHomeDirectionRequest(
        int p_connectionId,
        product::Ge1GripperDirection p_direction,
        bool p_saveToFlash
    );

    bool operator==(const Ge1GripperSetHomeDirectionRequest& other) const;

    bool operator!=(const Ge1GripperSetHomeDirectionRequest& other) const {
        return !(*this == other);
    }

    int getConnectionId() const;
    void setConnectionId(int p_connectionId);

    product::Ge1GripperDirection const& getDirection() const;
    void setDirection(product::Ge1GripperDirection p_direction);

    bool getSaveToFlash() const;
    void setSaveToFlash(bool p_saveToFlash);

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
