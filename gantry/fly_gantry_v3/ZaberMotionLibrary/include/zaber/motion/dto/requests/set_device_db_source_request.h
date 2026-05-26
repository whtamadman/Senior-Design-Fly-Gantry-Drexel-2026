// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/device_db_source_type.h"

namespace zaber {
namespace motion {
namespace requests {

class SetDeviceDbSourceRequest: public Serializable {
public:
    DeviceDbSourceType sourceType {0};
    std::optional<std::string> urlOrFilePath;

    SetDeviceDbSourceRequest();

    SetDeviceDbSourceRequest(
        DeviceDbSourceType p_sourceType,
        std::optional<std::string> p_urlOrFilePath
    );

    SetDeviceDbSourceRequest(
        DeviceDbSourceType p_sourceType
    );

    bool operator==(const SetDeviceDbSourceRequest& other) const;

    bool operator!=(const SetDeviceDbSourceRequest& other) const {
        return !(*this == other);
    }

    /**
     * Whether the source is a web service or a local DB file.
     */
    DeviceDbSourceType const& getSourceType() const;
    void setSourceType(DeviceDbSourceType p_sourceType);

    /**
     * The URL of the web service or path to the local DB file.
     */
    std::optional<std::string> const& getUrlOrFilePath() const;
    void setUrlOrFilePath(std::optional<std::string> p_urlOrFilePath);

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
