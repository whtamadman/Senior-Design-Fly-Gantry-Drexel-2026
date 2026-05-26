// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/ascii/stream.h"
#include "zaber/motion/ascii/stream_buffer.h"

namespace zaber {
namespace motion {
namespace ascii {


/**
 * Class providing access to device streams.
 * Requires at least Firmware 7.05.
 */
class Streams {
public:
    Streams(Device device);

    /**
     * Gets a Stream class instance which allows you to control a particular stream on the device.
     * @param streamId The ID of the stream to control. Stream IDs start at one.
     * @return Stream instance.
     */
    Stream getStream(int streamId);
    /**
     * Gets a StreamBuffer class instance which is a handle for a stream buffer on the device.
     * @param streamBufferNumber The ID number of the stream buffer to control. Stream buffer IDs start at one.
     * @return StreamBuffer instance.
     */
    StreamBuffer getBuffer(int streamBufferNumber);
    /**
     * Get a list of buffer ID numbers that are currently in use.
     * @return List of buffer IDs.
     */
    std::vector<int> listBufferNumbers();
    /**
     * Device that these streams belong to.
     */
    Device getDevice() const;
protected:
    Device _device;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
