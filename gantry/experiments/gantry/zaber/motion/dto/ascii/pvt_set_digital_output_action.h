// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/digital_output_action.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Change the state of a digital output pin in a PVT sequence or buffer.
 */
class PvtSetDigitalOutputAction: public Serializable {
public:
    int channel {0};
    DigitalOutputAction value {0};
    std::optional<Measurement> delay;
    std::optional<DigitalOutputAction> futureValue;

    PvtSetDigitalOutputAction();

    PvtSetDigitalOutputAction(
        int p_channel,
        DigitalOutputAction p_value,
        std::optional<Measurement> p_delay,
        std::optional<DigitalOutputAction> p_futureValue
    );

    PvtSetDigitalOutputAction(
        int p_channel,
        DigitalOutputAction p_value
    );

    bool operator==(const PvtSetDigitalOutputAction& other) const;

    bool operator!=(const PvtSetDigitalOutputAction& other) const {
        return !(*this == other);
    }

    /**
     * The number of the digital output pin to change.
     */
    int getChannel() const;
    void setChannel(int p_channel);

    /**
     * The state to set the digital output pin to.
     */
    DigitalOutputAction const& getValue() const;
    void setValue(DigitalOutputAction p_value);

    /**
     * If nonzero, specifies the time until the delayed output change occurs.
     */
    std::optional<Measurement> const& getDelay() const;
    void setDelay(std::optional<Measurement> p_delay);

    /**
     * The state to set the output pin to after the delay time expires. Ignored if the delay is zero or unspecified.
     */
    std::optional<DigitalOutputAction> const& getFutureValue() const;
    void setFutureValue(std::optional<DigitalOutputAction> p_futureValue);

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

} // namespace ascii
} // namespace motion
} // namespace zaber
