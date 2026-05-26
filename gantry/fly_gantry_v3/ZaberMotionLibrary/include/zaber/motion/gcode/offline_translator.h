// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <initializer_list>
#include <string>
#include <utility>
#include <vector>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/dto/gcode/device_definition.h"
#include "zaber/motion/dto/gcode/translate_result.h"
#include "zaber/motion/dto/gcode/translator_config.h"
#include "zaber/motion/units.h"

namespace zaber { namespace motion { namespace ascii {
    class Device;
}}}

namespace zaber {
namespace motion {
namespace gcode {


/**
 * Represents an offline G-Code translator.
 * It allows to translate G-Code blocks to Zaber ASCII protocol stream commands.
 * This translator does not need a connected device to perform translation.
 * Requires at least Firmware 7.11.
 */
class OfflineTranslator {
    using Device = zaber::motion::ascii::Device;

public:
    OfflineTranslator(int translatorId);

    OfflineTranslator(const OfflineTranslator& other) = delete;
    OfflineTranslator& operator=(const OfflineTranslator& other) = delete;

    /**
     * Sets up translator from provided device definition and configuration.
     * @param definition Definition of device and its peripherals.
     * The definition must match a device that later performs the commands.
     * @param config Configuration of the translator.
     * @return New instance of translator.
     */
    static OfflineTranslator setup(const DeviceDefinition& definition, const std::optional<TranslatorConfig>& config = {});
    /**
     * Sets up an offline translator from provided device, axes, and configuration.
     * @param device Device that later performs the command streaming.
     * @param axes Axis numbers that are later used to setup the stream.
     * For a lockstep group specify only the first axis of the group.
     * @param config Configuration of the translator.
     * @return New instance of translator.
     */
    static OfflineTranslator setupFromDevice(const Device& device, const std::vector<int>& axes, const std::optional<TranslatorConfig>& config = {});
    /**
     * Translates a single block (line) of G-code.
     * @param block Block (line) of G-code.
     * @return Result of translation containing the stream commands.
     */
    TranslateResult translate(const std::string& block);
    /**
     * Flushes the remaining stream commands waiting in optimization buffer.
     * The flush is also performed by M2 and M30 codes.
     * @return The remaining stream commands.
     */
    std::vector<std::string> flush();
    /**
     * Sets the speed at which the device moves when traversing (G0).
     * @param traverseRate The traverse rate.
     * @param unit Units of the traverse rate.
     */
    void setTraverseRate(double traverseRate, Units unit);
    /**
     * Sets position of translator's axis.
     * Use this method to set position after performing movement outside of the translator.
     * This method does not cause any movement.
     * @param axis Letter of the axis.
     * @param position The position.
     * @param unit Units of position.
     */
    void setAxisPosition(const std::string& axis, double position, Units unit);
    /**
     * Gets position of translator's axis.
     * This method does not query device but returns value from translator's state.
     * @param axis Letter of the axis.
     * @param unit Units of position.
     * @return Position of translator's axis.
     */
    double getAxisPosition(const std::string& axis, Units unit);
    /**
     * Sets the home position of translator's axis.
     * This position is used by G28.
     * @param axis Letter of the axis.
     * @param position The home position.
     * @param unit Units of position.
     */
    void setAxisHomePosition(const std::string& axis, double position, Units unit);
    /**
     * Sets the secondary home position of translator's axis.
     * This position is used by G30.
     * @param axis Letter of the axis.
     * @param position The home position.
     * @param unit Units of position.
     */
    void setAxisSecondaryHomePosition(const std::string& axis, double position, Units unit);
    /**
     * Gets offset of an axis in a given coordinate system.
     * @param coordinateSystem Coordinate system (e.g. G54).
     * @param axis Letter of the axis.
     * @param unit Units of position.
     * @return Offset in translator units of the axis.
     */
    double getAxisCoordinateSystemOffset(const std::string& coordinateSystem, const std::string& axis, Units unit);
    /**
     * Resets internal state after device rejected generated command.
     * Axis positions become uninitialized.
     */
    void resetAfterStreamError();
    /**
     * Allows to scale feed rate of the translated code by a coefficient.
     * @param coefficient Coefficient of the original feed rate.
     */
    void setFeedRateOverride(double coefficient);
    /**
     * The ID of the translator that serves to identify native resources.
     */
    int getTranslatorId() const;
    /**
     * Current coordinate system.
     */
    std::string getCoordinateSystem() const;
protected:
    /**
     * Releases native resources of a translator.
     * @param translatorId The ID of the translator.
     */
    static void free(int translatorId);
    /**
     * Gets current coordinate system (e.g. G54).
     * @return Current coordinate system.
     */
    std::string getCurrentCoordinateSystem() const;
    int _translatorId;
public:
    OfflineTranslator(): _translatorId(-1) {}
    ~OfflineTranslator();
    OfflineTranslator(OfflineTranslator&& other) noexcept;
    OfflineTranslator& operator=(OfflineTranslator&& other) noexcept;
};


}  // Namespace gcode
}  // Namespace motion
}  // Namespace zaber
