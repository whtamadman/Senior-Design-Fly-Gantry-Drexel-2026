// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Contains invalid PVT points for PvtExecutionException.
 */
class InvalidPvtPoint: public Serializable {
public:
    int index {0};
    std::string point;

    InvalidPvtPoint();

    InvalidPvtPoint(
        int p_index,
        std::string p_point
    );

    bool operator==(const InvalidPvtPoint& other) const;

    bool operator!=(const InvalidPvtPoint& other) const {
        return !(*this == other);
    }

    /**
     * Index of the point numbered from the last submitted point.
     */
    int getIndex() const;
    void setIndex(int p_index);

    /**
     * The textual representation of the point.
     */
    std::string const& getPoint() const;
    void setPoint(std::string p_point);

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

} // namespace exceptions
} // namespace motion
} // namespace zaber
