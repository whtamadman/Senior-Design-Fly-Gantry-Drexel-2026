// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/requests/axis_move_type.h"
#include "zaber/motion/units.h"
#include "zaber/motion/dto/cyclic_direction.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceMoveRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    bool waitUntilIdle {false};
    AxisMoveType type {0};
    double arg {0.0};
    int argInt {0};
    Units unit {Units::NATIVE};
    double velocity {0.0};
    Units velocityUnit {Units::NATIVE};
    double acceleration {0.0};
    Units accelerationUnit {Units::NATIVE};
    std::optional<CyclicDirection> cyclicDirection;
    std::optional<int> extraCycles;

    DeviceMoveRequest();

    DeviceMoveRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        bool p_waitUntilIdle,
        AxisMoveType p_type,
        double p_arg,
        int p_argInt,
        Units p_unit,
        double p_velocity,
        Units p_velocityUnit,
        double p_acceleration,
        Units p_accelerationUnit,
        std::optional<CyclicDirection> p_cyclicDirection,
        std::optional<int> p_extraCycles
    );

    DeviceMoveRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        bool p_waitUntilIdle,
        AxisMoveType p_type,
        double p_arg,
        int p_argInt,
        Units p_unit,
        double p_velocity,
        Units p_velocityUnit,
        double p_acceleration,
        Units p_accelerationUnit
    );

    bool operator==(const DeviceMoveRequest& other) const;

    bool operator!=(const DeviceMoveRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    bool getWaitUntilIdle() const;
    void setWaitUntilIdle(bool p_waitUntilIdle);

    AxisMoveType const& getType() const;
    void setType(AxisMoveType p_type);

    double getArg() const;
    void setArg(double p_arg);

    int getArgInt() const;
    void setArgInt(int p_argInt);

    Units getUnit() const;
    void setUnit(Units p_unit);

    double getVelocity() const;
    void setVelocity(double p_velocity);

    Units getVelocityUnit() const;
    void setVelocityUnit(Units p_velocityUnit);

    double getAcceleration() const;
    void setAcceleration(double p_acceleration);

    Units getAccelerationUnit() const;
    void setAccelerationUnit(Units p_accelerationUnit);

    std::optional<CyclicDirection> const& getCyclicDirection() const;
    void setCyclicDirection(std::optional<CyclicDirection> p_cyclicDirection);

    std::optional<int> getExtraCycles() const;
    void setExtraCycles(std::optional<int> p_extraCycles);

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
