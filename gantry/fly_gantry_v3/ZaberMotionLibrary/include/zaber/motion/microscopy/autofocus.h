// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <utility>
#include "zaber/motion/ascii/axis.h"
#include "zaber/motion/ascii/connection.h"
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/dto/microscopy/autofocus_status.h"
#include "zaber/motion/dto/named_parameter.h"

namespace zaber {
namespace motion {
namespace microscopy {


/**
 * A generic autofocus device.
 */
class Autofocus {
    using Axis = zaber::motion::ascii::Axis;
    using BaseConnection = zaber::motion::ascii::BaseConnection;
    using Connection = zaber::motion::ascii::Connection;
    using Device = zaber::motion::ascii::Device;

public:
    /**
     * Creates instance of `Autofocus` based on the given provider id.
     */
    Autofocus(int providerId, Axis focusAxis, std::optional<Device> objectiveTurret);

    Autofocus();

    /**
     * Sets the current focus to be target for the autofocus control loop.
     */
    void setFocusZero();
    /**
     * Returns the status of the autofocus.
     * @return The status of the autofocus.
     */
    AutofocusStatus getStatus();
    /**
     * Moves the device until it's in focus.
     * @param scan If true, the autofocus will approach from the limit moving until it's in range.
     * @param timeout Sets autofocus timeout duration in milliseconds.
     */
    void focusOnce(bool scan = false, int timeout = -1);
    /**
     * Moves the focus axis continuously maintaining focus.
     * Starts the autofocus control loop.
     * Note that the control loop may stop if the autofocus comes out of range or a movement error occurs.
     * Use WaitUntilIdle of the focus axis to wait for the loop to stop and handle potential errors.
     */
    void startFocusLoop();
    /**
     * Stops autofocus control loop.
     * If the focus axis already stopped moving because of an error, an exception will be thrown.
     */
    void stopFocusLoop();
    /**
     * Returns bool indicating whether the focus axis is busy.
     * Can be used to determine if the focus loop is running.
     * @return True if the axis is currently executing a motion command.
     */
    bool isBusy();
    /**
     * Gets the lower motion limit for the autofocus control loop.
     * Gets motion.tracking.limit.min setting of the focus axis.
     * @param unit The units of the limit.
     * @return Limit value.
     */
    double getLimitMin(Units unit = Units::NATIVE);
    /**
     * Gets the upper motion limit for the autofocus control loop.
     * Gets motion.tracking.limit.max setting of the focus axis.
     * @param unit The units of the limit.
     * @return Limit value.
     */
    double getLimitMax(Units unit = Units::NATIVE);
    /**
     * Sets the lower motion limit for the autofocus control loop.
     * Use the limits to prevent the focus axis from crashing into the sample.
     * Changes motion.tracking.limit.min setting of the focus axis.
     * @param limit The lower limit of the focus axis.
     * @param unit The units of the limit.
     */
    void setLimitMin(double limit, Units unit = Units::NATIVE);
    /**
     * Sets the upper motion limit for the autofocus control loop.
     * Use the limits to prevent the focus axis from crashing into the sample.
     * Changes motion.tracking.limit.max setting of the focus axis.
     * @param limit The upper limit of the focus axis.
     * @param unit The units of the limit.
     */
    void setLimitMax(double limit, Units unit = Units::NATIVE);
    /**
     * Typically, the control loop parameters and objective are kept synchronized by the library.
     * If the parameters or current objective changes outside of the library, call this method to synchronize them.
     */
    void synchronizeParameters();
    /**
     * Sets the parameters for the autofocus objective.
     * Note that the method temporarily switches current objective to set the parameters.
     * @param objective The objective (numbered from 1) to set the parameters for.
     * If your microscope has only one objective, use value of 1.
     * @param parameters The parameters for the autofocus objective.
     */
    void setObjectiveParameters(int objective, const std::vector<NamedParameter>& parameters);
    /**
     * Returns the parameters for the autofocus objective.
     * @param objective The objective (numbered from 1) to get the parameters for.
     * If your microscope has only one objective, use value of 1.
     * Note that the method temporarily switches current objective to get the parameters.
     * @return The parameters for the autofocus objective.
     */
    std::vector<NamedParameter> getObjectiveParameters(int objective);
    /**
     * Returns a string that represents the autofocus.
     * @return A string that represents the autofocus.
     */
    std::string toString() const;
    /**
     * The identification of external device providing the capability.
     */
    int getProviderId() const;
    /**
     * The focus axis.
     */
    Axis getFocusAxis() const;
    /**
     * The objective turret device if the microscope has one.
     */
    std::optional<Device> getObjectiveTurret() const;
protected:
    int _providerId;
    Axis _focusAxis;
    std::optional<Device> _objectiveTurret;
};


}  // Namespace microscopy
}  // Namespace motion
}  // Namespace zaber
