// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/io_port_type.h"
#include "zaber/motion/dto/ascii/trigger_condition.h"

namespace zaber {
namespace motion {
namespace requests {

class TriggerFireWhenIoRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int triggerNumber {0};
    ascii::IoPortType portType {0};
    int channel {0};
    ascii::TriggerCondition triggerCondition {0};
    double value {0.0};

    TriggerFireWhenIoRequest();

    TriggerFireWhenIoRequest(
        int p_interfaceId,
        int p_device,
        int p_triggerNumber,
        ascii::IoPortType p_portType,
        int p_channel,
        ascii::TriggerCondition p_triggerCondition,
        double p_value
    );

    bool operator==(const TriggerFireWhenIoRequest& other) const;

    bool operator!=(const TriggerFireWhenIoRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getTriggerNumber() const;
    void setTriggerNumber(int p_triggerNumber);

    ascii::IoPortType const& getPortType() const;
    void setPortType(ascii::IoPortType p_portType);

    int getChannel() const;
    void setChannel(int p_channel);

    ascii::TriggerCondition const& getTriggerCondition() const;
    void setTriggerCondition(ascii::TriggerCondition p_triggerCondition);

    double getValue() const;
    void setValue(double p_value);

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
