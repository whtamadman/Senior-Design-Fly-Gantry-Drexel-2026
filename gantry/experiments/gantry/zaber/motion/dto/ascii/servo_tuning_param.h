// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * A parameter used to establish the servo tuning of an axis.
 */
class ServoTuningParam: public Serializable {
public:
    std::string name;
    double value {0.0};

    ServoTuningParam();

    ServoTuningParam(
        std::string p_name,
        double p_value
    );

    bool operator==(const ServoTuningParam& other) const;

    bool operator!=(const ServoTuningParam& other) const {
        return !(*this == other);
    }

    /**
     * The name of the parameter to set.
     */
    std::string const& getName() const;
    void setName(std::string p_name);

    /**
     * The value to use for this parameter.
     */
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

} // namespace ascii
} // namespace motion
} // namespace zaber
