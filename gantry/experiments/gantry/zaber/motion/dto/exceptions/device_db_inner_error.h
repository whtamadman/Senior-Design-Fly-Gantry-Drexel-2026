// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/device_db_source_type.h"
#include "zaber/motion/dto/exceptions/device_db_inner_error.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * One of the errors that occurred while trying to access information from the device database.
 */
class DeviceDbInnerError: public Serializable {
public:
    std::string code;
    DeviceDbSourceType sourceType {0};
    std::string message;
    std::vector<DeviceDbInnerError> innerErrors;

    DeviceDbInnerError();

    DeviceDbInnerError(
        std::string p_code,
        DeviceDbSourceType p_sourceType,
        std::string p_message,
        std::vector<DeviceDbInnerError> p_innerErrors
    );

    bool operator==(const DeviceDbInnerError& other) const;

    bool operator!=(const DeviceDbInnerError& other) const {
        return !(*this == other);
    }

    /**
     * Code describing type of the error.
     */
    std::string const& getCode() const;
    void setCode(std::string p_code);

    /**
     * The type of database source that caused the error.
     */
    DeviceDbSourceType const& getSourceType() const;
    void setSourceType(DeviceDbSourceType p_sourceType);

    /**
     * Description of the error.
     */
    std::string const& getMessage() const;
    void setMessage(std::string p_message);

    /**
     * A list of errors that occurred while trying to access information from the device database.
     */
    std::vector<DeviceDbInnerError> const& getInnerErrors() const;
    void setInnerErrors(std::vector<DeviceDbInnerError> p_innerErrors);

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

} // namespace exceptions
} // namespace motion
} // namespace zaber
