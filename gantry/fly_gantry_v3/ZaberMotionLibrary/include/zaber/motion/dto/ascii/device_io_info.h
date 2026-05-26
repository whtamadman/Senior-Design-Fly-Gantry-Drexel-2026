// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Class representing information on the I/O channels of the device.
 */
class DeviceIOInfo: public Serializable {
public:
    int numberAnalogOutputs {0};
    int numberAnalogInputs {0};
    int numberDigitalOutputs {0};
    int numberDigitalInputs {0};

    DeviceIOInfo();

    DeviceIOInfo(
        int p_numberAnalogOutputs,
        int p_numberAnalogInputs,
        int p_numberDigitalOutputs,
        int p_numberDigitalInputs
    );

    bool operator==(const DeviceIOInfo& other) const;

    bool operator!=(const DeviceIOInfo& other) const {
        return !(*this == other);
    }

    /**
     * Number of analog output channels.
     */
    int getNumberAnalogOutputs() const;
    void setNumberAnalogOutputs(int p_numberAnalogOutputs);

    /**
     * Number of analog input channels.
     */
    int getNumberAnalogInputs() const;
    void setNumberAnalogInputs(int p_numberAnalogInputs);

    /**
     * Number of digital output channels.
     */
    int getNumberDigitalOutputs() const;
    void setNumberDigitalOutputs(int p_numberDigitalOutputs);

    /**
     * Number of digital input channels.
     */
    int getNumberDigitalInputs() const;
    void setNumberDigitalInputs(int p_numberDigitalInputs);

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

} // namespace ascii
} // namespace motion
} // namespace zaber
