// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/binary/command_code.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class BinaryGenericWithUnitsRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    binary::CommandCode command {0};
    double data {0.0};
    Units fromUnit {Units::NATIVE};
    Units toUnit {Units::NATIVE};
    double timeout {0.0};

    BinaryGenericWithUnitsRequest();

    BinaryGenericWithUnitsRequest(
        int p_interfaceId,
        int p_device,
        binary::CommandCode p_command,
        double p_data,
        Units p_fromUnit,
        Units p_toUnit,
        double p_timeout
    );

    bool operator==(const BinaryGenericWithUnitsRequest& other) const;

    bool operator!=(const BinaryGenericWithUnitsRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    binary::CommandCode const& getCommand() const;
    void setCommand(binary::CommandCode p_command);

    double getData() const;
    void setData(double p_data);

    Units getFromUnit() const;
    void setFromUnit(Units p_fromUnit);

    Units getToUnit() const;
    void setToUnit(Units p_toUnit);

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
