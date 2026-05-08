// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class GenericCommandRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int axis {0};
    std::string command;
    bool checkErrors {false};
    int timeout {0};

    GenericCommandRequest();

    GenericCommandRequest(
        int p_interfaceId,
        int p_device,
        int p_axis,
        std::string p_command,
        bool p_checkErrors,
        int p_timeout
    );

    bool operator==(const GenericCommandRequest& other) const;

    bool operator!=(const GenericCommandRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getAxis() const;
    void setAxis(int p_axis);

    std::string const& getCommand() const;
    void setCommand(std::string p_command);

    bool getCheckErrors() const;
    void setCheckErrors(bool p_checkErrors);

    int getTimeout() const;
    void setTimeout(int p_timeout);

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
