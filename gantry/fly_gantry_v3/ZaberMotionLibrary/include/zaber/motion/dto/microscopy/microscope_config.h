// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/axis_address.h"
#include "zaber/motion/dto/channel_address.h"

namespace zaber {
namespace motion {
namespace microscopy {

/**
 * Configuration representing a microscope setup.
 * Device address of value 0 means that the part is not present.
 */
class MicroscopeConfig: public Serializable {
public:
    std::optional<AxisAddress> focusAxis;
    std::optional<AxisAddress> xAxis;
    std::optional<AxisAddress> yAxis;
    std::optional<int> illuminator;
    std::optional<int> filterChanger;
    std::optional<int> objectiveChanger;
    std::optional<int> autofocus;
    std::optional<ChannelAddress> cameraTrigger;

    MicroscopeConfig();

    MicroscopeConfig(
        std::optional<AxisAddress> p_focusAxis,
        std::optional<AxisAddress> p_xAxis,
        std::optional<AxisAddress> p_yAxis,
        std::optional<int> p_illuminator,
        std::optional<int> p_filterChanger,
        std::optional<int> p_objectiveChanger,
        std::optional<int> p_autofocus,
        std::optional<ChannelAddress> p_cameraTrigger
    );

    bool operator==(const MicroscopeConfig& other) const;

    bool operator!=(const MicroscopeConfig& other) const {
        return !(*this == other);
    }

    /**
     * Focus axis of the microscope.
     */
    std::optional<AxisAddress> const& getFocusAxis() const;
    void setFocusAxis(std::optional<AxisAddress> p_focusAxis);

    /**
     * X axis of the microscope.
     */
    std::optional<AxisAddress> const& getXAxis() const;
    void setXAxis(std::optional<AxisAddress> p_xAxis);

    /**
     * Y axis of the microscope.
     */
    std::optional<AxisAddress> const& getYAxis() const;
    void setYAxis(std::optional<AxisAddress> p_yAxis);

    /**
     * Illuminator device address.
     */
    std::optional<int> getIlluminator() const;
    void setIlluminator(std::optional<int> p_illuminator);

    /**
     * Filter changer device address.
     */
    std::optional<int> getFilterChanger() const;
    void setFilterChanger(std::optional<int> p_filterChanger);

    /**
     * Objective changer device address.
     */
    std::optional<int> getObjectiveChanger() const;
    void setObjectiveChanger(std::optional<int> p_objectiveChanger);

    /**
     * Autofocus identifier.
     */
    std::optional<int> getAutofocus() const;
    void setAutofocus(std::optional<int> p_autofocus);

    /**
     * Camera trigger digital output address.
     */
    std::optional<ChannelAddress> const& getCameraTrigger() const;
    void setCameraTrigger(std::optional<ChannelAddress> p_cameraTrigger);

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

} // namespace microscopy
} // namespace motion
} // namespace zaber
