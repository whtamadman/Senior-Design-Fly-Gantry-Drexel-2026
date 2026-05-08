// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/io_port_type.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Cancel pending scheduled output changes for multiple analog or digital output pins in a PVT sequence or buffer.
 */
class PvtCancelAllOutputsScheduleAction: public Serializable {
public:
    IoPortType ioType {0};
    std::vector<bool> cancel;

    PvtCancelAllOutputsScheduleAction();

    PvtCancelAllOutputsScheduleAction(
        IoPortType p_ioType,
        std::vector<bool> p_cancel
    );

    PvtCancelAllOutputsScheduleAction(
        IoPortType p_ioType
    );

    bool operator==(const PvtCancelAllOutputsScheduleAction& other) const;

    bool operator!=(const PvtCancelAllOutputsScheduleAction& other) const {
        return !(*this == other);
    }

    /**
     * The type of the output port to cancel. Must be AO or DO; input types are not valid here.
     */
    IoPortType const& getIoType() const;
    void setIoType(IoPortType p_ioType);

    /**
     * Specifies which pins to cancel. If absent, all pins in the port are cancelled.
     */
    std::vector<bool> const& getCancel() const;
    void setCancel(std::vector<bool> p_cancel);

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
