// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace gcode {

/**
 * Maps a translator axis to a Zaber stream axis.
 */
class AxisMapping: public Serializable {
public:
    std::string axisLetter;
    int axisIndex {0};

    AxisMapping();

    AxisMapping(
        std::string p_axisLetter,
        int p_axisIndex
    );

    bool operator==(const AxisMapping& other) const;

    bool operator!=(const AxisMapping& other) const {
        return !(*this == other);
    }

    /**
     * Letter of the translator axis (X,Y,Z,A,B,C,E).
     */
    std::string const& getAxisLetter() const;
    void setAxisLetter(std::string p_axisLetter);

    /**
     * Index of the stream axis.
     */
    int getAxisIndex() const;
    void setAxisIndex(int p_axisIndex);

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

} // namespace gcode
} // namespace motion
} // namespace zaber
