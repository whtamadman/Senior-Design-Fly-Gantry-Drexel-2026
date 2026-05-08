// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/servo_tuning_paramset.h"
#include "zaber/motion/units.h"
#include "zaber/motion/dto/ascii/servo_tuning_param.h"

namespace zaber {
namespace motion {
namespace requests {

class SetSimpleTuning: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    ascii::ServoTuningParamset paramset {0};
    double loadInertia {0.0};
    Units loadInertiaUnits {Units::NATIVE};
    std::optional<double> carriageInertia;
    Units carriageInertiaUnits {Units::NATIVE};
    std::optional<double> motorInertia;
    Units motorInertiaUnits {Units::NATIVE};
    std::vector<ascii::ServoTuningParam> tuningParams;

    SetSimpleTuning();

    SetSimpleTuning(
        int p_interfaceId,
        int p_device,
        int p_axis,
        ascii::ServoTuningParamset p_paramset,
        double p_loadInertia,
        Units p_loadInertiaUnits,
        std::optional<double> p_carriageInertia,
        Units p_carriageInertiaUnits,
        std::optional<double> p_motorInertia,
        Units p_motorInertiaUnits,
        std::vector<ascii::ServoTuningParam> p_tuningParams
    );

    SetSimpleTuning(
        int p_interfaceId,
        int p_device,
        int p_axis,
        ascii::ServoTuningParamset p_paramset,
        double p_loadInertia,
        Units p_loadInertiaUnits,
        Units p_carriageInertiaUnits,
        Units p_motorInertiaUnits,
        std::vector<ascii::ServoTuningParam> p_tuningParams
    );

    bool operator==(const SetSimpleTuning& other) const;

    bool operator!=(const SetSimpleTuning& other) const {
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

    double getLoadInertia() const;
    void setLoadInertia(double p_loadInertia);

    Units getLoadInertiaUnits() const;
    void setLoadInertiaUnits(Units p_loadInertiaUnits);

    std::optional<double> getCarriageInertia() const;
    void setCarriageInertia(std::optional<double> p_carriageInertia);

    Units getCarriageInertiaUnits() const;
    void setCarriageInertiaUnits(Units p_carriageInertiaUnits);

    std::optional<double> getMotorInertia() const;
    void setMotorInertia(std::optional<double> p_motorInertia);

    Units getMotorInertiaUnits() const;
    void setMotorInertiaUnits(Units p_motorInertiaUnits);

    std::vector<ascii::ServoTuningParam> const& getTuningParams() const;
    void setTuningParams(std::vector<ascii::ServoTuningParam> p_tuningParams);

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
