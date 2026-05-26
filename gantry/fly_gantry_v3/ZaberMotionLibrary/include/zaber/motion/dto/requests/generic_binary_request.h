// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/binary/command_code.h"

namespace zaber {
namespace motion {
namespace requests {

class GenericBinaryRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    binary::CommandCode command {0};
    int data {0};
    bool checkErrors {false};
    double timeout {0.0};

    GenericBinaryRequest();

    GenericBinaryRequest(
        int p_interfaceId,
        int p_device,
        binary::CommandCode p_command,
        int p_data,
        bool p_checkErrors,
        double p_timeout
    );

    bool operator==(const GenericBinaryRequest& other) const;

    bool operator!=(const GenericBinaryRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    binary::CommandCode const& getCommand() const;
    void setCommand(binary::CommandCode p_command);

    int getData() const;
    void setData(int p_data);

    bool getCheckErrors() const;
    void setCheckErrors(bool p_checkErrors);

    double getTimeout() const;
    void setTimeout(double p_timeout);

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
