// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class TranslatorFlushResponse: public Serializable {
public:
    std::vector<std::string> commands;

    TranslatorFlushResponse();

    TranslatorFlushResponse(
        std::vector<std::string> p_commands
    );

    bool operator==(const TranslatorFlushResponse& other) const;

    bool operator!=(const TranslatorFlushResponse& other) const {
        return !(*this == other);
    }

    std::vector<std::string> const& getCommands() const;
    void setCommands(std::vector<std::string> p_commands);

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

} // namespace requests
} // namespace motion
} // namespace zaber
