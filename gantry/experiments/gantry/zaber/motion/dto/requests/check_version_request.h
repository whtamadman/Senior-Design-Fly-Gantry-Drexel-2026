// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class CheckVersionRequest: public Serializable {
public:
    std::string version;
    std::string host;

    CheckVersionRequest();

    CheckVersionRequest(
        std::string p_version,
        std::string p_host
    );

    bool operator==(const CheckVersionRequest& other) const;

    bool operator!=(const CheckVersionRequest& other) const {
        return !(*this == other);
    }

    std::string const& getVersion() const;
    void setVersion(std::string p_version);

    std::string const& getHost() const;
    void setHost(std::string p_host);

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
