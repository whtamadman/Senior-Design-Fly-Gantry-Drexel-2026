// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/servo_tuning_param.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * The masses and parameters last used by simple tuning.
 */
class SimpleTuning: public Serializable {
public:
    bool isUsed {false};
    bool isSet {false};
    std::optional<double> carriageInertia;
    std::optional<double> motorInertia;
    double loadInertia {0.0};
    std::vector<ServoTuningParam> tuningParams;

    SimpleTuning();

    SimpleTuning(
        bool p_isUsed,
        bool p_isSet,
        std::optional<double> p_carriageInertia,
        std::optional<double> p_motorInertia,
        double p_loadInertia,
        std::vector<ServoTuningParam> p_tuningParams
    );

    SimpleTuning(
        bool p_isUsed,
        bool p_isSet,
        double p_loadInertia,
        std::vector<ServoTuningParam> p_tuningParams
    );

    bool operator==(const SimpleTuning& other) const;

    bool operator!=(const SimpleTuning& other) const {
        return !(*this == other);
    }

    /**
     * Whether the tuning returned is currently in use by this paramset,
     * or if it has been overwritten by a later change.
     */
    bool getIsUsed() const;
    void setIsUsed(bool p_isUsed);

    /**
     * If this paramset has been tuned using the simple tuning method, whether or not it's currently in use.
     */
    bool getIsSet() const;
    void setIsSet(bool p_isSet);

    /**
     * The inertia of the carriage in kg (for linear devices) or kg⋅m² (for rotary devices).
     */
    std::optional<double> getCarriageInertia() const;
    void setCarriageInertia(std::optional<double> p_carriageInertia);

    /**
     * The inertia of the motor in kg⋅m².
     */
    std::optional<double> getMotorInertia() const;
    void setMotorInertia(std::optional<double> p_motorInertia);

    /**
     * The inertia of the load in kg (for linear devices) or kg⋅m² (for rotary devices),
     * excluding the inertia of the carriage.
     */
    double getLoadInertia() const;
    void setLoadInertia(double p_loadInertia);

    /**
     * The parameters used by simple tuning.
     */
    std::vector<ServoTuningParam> const& getTuningParams() const;
    void setTuningParams(std::vector<ServoTuningParam> p_tuningParams);

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
