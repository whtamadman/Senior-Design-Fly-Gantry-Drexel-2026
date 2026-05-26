// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class TriggerSetLabelRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int triggerNumber {0};
    std::optional<std::string> label;

    TriggerSetLabelRequest();

    TriggerSetLabelRequest(
        int p_interfaceId,
        int p_device,
        int p_triggerNumber,
        std::optional<std::string> p_label
    );

    TriggerSetLabelRequest(
        int p_interfaceId,
        int p_device,
        int p_triggerNumber
    );

    bool operator==(const TriggerSetLabelRequest& other) const;

    bool operator!=(const TriggerSetLabelRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getTriggerNumber() const;
    void setTriggerNumber(int p_triggerNumber);

    std::optional<std::string> const& getLabel() const;
    void setLabel(std::optional<std::string> p_label);

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
