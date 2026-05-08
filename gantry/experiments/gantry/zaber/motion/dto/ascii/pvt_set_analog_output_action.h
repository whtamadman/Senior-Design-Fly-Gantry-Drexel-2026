// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Change the state of an analog output pin in a PVT sequence or buffer.
 */
class PvtSetAnalogOutputAction: public Serializable {
public:
    int channel {0};
    Measurement value;
    std::optional<Measurement> delay;
    std::optional<Measurement> futureValue;

    PvtSetAnalogOutputAction();

    PvtSetAnalogOutputAction(
        int p_channel,
        Measurement p_value,
        std::optional<Measurement> p_delay,
        std::optional<Measurement> p_futureValue
    );

    PvtSetAnalogOutputAction(
        int p_channel,
        Measurement p_value
    );

    bool operator==(const PvtSetAnalogOutputAction& other) const;

    bool operator!=(const PvtSetAnalogOutputAction& other) const {
        return !(*this == other);
    }

    /**
     * The number of the analog output pin to change.
     */
    int getChannel() const;
    void setChannel(int p_channel);

    /**
     * The voltage to set the analog output pin to.
     */
    Measurement const& getValue() const;
    void setValue(Measurement p_value);

    /**
     * If nonzero, specifies the time until the delayed output change occurs.
     */
    std::optional<Measurement> const& getDelay() const;
    void setDelay(std::optional<Measurement> p_delay);

    /**
     * The voltage to set the output pin to after the delay time expires. Ignored if the delay is zero or unspecified.
     */
    std::optional<Measurement> const& getFutureValue() const;
    void setFutureValue(std::optional<Measurement> p_futureValue);

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
