// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/requests/axis_move_type.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class BinaryDeviceMoveRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    double timeout {0.0};
    AxisMoveType type {0};
    double arg {0.0};
    Units unit {Units::NATIVE};

    BinaryDeviceMoveRequest();

    BinaryDeviceMoveRequest(
        int p_interfaceId,
        int p_device,
        double p_timeout,
        AxisMoveType p_type,
        double p_arg,
        Units p_unit
    );

    bool operator==(const BinaryDeviceMoveRequest& other) const;

    bool operator!=(const BinaryDeviceMoveRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    double getTimeout() const;
    void setTimeout(double p_timeout);

    AxisMoveType const& getType() const;
    void setType(AxisMoveType p_type);

    double getArg() const;
    void setArg(double p_arg);

    Units getUnit() const;
    void setUnit(Units p_unit);

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
