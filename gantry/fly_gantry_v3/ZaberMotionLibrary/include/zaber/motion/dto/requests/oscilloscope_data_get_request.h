// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class OscilloscopeDataGetRequest: public Serializable {
public:
    int dataId {0};
    Units unit {Units::NATIVE};

    OscilloscopeDataGetRequest();

    OscilloscopeDataGetRequest(
        int p_dataId,
        Units p_unit
    );

    bool operator==(const OscilloscopeDataGetRequest& other) const;

    bool operator!=(const OscilloscopeDataGetRequest& other) const {
        return !(*this == other);
    }

    int getDataId() const;
    void setDataId(int p_dataId);

    Units getUnit() const;
    void setUnit(Units p_unit);

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
