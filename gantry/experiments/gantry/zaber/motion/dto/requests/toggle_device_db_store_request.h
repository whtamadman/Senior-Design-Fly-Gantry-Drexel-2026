// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class ToggleDeviceDbStoreRequest: public Serializable {
public:
    bool toggleOn {false};
    std::optional<std::string> storeLocation;

    ToggleDeviceDbStoreRequest();

    ToggleDeviceDbStoreRequest(
        bool p_toggleOn,
        std::optional<std::string> p_storeLocation
    );

    ToggleDeviceDbStoreRequest(
        bool p_toggleOn
    );

    bool operator==(const ToggleDeviceDbStoreRequest& other) const;

    bool operator!=(const ToggleDeviceDbStoreRequest& other) const {
        return !(*this == other);
    }

    bool getToggleOn() const;
    void setToggleOn(bool p_toggleOn);

    std::optional<std::string> const& getStoreLocation() const;
    void setStoreLocation(std::optional<std::string> p_storeLocation);

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
