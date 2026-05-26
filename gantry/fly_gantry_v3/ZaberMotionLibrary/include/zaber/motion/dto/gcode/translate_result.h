// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/gcode/translate_message.h"

namespace zaber {
namespace motion {
namespace gcode {

/**
 * Represents a result of a G-code block translation.
 */
class TranslateResult: public Serializable {
public:
    std::vector<std::string> commands;
    std::vector<TranslateMessage> warnings;

    TranslateResult();

    TranslateResult(
        std::vector<std::string> p_commands,
        std::vector<TranslateMessage> p_warnings
    );

    bool operator==(const TranslateResult& other) const;

    bool operator!=(const TranslateResult& other) const {
        return !(*this == other);
    }

    /**
     * Stream commands resulting from the block.
     */
    std::vector<std::string> const& getCommands() const;
    void setCommands(std::vector<std::string> p_commands);

    /**
     * Messages informing about unsupported codes and features.
     */
    std::vector<TranslateMessage> const& getWarnings() const;
    void setWarnings(std::vector<TranslateMessage> p_warnings);

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

} // namespace gcode
} // namespace motion
} // namespace zaber
