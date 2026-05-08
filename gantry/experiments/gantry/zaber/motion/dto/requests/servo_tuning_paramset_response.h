// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/servo_tuning_paramset.h"

namespace zaber {
namespace motion {
namespace requests {

class ServoTuningParamsetResponse: public Serializable {
public:
    ascii::ServoTuningParamset paramset {0};

    ServoTuningParamsetResponse();

    ServoTuningParamsetResponse(
        ascii::ServoTuningParamset p_paramset
    );

    bool operator==(const ServoTuningParamsetResponse& other) const;

    bool operator!=(const ServoTuningParamsetResponse& other) const {
        return !(*this == other);
    }

    ascii::ServoTuningParamset const& getParamset() const;
    void setParamset(ascii::ServoTuningParamset p_paramset);

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
