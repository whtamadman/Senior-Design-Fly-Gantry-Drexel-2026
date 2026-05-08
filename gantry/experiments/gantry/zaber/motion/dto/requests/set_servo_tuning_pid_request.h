// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/servo_tuning_paramset.h"

namespace zaber {
namespace motion {
namespace requests {

class SetServoTuningPIDRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    ascii::ServoTuningParamset paramset {0};
    double p {0.0};
    double i {0.0};
    double d {0.0};
    double fc {0.0};

    SetServoTuningPIDRequest();

    SetServoTuningPIDRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        ascii::ServoTuningParamset p_paramset,
        double p_p,
        double p_i,
        double p_d,
        double p_fc
    );

    bool operator==(const SetServoTuningPIDRequest& other) const;

    bool operator!=(const SetServoTuningPIDRequest& other) const {
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

    double getP() const;
    void setP(double p_p);

    double getI() const;
    void setI(double p_i);

    double getD() const;
    void setD(double p_d);

    double getFc() const;
    void setFc(double p_fc);

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
