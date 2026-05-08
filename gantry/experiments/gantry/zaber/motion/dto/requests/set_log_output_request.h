// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/log_output_mode.h"

namespace zaber {
namespace motion {
namespace requests {

class SetLogOutputRequest: public Serializable {
public:
    LogOutputMode mode {0};
    std::optional<std::string> filePath;

    SetLogOutputRequest();

    SetLogOutputRequest(
        LogOutputMode p_mode,
        std::optional<std::string> p_filePath
    );

    SetLogOutputRequest(
        LogOutputMode p_mode
    );

    bool operator==(const SetLogOutputRequest& other) const;

    bool operator!=(const SetLogOutputRequest& other) const {
        return !(*this == other);
    }

    LogOutputMode const& getMode() const;
    void setMode(LogOutputMode p_mode);

    std::optional<std::string> const& getFilePath() const;
    void setFilePath(std::optional<std::string> p_filePath);

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
