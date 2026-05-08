// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperSetAutoHomeRequest: public Serializable {
public:
    int connectionId {0};
    bool enabled {false};
    bool saveToFlash {false};

    Ge1GripperSetAutoHomeRequest();

    Ge1GripperSetAutoHomeRequest(
        int p_connectionId,
        bool p_enabled,
        bool p_saveToFlash
    );

    bool operator==(const Ge1GripperSetAutoHomeRequest& other) const;

    bool operator!=(const Ge1GripperSetAutoHomeRequest& other) const {
        return !(*this == other);
    }

    int getConnectionId() const;
    void setConnectionId(int p_connectionId);

    bool getEnabled() const;
    void setEnabled(bool p_enabled);

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
