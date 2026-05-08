// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/product/process_controller_source.h"

namespace zaber {
namespace motion {
namespace requests {

class SetProcessControllerSource: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    product::ProcessControllerSource source;

    SetProcessControllerSource();

    SetProcessControllerSource(
        int p_interfaceId,
        int p_device,
        int p_axis,
        product::ProcessControllerSource p_source
    );

    bool operator==(const SetProcessControllerSource& other) const;

    bool operator!=(const SetProcessControllerSource& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    product::ProcessControllerSource const& getSource() const;
    void setSource(product::ProcessControllerSource p_source);

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
