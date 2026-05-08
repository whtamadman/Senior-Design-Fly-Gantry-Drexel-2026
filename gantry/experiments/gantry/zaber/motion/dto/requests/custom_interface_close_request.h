// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class CustomInterfaceCloseRequest: public Serializable {
public:
    int transportId {0};
    std::string errorMessage;

    CustomInterfaceCloseRequest();

    CustomInterfaceCloseRequest(
        int p_transportId,
        std::string p_errorMessage
    );

    bool operator==(const CustomInterfaceCloseRequest& other) const;

    bool operator!=(const CustomInterfaceCloseRequest& other) const {
        return !(*this == other);
    }

    int getTransportId() const;
    void setTransportId(int p_transportId);

    std::string const& getErrorMessage() const;
    void setErrorMessage(std::string p_errorMessage);

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
