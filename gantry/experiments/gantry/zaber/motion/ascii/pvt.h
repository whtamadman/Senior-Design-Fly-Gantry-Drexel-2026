// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/ascii/device.h"

namespace zaber {
namespace motion {
namespace ascii {

/* Forward Declarations */
class PvtSequence;
class PvtBuffer;


/**
 * Class providing access to device PVT (Position-Velocity-Time) features.
 * Requires at least Firmware 7.33.
 */
class Pvt {
public:
    Pvt(Device device);

    /**
     * Gets a PvtSequence class instance which allows you to control a particular PVT sequence on the device.
     * @param pvtId The ID of the PVT sequence to control. The IDs start at 1.
     * @return PvtSequence instance.
     */
    PvtSequence getSequence(int pvtId);
    /**
     * Gets a PvtBuffer class instance which is a handle for a PVT buffer on the device.
     * @param pvtBufferNumber The ID number of the PVT buffer to control. PVT buffer numbers start at one.
     * @return PvtBuffer instance.
     */
    PvtBuffer getBuffer(int pvtBufferNumber);
    /**
     * Get a list of buffer ID numbers that are currently in use.
     * @return List of buffer IDs.
     */
    std::vector<int> listBufferNumbers();
    /**
     * Device that this PVT belongs to.
     */
    Device getDevice() const;
protected:
    Device _device;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
