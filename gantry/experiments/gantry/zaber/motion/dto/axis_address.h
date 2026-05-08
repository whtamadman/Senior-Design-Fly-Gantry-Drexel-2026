// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {

/**
 * Holds device address and axis number.
 */
class AxisAddress: public Serializable {
public:
    int device {0};
    int axis {0};

    AxisAddress();

    AxisAddress(
        int p_device,
        int p_axis
    );

    bool operator==(const AxisAddress& other) const;

    bool operator!=(const AxisAddress& other) const {
        return !(*this == other);
    }

    /**
     * Device address.
     */
    int getDevice() const;
    void setDevice(int p_device);

    /**
     * Axis number.
     */
    int getAxis() const;
    void setAxis(int p_axis);

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

} // namespace motion
} // namespace zaber
