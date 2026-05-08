// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <utility>
#include "zaber/motion/ascii/axis.h"
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber { namespace motion { namespace ascii {
    class Axis;
}}}

namespace zaber {
namespace motion {
namespace microscopy {


/**
 * Represents an objective changer of a microscope.
 * Unstable. Expect breaking changes in future releases.
 * Requires at least Firmware 7.32.
 */
class ObjectiveChanger {
    using Axis = zaber::motion::ascii::Axis;
    using BaseConnection = zaber::motion::ascii::BaseConnection;
    using Connection = zaber::motion::ascii::Connection;
    using Device = zaber::motion::ascii::Device;

public:
    struct ChangeOptions {
        // Optional offset from the focus datum.
        std::optional<Measurement> focusOffset {std::nullopt};
    };

    /**
     * Creates instance of `ObjectiveChanger` based on the given device.
     * If the device is identified, this constructor will ensure it is an objective changer.
     */
    ObjectiveChanger(Device turret, Axis focusAxis);

    ObjectiveChanger();

    /**
     * Changes the objective.
     * Runs a sequence of movements switching from the current objective to the new one.
     * The focus stage moves to the focus datum after the objective change.
     * @param objective Objective number starting from 1.
     * @param focusOffset Optional offset from the focus datum.
     */
    void change(int objective, const std::optional<Measurement>& focusOffset = std::nullopt);

    /**
     * Changes the objective.
     * Runs a sequence of movements switching from the current objective to the new one.
     * The focus stage moves to the focus datum after the objective change.
     * @param objective Objective number starting from 1.
     * @param options A struct of type ChangeOptions. It has the following members:
     * * `focusOffset`: Optional offset from the focus datum.
     */
    void change(int objective, const ObjectiveChanger::ChangeOptions& options);
    /**
     * Moves the focus stage out of the turret releasing the current objective.
     */
    void release();
    /**
     * Returns current objective number starting from 1.
     * The value of 0 indicates that the position is either unknown or between two objectives.
     * @return Current objective number starting from 1 or 0 if not applicable.
     */
    int getCurrentObjective();
    /**
     * Gets number of objectives that the turret can accommodate.
     * @return Number of positions.
     */
    int getNumberOfObjectives();
    /**
     * Gets the focus datum.
     * The focus datum is the position that the focus stage moves to after an objective change.
     * It is backed by the limit.home.offset setting.
     * @param unit Units of datum.
     * @return The datum.
     */
    double getFocusDatum(Units unit = Units::NATIVE);
    /**
     * Sets the focus datum.
     * The focus datum is the position that the focus stage moves to after an objective change.
     * It is backed by the limit.home.offset setting.
     * @param datum Value of datum.
     * @param unit Units of datum.
     */
    void setFocusDatum(double datum, Units unit = Units::NATIVE);
    /**
     * Returns a string that represents the device.
     * @return A string that represents the device.
     */
    std::string toString() const;
    /**
     * Device address of the turret.
     */
    Device getTurret() const;
    /**
     * The focus axis.
     */
    Axis getFocusAxis() const;
protected:
    /**
     * Checks if this is a objective changer and throws an error if it is not.
     */
    void verifyIsChanger() const;
    Device _turret;
    Axis _focusAxis;
};


}  // Namespace microscopy
}  // Namespace motion
}  // Namespace zaber
