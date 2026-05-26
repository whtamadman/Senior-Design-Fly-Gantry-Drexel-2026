// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <utility>
#include "zaber/motion/ascii/axis.h"
#include "zaber/motion/ascii/connection.h"
#include "zaber/motion/ascii/device.h"

namespace zaber { namespace motion { namespace ascii {
    class Axis;
}}}

namespace zaber {
namespace motion {
namespace microscopy {


/**
 * A generic turret device.
 */
class FilterChanger {
    using Axis = zaber::motion::ascii::Axis;
    using BaseConnection = zaber::motion::ascii::BaseConnection;
    using Connection = zaber::motion::ascii::Connection;
    using Device = zaber::motion::ascii::Device;

public:
    /**
     * Creates instance of `FilterChanger` based on the given device.
     */
    FilterChanger(Device device);

    FilterChanger();

    /**
     * Gets number of filters of the changer.
     * @return Number of positions.
     */
    int getNumberOfFilters();
    /**
     * Returns the current filter number starting from 1.
     * The value of 0 indicates that the position is either unknown or between two filters.
     * @return Filter number starting from 1 or 0 if the position cannot be determined.
     */
    int getCurrentFilter();
    /**
     * Changes to the specified filter.
     * @param filter Filter number starting from 1.
     */
    void change(int filter);
    /**
     * Returns a string that represents the device.
     * @return A string that represents the device.
     */
    std::string toString() const;
    /**
     * The base device of this turret.
     */
    Device getDevice() const;
protected:
    Device _device;
};


}  // Namespace microscopy
}  // Namespace motion
}  // Namespace zaber
