// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace requests {

class PrepareCommandRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    std::string commandTemplate;
    std::vector<Measurement> parameters;

    PrepareCommandRequest();

    PrepareCommandRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        std::string p_commandTemplate,
        std::vector<Measurement> p_parameters
    );

    bool operator==(const PrepareCommandRequest& other) const;

    bool operator!=(const PrepareCommandRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    std::string const& getCommandTemplate() const;
    void setCommandTemplate(std::string p_commandTemplate);

    std::vector<Measurement> const& getParameters() const;
    void setParameters(std::vector<Measurement> p_parameters);

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
