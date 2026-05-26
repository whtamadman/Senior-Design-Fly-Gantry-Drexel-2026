// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/servo_tuning_paramset.h"

namespace zaber {
namespace motion {
namespace requests {

class LoadParamset: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    ascii::ServoTuningParamset toParamset {0};
    ascii::ServoTuningParamset fromParamset {0};

    LoadParamset();

    LoadParamset(
        int p_interfaceId,
        int p_device,
        int p_axis,
        ascii::ServoTuningParamset p_toParamset,
        ascii::ServoTuningParamset p_fromParamset
    );

    bool operator==(const LoadParamset& other) const;

    bool operator!=(const LoadParamset& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    ascii::ServoTuningParamset const& getToParamset() const;
    void setToParamset(ascii::ServoTuningParamset p_toParamset);

    ascii::ServoTuningParamset const& getFromParamset() const;
    void setFromParamset(ascii::ServoTuningParamset p_fromParamset);

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
