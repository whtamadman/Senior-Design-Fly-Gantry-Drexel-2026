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
 * Cancel the pending scheduled output change for a single analog or digital output pin in a PVT sequence or buffer.
 */
class PvtCancelOutputScheduleAction: public Serializable {
public:
    int channel {0};
    IoPortType ioType {0};

    PvtCancelOutputScheduleAction();

    PvtCancelOutputScheduleAction(
        int p_channel,
        IoPortType p_ioType
    );

    bool operator==(const PvtCancelOutputScheduleAction& other) const;

    bool operator!=(const PvtCancelOutputScheduleAction& other) const {
        return !(*this == other);
    }

    /**
     * The 1-based number of the output pin whose pending scheduled change to cancel.
     */
    int getChannel() const;
    void setChannel(int p_channel);

    /**
     * The type of the output pin to cancel. Must be AO or DO; input types are not valid here.
     */
    IoPortType const& getIoType() const;
    void setIoType(IoPortType p_ioType);

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
