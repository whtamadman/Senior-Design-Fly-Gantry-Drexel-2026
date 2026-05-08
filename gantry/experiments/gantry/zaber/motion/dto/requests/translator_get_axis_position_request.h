// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class TranslatorGetAxisPositionRequest: public Serializable {
public:
    int translatorId {0};
    std::string axis;
    Units unit {Units::NATIVE};

    TranslatorGetAxisPositionRequest();

    TranslatorGetAxisPositionRequest(
        int p_translatorId,
        std::string p_axis,
        Units p_unit
    );

    bool operator==(const TranslatorGetAxisPositionRequest& other) const;

    bool operator!=(const TranslatorGetAxisPositionRequest& other) const {
        return !(*this == other);
    }

    int getTranslatorId() const;
    void setTranslatorId(int p_translatorId);

    std::string const& getAxis() const;
    void setAxis(std::string p_axis);

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
