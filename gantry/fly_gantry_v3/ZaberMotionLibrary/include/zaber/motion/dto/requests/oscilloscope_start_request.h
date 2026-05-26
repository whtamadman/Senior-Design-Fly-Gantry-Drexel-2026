// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class OscilloscopeStartRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int captureLength {0};

    OscilloscopeStartRequest();

    OscilloscopeStartRequest(
        int p_interfaceId,
        int p_device,
        int p_captureLength
    );

    bool operator==(const OscilloscopeStartRequest& other) const;

    bool operator!=(const OscilloscopeStartRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getCaptureLength() const;
    void setCaptureLength(int p_captureLength);

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
