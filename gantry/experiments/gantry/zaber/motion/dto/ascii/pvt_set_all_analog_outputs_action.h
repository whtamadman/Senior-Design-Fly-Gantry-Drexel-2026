// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Change the state of multiple pins of an analog output port in a PVT sequence or buffer.
 */
class PvtSetAllAnalogOutputsAction: public Serializable {
public:
    std::vector<Measurement> values;
    std::optional<Measurement> delay;
    std::vector<Measurement> futureValues;

    PvtSetAllAnalogOutputsAction();

    PvtSetAllAnalogOutputsAction(
        std::vector<Measurement> p_values,
        std::optional<Measurement> p_delay,
        std::vector<Measurement> p_futureValues
    );

    PvtSetAllAnalogOutputsAction(
        std::vector<Measurement> p_values
    );

    bool operator==(const PvtSetAllAnalogOutputsAction& other) const;

    bool operator!=(const PvtSetAllAnalogOutputsAction& other) const {
        return !(*this == other);
    }

    /**
     * The voltages to set the analog output pins to. Must have one entry per pin in the port.
     */
    std::vector<Measurement> const& getValues() const;
    void setValues(std::vector<Measurement> p_values);

    /**
     * If nonzero, specifies the time until the delayed output change occurs.
     */
    std::optional<Measurement> const& getDelay() const;
    void setDelay(std::optional<Measurement> p_delay);

    /**
     * The voltages to set the output pins to after the delay time expires. Ignored if the delay is zero or unspecified.
     * Must have one entry per pin in the port.
     */
    std::vector<Measurement> const& getFutureValues() const;
    void setFutureValues(std::vector<Measurement> p_futureValues);

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
