// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class FindDeviceResponse: public Serializable {
public:
    int address {0};

    FindDeviceResponse();

    FindDeviceResponse(
        int p_address
    );

    bool operator==(const FindDeviceResponse& other) const;

    bool operator!=(const FindDeviceResponse& other) const {
        return !(*this == other);
    }

    int getAddress() const;
    void setAddress(int p_address);

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
