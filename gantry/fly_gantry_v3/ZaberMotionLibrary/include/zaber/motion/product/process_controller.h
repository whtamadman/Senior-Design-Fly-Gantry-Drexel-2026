// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <initializer_list>
#include <string>
#include <utility>
#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/dto/ascii/can_set_state_device_response.h"
#include "zaber/motion/units.h"

namespace zaber { namespace motion { namespace ascii {
    class Device;
    class BaseConnection;
    class Connection;
}}}

namespace zaber {
namespace motion {
namespace product {

/* Forward Declarations */
class Process;


/**
 * Use to manage a process controller.
 * Requires at least Firmware 7.35.
 */
class ProcessController {
    using BaseConnection = zaber::motion::ascii::BaseConnection;
    using Connection = zaber::motion::ascii::Connection;
    using Device = zaber::motion::ascii::Device;

public:
    /**
     * Creates instance of `ProcessController` of the given device.
     * If the device is identified, this constructor will ensure it is a process controller.
     */
    ProcessController(Device device);

    /**
     * Detects the process controllers on the connection.
     * @param connection The connection to detect process controllers on.
     * @param identify If the Process Controllers should be identified upon detection.
     * @return A list of all `ProcessController`s on the connection.
     */
    static std::vector<ProcessController> detect(const BaseConnection& connection, bool identify = true);
    /**
     * Gets an Process class instance which allows you to control a particular voltage source.
     * Axes are numbered from 1.
     * @param processNumber Number of process to control.
     * @return Process instance.
     */
    Process getProcess(int processNumber);
    /**
     * Returns a string that represents the device.
     * @return A string that represents the device.
     */
    std::string toString() const;
    /**
     * The base device of this process controller.
     */
    Device getDevice() const;
protected:
    /**
     * Checks if this is a process controller or some other type of device and throws an error if it is not.
     */
    void verifyIsProcessController() const;
    Device _device;
};


}  // Namespace product
}  // Namespace motion
}  // Namespace zaber
