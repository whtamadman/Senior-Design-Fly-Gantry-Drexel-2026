// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class ForgetDevicesRequest: public Serializable {
public:
    int interfaceId {0};
    std::vector<int> exceptDevices;

    ForgetDevicesRequest();

    ForgetDevicesRequest(
        int p_interfaceId,
        std::vector<int> p_exceptDevices
    );

    bool operator==(const ForgetDevicesRequest& other) const;

    bool operator!=(const ForgetDevicesRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    std::vector<int> const& getExceptDevices() const;
    void setExceptDevices(std::vector<int> p_exceptDevices);

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
