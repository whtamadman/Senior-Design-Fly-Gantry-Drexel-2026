// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include "zaber/motion/ascii/connection.h"
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/gateway/call.h"

namespace zaber {
namespace motion {
namespace ascii {

/* Forward Declarations */
class StreamBuffer;


/**
 * Represents a stream buffer with this number on a device.
 * A stream buffer is a place to store a queue of stream actions.
 */
class StreamBuffer {
public:
    StreamBuffer(Device device, int bufferNumber);

    /**
     * Get the buffer contents as an array of strings.
     * @return A string array containing all the stream commands stored in the buffer.
     */
    std::vector<std::string> getContent();
    /**
     * Erase the contents of the buffer.
     * This method fails if there is a stream writing to the buffer.
     */
    void erase();
    /**
     * The Device this buffer exists on.
     */
    Device getDevice() const;
    /**
     * The number identifying the buffer on the device.
     */
    int getBufferNumber() const;
protected:
    Device _device;
    int _bufferNumber;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
