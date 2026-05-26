// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/servo_tuning_paramset.h"
#include "zaber/motion/dto/ascii/servo_tuning_param.h"

namespace zaber {
namespace motion {
namespace requests {

class SetServoTuningRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    ascii::ServoTuningParamset paramset {0};
    std::vector<ascii::ServoTuningParam> tuningParams;
    bool setUnspecifiedToDefault {false};

    SetServoTuningRequest();

    SetServoTuningRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        ascii::ServoTuningParamset p_paramset,
        std::vector<ascii::ServoTuningParam> p_tuningParams,
        bool p_setUnspecifiedToDefault
    );

    bool operator==(const SetServoTuningRequest& other) const;

    bool operator!=(const SetServoTuningRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    ascii::ServoTuningParamset const& getParamset() const;
    void setParamset(ascii::ServoTuningParamset p_paramset);

    std::vector<ascii::ServoTuningParam> const& getTuningParams() const;
    void setTuningParams(std::vector<ascii::ServoTuningParam> p_tuningParams);

    bool getSetUnspecifiedToDefault() const;
    void setSetUnspecifiedToDefault(bool p_setUnspecifiedToDefault);

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
