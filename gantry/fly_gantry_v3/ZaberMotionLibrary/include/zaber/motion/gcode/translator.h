// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <initializer_list>
#include <string>
#include <utility>
#include <vector>
#include "zaber/motion/ascii/stream.h"
#include "zaber/motion/dto/gcode/translate_result.h"
#include "zaber/motion/dto/gcode/translator_config.h"
#include "zaber/motion/units.h"

namespace zaber { namespace motion { namespace ascii {
    class Stream;
}}}

namespace zaber {
namespace motion {
namespace gcode {


/**
 * Represents a live G-Code translator.
 * It allows to stream G-Code blocks to a connected device.
 * It requires a stream to be setup on the device.
 * Requires at least Firmware 7.11.
 */
class Translator {
    using Stream = zaber::motion::ascii::Stream;

public:
    struct FlushOptions {
        // Determines whether to wait for the stream to finish all the movements.
        bool waitUntilIdle {true};
    };

    Translator(int translatorId);

    Translator(const Translator& other) = delete;
    Translator& operator=(const Translator& other) = delete;

    /**
     * Sets up the translator on top of a provided stream.
     * @param stream The stream to setup the translator on.
     * The stream must be already setup in a live or a store mode.
     * @param config Configuration of the translator.
     * @return New instance of translator.
     */
    static Translator setup(const Stream& stream, const std::optional<TranslatorConfig>& config = {});
    /**
     * Translates a single block (line) of G-code.
     * The commands are queued in the underlying stream to ensure smooth continues movement.
     * Returning of this method indicates that the commands are queued (not necessarily executed).
     * @param block Block (line) of G-code.
     * @return Result of translation containing the commands sent to the device.
     */
    TranslateResult translate(const std::string& block);
    /**
     * Flushes the remaining stream commands waiting in optimization buffer into the underlying stream.
     * The flush is also performed by M2 and M30 codes.
     * @param waitUntilIdle Determines whether to wait for the stream to finish all the movements.
     * @return The remaining stream commands.
     */
    std::vector<std::string> flush(bool waitUntilIdle = true);

    /**
     * Flushes the remaining stream commands waiting in optimization buffer into the underlying stream.
     * The flush is also performed by M2 and M30 codes.
     * @param options A struct of type FlushOptions. It has the following members:
     * * `waitUntilIdle`: Determines whether to wait for the stream to finish all the movements.
     * @return The remaining stream commands.
     */
    std::vector<std::string> flush(const Translator::FlushOptions& options);
    /**
     * Resets position of the translator from the underlying stream.
     * Call this method after performing a movement outside of translator.
     */
    void resetPosition();
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
    Translator(): _translatorId(-1) {}
    ~Translator();
    Translator(Translator&& other) noexcept;
    Translator& operator=(Translator&& other) noexcept;
};


}  // Namespace gcode
}  // Namespace motion
}  // Namespace zaber
