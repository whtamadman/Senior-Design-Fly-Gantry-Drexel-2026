// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class StreamBufferList: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    bool pvt {false};

    StreamBufferList();

    StreamBufferList(
        int p_interfaceId,
        int p_device,
        bool p_pvt
    );

    bool operator==(const StreamBufferList& other) const;

    bool operator!=(const StreamBufferList& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    bool getPvt() const;
    void setPvt(bool p_pvt);

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
