// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class PvtBufferGetSequenceDataRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int bufferNumber {0};

    PvtBufferGetSequenceDataRequest();

    PvtBufferGetSequenceDataRequest(
        int p_interfaceId,
        int p_device,
        int p_bufferNumber
    );

    bool operator==(const PvtBufferGetSequenceDataRequest& other) const;

    bool operator!=(const PvtBufferGetSequenceDataRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getBufferNumber() const;
    void setBufferNumber(int p_bufferNumber);

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
