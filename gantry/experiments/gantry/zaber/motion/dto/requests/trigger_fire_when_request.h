// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class TriggerFireWhenRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int triggerNumber {0};
    std::string condition;

    TriggerFireWhenRequest();

    TriggerFireWhenRequest(
        int p_interfaceId,
        int p_device,
        int p_triggerNumber,
        std::string p_condition
    );

    bool operator==(const TriggerFireWhenRequest& other) const;

    bool operator!=(const TriggerFireWhenRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getTriggerNumber() const;
    void setTriggerNumber(int p_triggerNumber);

    std::string const& getCondition() const;
    void setCondition(std::string p_condition);

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
