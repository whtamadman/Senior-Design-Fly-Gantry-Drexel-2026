// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class Ge1GripperSetPresetRequest: public Serializable {
public:
    int connectionId {0};
    int presetNumber {0};
    double position {0.0};
    int force {0};
    int speed {0};
    bool saveToFlash {false};

    Ge1GripperSetPresetRequest();

    Ge1GripperSetPresetRequest(
        int p_connectionId,
        int p_presetNumber,
        double p_position,
        int p_force,
        int p_speed,
        bool p_saveToFlash
    );

    bool operator==(const Ge1GripperSetPresetRequest& other) const;

    bool operator!=(const Ge1GripperSetPresetRequest& other) const {
        return !(*this == other);
    }

    int getConnectionId() const;
    void setConnectionId(int p_connectionId);

    int getPresetNumber() const;
    void setPresetNumber(int p_presetNumber);

    double getPosition() const;
    void setPosition(double p_position);

    int getForce() const;
    void setForce(int p_force);

    int getSpeed() const;
    void setSpeed(int p_speed);

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
