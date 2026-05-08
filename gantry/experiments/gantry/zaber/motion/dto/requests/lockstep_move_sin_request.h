// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class LockstepMoveSinRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int lockstepGroupId {0};
    double amplitude {0.0};
    Units amplitudeUnits {Units::NATIVE};
    double period {0.0};
    Units periodUnits {Units::NATIVE};
    double count {0.0};
    bool waitUntilIdle {false};

    LockstepMoveSinRequest();

    LockstepMoveSinRequest(
        int p_interfaceId,
        int p_device,
        int p_lockstepGroupId,
        double p_amplitude,
        Units p_amplitudeUnits,
        double p_period,
        Units p_periodUnits,
        double p_count,
        bool p_waitUntilIdle
    );

    bool operator==(const LockstepMoveSinRequest& other) const;

    bool operator!=(const LockstepMoveSinRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getLockstepGroupId() const;
    void setLockstepGroupId(int p_lockstepGroupId);

    double getAmplitude() const;
    void setAmplitude(double p_amplitude);

    Units getAmplitudeUnits() const;
    void setAmplitudeUnits(Units p_amplitudeUnits);

    double getPeriod() const;
    void setPeriod(double p_period);

    Units getPeriodUnits() const;
    void setPeriodUnits(Units p_periodUnits);

    double getCount() const;
    void setCount(double p_count);

    bool getWaitUntilIdle() const;
    void setWaitUntilIdle(bool p_waitUntilIdle);

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
