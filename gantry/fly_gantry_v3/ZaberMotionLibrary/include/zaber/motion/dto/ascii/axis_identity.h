// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/axis_type.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Representation of data gathered during axis identification.
 */
class AxisIdentity: public Serializable {
public:
    int peripheralId {0};
    std::string peripheralName;
    unsigned int peripheralSerialNumber {0};
    bool isPeripheral {false};
    AxisType axisType {0};
    bool isModified {false};
    unsigned int resolution {0};

    AxisIdentity();

    AxisIdentity(
        int p_peripheralId,
        std::string p_peripheralName,
        unsigned int p_peripheralSerialNumber,
        bool p_isPeripheral,
        AxisType p_axisType,
        bool p_isModified,
        unsigned int p_resolution
    );

    bool operator==(const AxisIdentity& other) const;

    bool operator!=(const AxisIdentity& other) const {
        return !(*this == other);
    }

    /**
     * Unique ID of the peripheral hardware.
     */
    int getPeripheralId() const;
    void setPeripheralId(int p_peripheralId);

    /**
     * Name of the peripheral.
     */
    std::string const& getPeripheralName() const;
    void setPeripheralName(std::string p_peripheralName);

    /**
     * Serial number of the peripheral, or 0 when not applicable.
     */
    unsigned int getPeripheralSerialNumber() const;
    void setPeripheralSerialNumber(unsigned int p_peripheralSerialNumber);

    /**
     * Indicates whether the axis is a peripheral or part of an integrated device.
     */
    bool getIsPeripheral() const;
    void setIsPeripheral(bool p_isPeripheral);

    /**
     * Determines the type of an axis and units it accepts.
     */
    AxisType const& getAxisType() const;
    void setAxisType(AxisType p_axisType);

    /**
     * The peripheral has hardware modifications.
     */
    bool getIsModified() const;
    void setIsModified(bool p_isModified);

    /**
     * The number of microsteps per full step for motion axes. Always equal to 0 for non-motion axes.
     */
    unsigned int getResolution() const;
    void setResolution(unsigned int p_resolution);

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
