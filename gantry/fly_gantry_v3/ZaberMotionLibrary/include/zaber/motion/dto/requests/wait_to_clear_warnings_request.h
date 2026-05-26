// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class WaitToClearWarningsRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    double timeout {0.0};
    std::vector<std::string> warningFlags;

    WaitToClearWarningsRequest();

    WaitToClearWarningsRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        double p_timeout,
        std::vector<std::string> p_warningFlags
    );

    bool operator==(const WaitToClearWarningsRequest& other) const;

    bool operator!=(const WaitToClearWarningsRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    double getTimeout() const;
    void setTimeout(double p_timeout);

    std::vector<std::string> const& getWarningFlags() const;
    void setWarningFlags(std::vector<std::string> p_warningFlags);

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
