// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class OscilloscopeDataGetSampleTimeRequest: public Serializable {
public:
    int dataId {0};
    Units unit {Units::NATIVE};
    int index {0};

    OscilloscopeDataGetSampleTimeRequest();

    OscilloscopeDataGetSampleTimeRequest(
        int p_dataId,
        Units p_unit,
        int p_index
    );

    bool operator==(const OscilloscopeDataGetSampleTimeRequest& other) const;

    bool operator!=(const OscilloscopeDataGetSampleTimeRequest& other) const {
        return !(*this == other);
    }

    int getDataId() const;
    void setDataId(int p_dataId);

    Units getUnit() const;
    void setUnit(Units p_unit);

    int getIndex() const;
    void setIndex(int p_index);

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
