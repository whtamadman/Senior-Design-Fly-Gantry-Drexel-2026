// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/microscopy/third_party_components.h"

namespace zaber {
namespace motion {
namespace requests {

class MicroscopeFindRequest: public Serializable {
public:
    int interfaceId {0};
    std::optional<microscopy::ThirdPartyComponents> thirdParty;

    MicroscopeFindRequest();

    MicroscopeFindRequest(
        int p_interfaceId,
        std::optional<microscopy::ThirdPartyComponents> p_thirdParty
    );

    MicroscopeFindRequest(
        int p_interfaceId
    );

    bool operator==(const MicroscopeFindRequest& other) const;

    bool operator!=(const MicroscopeFindRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    std::optional<microscopy::ThirdPartyComponents> const& getThirdParty() const;
    void setThirdParty(std::optional<microscopy::ThirdPartyComponents> p_thirdParty);

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
