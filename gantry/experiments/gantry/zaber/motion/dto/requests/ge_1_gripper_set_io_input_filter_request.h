// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperSetIoInputFilterRequest: public Serializable {
public:
    int connectionId {0};
    int duration {0};
    bool saveToFlash {false};

    Ge1GripperSetIoInputFilterRequest();

    Ge1GripperSetIoInputFilterRequest(
        int p_connectionId,
        int p_duration,
        bool p_saveToFlash
    );

    bool operator==(const Ge1GripperSetIoInputFilterRequest& other) const;

    bool operator!=(const Ge1GripperSetIoInputFilterRequest& other) const {
        return !(*this == other);
    }

    int getConnectionId() const;
    void setConnectionId(int p_connectionId);

    int getDuration() const;
    void setDuration(int p_duration);

    bool getSaveToFlash() const;
    void setSaveToFlash(bool p_saveToFlash);

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
