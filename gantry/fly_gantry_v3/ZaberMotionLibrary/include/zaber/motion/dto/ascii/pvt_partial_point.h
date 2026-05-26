// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <optional>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * Data representing a single point in a PVT sequence or buffer with optional members.
 * This is used to represent sequences with missing columns such as velocity or time.
 * The data must be completed using the PvtSequence.Generate... methods before it can be sent to a device.
 */
class PvtPartialPoint: public Serializable {
public:
    std::vector<std::optional<Measurement>> positions;
    std::vector<std::optional<Measurement>> velocities;
    std::optional<Measurement> time;
    std::optional<bool> relative;

    PvtPartialPoint();

    PvtPartialPoint(
        std::vector<std::optional<Measurement>> p_positions,
        std::vector<std::optional<Measurement>> p_velocities,
        std::optional<Measurement> p_time,
        std::optional<bool> p_relative
    );

    PvtPartialPoint(
        std::vector<std::optional<Measurement>> p_positions,
        std::vector<std::optional<Measurement>> p_velocities
    );

    bool operator==(const PvtPartialPoint& other) const;

    bool operator!=(const PvtPartialPoint& other) const {
        return !(*this == other);
    }

    /**
     * Position of this point for all series (axes).
     */
    std::vector<std::optional<Measurement>> const& getPositions() const;
    void setPositions(std::vector<std::optional<Measurement>> p_positions);

    /**
     * Velocity at this point for all series (axes).
     */
    std::vector<std::optional<Measurement>> const& getVelocities() const;
    void setVelocities(std::vector<std::optional<Measurement>> p_velocities);

    /**
     * Time to take to reach this point from the previous point or starting position.
     */
    std::optional<Measurement> const& getTime() const;
    void setTime(std::optional<Measurement> p_time);

    /**
     * Flag indicating if this point's position is relative to the previous point or starting position.
     * Defaults to false, meaning absolute positioning.
     */
    std::optional<bool> getRelative() const;
    void setRelative(std::optional<bool> p_relative);

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
