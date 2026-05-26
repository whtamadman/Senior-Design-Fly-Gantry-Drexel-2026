// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/io_port_type.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * The label of an IO port.
 */
class IoPortLabel: public Serializable {
public:
    IoPortType portType {0};
    int channelNumber {0};
    std::string label;

    IoPortLabel();

    IoPortLabel(
        IoPortType p_portType,
        int p_channelNumber,
        std::string p_label
    );

    bool operator==(const IoPortLabel& other) const;

    bool operator!=(const IoPortLabel& other) const {
        return !(*this == other);
    }

    /**
     * The type of the port.
     */
    IoPortType const& getPortType() const;
    void setPortType(IoPortType p_portType);

    /**
     * The number of the port.
     */
    int getChannelNumber() const;
    void setChannelNumber(int p_channelNumber);

    /**
     * The label of the port.
     */
    std::string const& getLabel() const;
    void setLabel(std::string p_label);

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
