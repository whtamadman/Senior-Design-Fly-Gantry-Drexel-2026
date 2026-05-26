// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/conversion_factor.h"

namespace zaber {
namespace motion {
namespace requests {

class DeviceSetUnitConversionsRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    std::string key;
    std::vector<ascii::ConversionFactor> conversions;

    DeviceSetUnitConversionsRequest();

    DeviceSetUnitConversionsRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        std::string p_key,
        std::vector<ascii::ConversionFactor> p_conversions
    );

    bool operator==(const DeviceSetUnitConversionsRequest& other) const;

    bool operator!=(const DeviceSetUnitConversionsRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    std::string const& getKey() const;
    void setKey(std::string p_key);

    std::vector<ascii::ConversionFactor> const& getConversions() const;
    void setConversions(std::vector<ascii::ConversionFactor> p_conversions);

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
