// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Data representing a single point in a PVT sequence or buffer.
 */
class PvtPoint: public Serializable {
public:
    std::vector<Measurement> positions;
    std::vector<Measurement> velocities;
    Measurement time;
    bool relative {false};

    PvtPoint();

    PvtPoint(
        std::vector<Measurement> p_positions,
        std::vector<Measurement> p_velocities,
        Measurement p_time,
        bool p_relative
    );

    bool operator==(const PvtPoint& other) const;

    bool operator!=(const PvtPoint& other) const {
        return !(*this == other);
    }

    /**
     * Position of this point for all series (axes).
     */
    std::vector<Measurement> const& getPositions() const;
    void setPositions(std::vector<Measurement> p_positions);

    /**
     * Velocity at this point for all series (axes).
     */
    std::vector<Measurement> const& getVelocities() const;
    void setVelocities(std::vector<Measurement> p_velocities);

    /**
     * Time to take to reach this point from the previous point or starting position.
     */
    Measurement const& getTime() const;
    void setTime(Measurement p_time);

    /**
     * Flag indicating if this point's position is relative to the previous point or starting position.
     * Defaults to false, meaning absolute positioning.
     */
    bool getRelative() const;
    void setRelative(bool p_relative);

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

} // namespace ascii
} // namespace motion
} // namespace zaber
