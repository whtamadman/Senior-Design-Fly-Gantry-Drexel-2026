// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>
#include <utility>
#include "zaber/motion/ascii/axis.h"
#include "zaber/motion/ascii/axis_group.h"
#include "zaber/motion/ascii/connection.h"
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/dto/microscopy/microscope_config.h"
#include "zaber/motion/dto/microscopy/third_party_components.h"
#include "zaber/motion/microscopy/autofocus.h"
#include "zaber/motion/microscopy/camera_trigger.h"
#include "zaber/motion/microscopy/filter_changer.h"
#include "zaber/motion/microscopy/illuminator.h"
#include "zaber/motion/microscopy/objective_changer.h"

namespace zaber {
namespace motion {
namespace microscopy {


/**
 * Represent a microscope.
 * Parts of the microscope may or may not be instantiated depending on the configuration.
 * Requires at least Firmware 7.34.
 */
class Microscope {
    using Axis = zaber::motion::ascii::Axis;
    using AxisGroup = zaber::motion::ascii::AxisGroup;
    using BaseConnection = zaber::motion::ascii::BaseConnection;
    using Connection = zaber::motion::ascii::Connection;
    using Device = zaber::motion::ascii::Device;

public:
    struct InitializeOptions {
        // Forces all devices to home even when not required.
        bool force {false};
    };

    /**
     * Creates instance of `Microscope` from the given config.
     * Parts are instantiated depending on device addresses in the config.
     */
    Microscope(BaseConnection connection, MicroscopeConfig config);

    Microscope();

    /**
     * Finds a microscope on a connection.
     * @param connection Connection on which to detect the microscope.
     * @param thirdPartyComponents Third party components of the microscope that cannot be found on the connection.
     * @return New instance of microscope.
     */
    static Microscope find(const BaseConnection& connection, const std::optional<ThirdPartyComponents>& thirdPartyComponents = {});
    /**
     * Initializes the microscope.
     * Homes all axes, filter changer, and objective changer if they require it.
     * @param force Forces all devices to home even when not required.
     */
    void initialize(bool force = false);

    /**
     * Initializes the microscope.
     * Homes all axes, filter changer, and objective changer if they require it.
     * @param options A struct of type InitializeOptions. It has the following members:
     * * `force`: Forces all devices to home even when not required.
     */
    void initialize(const Microscope::InitializeOptions& options);
    /**
     * Checks whether the microscope is initialized.
     * @return True, when the microscope is initialized. False, otherwise.
     */
    bool isInitialized();
    /**
     * Returns a string that represents the microscope.
     * @return A string that represents the microscope.
     */
    std::string toString() const;
    /**
     * Connection of the microscope.
     */
    BaseConnection getConnection() const;
    /**
     * The illuminator.
     */
    std::optional<Illuminator> getIlluminator() const;
    /**
     * The focus axis.
     */
    std::optional<Axis> getFocusAxis() const;
    /**
     * The X axis.
     */
    std::optional<Axis> getXAxis() const;
    /**
     * The Y axis.
     */
    std::optional<Axis> getYAxis() const;
    /**
     * Axis group consisting of X and Y axes representing the plate of the microscope.
     */
    std::optional<AxisGroup> getPlate() const;
    /**
     * The objective changer.
     */
    std::optional<ObjectiveChanger> getObjectiveChanger() const;
    /**
     * The filter changer.
     */
    std::optional<FilterChanger> getFilterChanger() const;
    /**
     * The autofocus feature.
     */
    std::optional<Autofocus> getAutofocus() const;
    /**
     * The camera trigger.
     */
    std::optional<CameraTrigger> getCameraTrigger() const;
protected:
    MicroscopeConfig getConfig() const;
    BaseConnection _connection;
    MicroscopeConfig _config;
    std::optional<Illuminator> _illuminator;
    std::optional<Axis> _focusAxis;
    std::optional<Axis> _xAxis;
    std::optional<Axis> _yAxis;
    std::optional<AxisGroup> _plate;
    std::optional<ObjectiveChanger> _objectiveChanger;
    std::optional<FilterChanger> _filterChanger;
    std::optional<Autofocus> _autofocus;
    std::optional<CameraTrigger> _cameraTrigger;
public:
    /**
     * Initializes the components of the microscope based on the configuration.
     */
    void initializeComponents();
};


}  // Namespace microscopy
}  // Namespace motion
}  // Namespace zaber
