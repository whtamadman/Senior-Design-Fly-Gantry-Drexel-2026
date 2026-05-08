// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace requests {

class AxesMoveRequest: public Serializable {
public:
    std::vector<int> interfaces;
    std::vector<int> devices;
    std::vector<int> axes;
    std::vector<Measurement> position;

    AxesMoveRequest();

    AxesMoveRequest(
        std::vector<int> p_interfaces,
        std::vector<int> p_devices,
        std::vector<int> p_axes,
        std::vector<Measurement> p_position
    );

    bool operator==(const AxesMoveRequest& other) const;

    bool operator!=(const AxesMoveRequest& other) const {
        return !(*this == other);
    }

    std::vector<int> const& getInterfaces() const;
    void setInterfaces(std::vector<int> p_interfaces);

    std::vector<int> const& getDevices() const;
    void setDevices(std::vector<int> p_devices);

    std::vector<int> const& getAxes() const;
    void setAxes(std::vector<int> p_axes);

    std::vector<Measurement> const& getPosition() const;
    void setPosition(std::vector<Measurement> p_position);

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
