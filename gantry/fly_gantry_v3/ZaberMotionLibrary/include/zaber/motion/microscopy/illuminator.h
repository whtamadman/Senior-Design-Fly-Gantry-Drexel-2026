// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <utility>
#include "zaber/motion/ascii/axis.h"
#include "zaber/motion/ascii/connection.h"
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/ascii/device_io.h"

namespace zaber { namespace motion { namespace ascii {
    class Axis;
    class DeviceIO;
}}}

namespace zaber {
namespace motion {
namespace microscopy {

/* Forward Declarations */
class IlluminatorChannel;


/**
 * Use to manage an LED controller.
 * Requires at least Firmware 7.09.
 */
class Illuminator {
    using Axis = zaber::motion::ascii::Axis;
    using BaseConnection = zaber::motion::ascii::BaseConnection;
    using Connection = zaber::motion::ascii::Connection;
    using Device = zaber::motion::ascii::Device;
    using DeviceIO = zaber::motion::ascii::DeviceIO;

public:
    struct FindOptions {
        // Optional device address of the illuminator.
        int deviceAddress {0};
    };

    /**
     * Creates instance of `Illuminator` based on the given device.
     * If the device is identified, this constructor will ensure it is an illuminator.
     */
    Illuminator(Device device);

    Illuminator();

    /**
     * Gets an IlluminatorChannel class instance that allows control of a particular channel.
     * Channels are numbered from 1.
     * @param channelNumber Number of channel to control.
     * @return Illuminator channel instance.
     */
    IlluminatorChannel getChannel(int channelNumber);
    /**
     * Turns all channels off.
     */
    void turnOff();
    /**
     * Finds an illuminator on a connection.
     * In case of conflict, specify the optional device address.
     * @param connection Connection on which to detect the illuminator.
     * @param deviceAddress Optional device address of the illuminator.
     * @return New instance of illuminator.
     */
    static Illuminator find(const BaseConnection& connection, int deviceAddress = 0);

    /**
     * Finds an illuminator on a connection.
     * In case of conflict, specify the optional device address.
     * @param connection Connection on which to detect the illuminator.
     * @param options A struct of type FindOptions. It has the following members:
     * * `deviceAddress`: Optional device address of the illuminator.
     * @return New instance of illuminator.
     */
    static Illuminator find(const BaseConnection& connection, const Illuminator::FindOptions& options);
    /**
     * Returns a string that represents the device.
     * @return A string that represents the device.
     */
    std::string toString() const;
    /**
     * The base device of this illuminator.
     */
    Device getDevice() const;
    /**
     * I/O channels of this device.
     */
    DeviceIO getIO() const;
protected:
    /**
     * Checks if this is an illuminator or some other type of device and throws an error if it is not.
     */
    void verifyIsIlluminator() const;
    Device _device;
    DeviceIO _io;
};


}  // Namespace microscopy
}  // Namespace motion
}  // Namespace zaber
