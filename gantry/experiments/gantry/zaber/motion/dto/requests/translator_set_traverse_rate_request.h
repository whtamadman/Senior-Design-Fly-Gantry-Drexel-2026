// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace requests {

class TranslatorSetTraverseRateRequest: public Serializable {
public:
    int translatorId {0};
    double traverseRate {0.0};
    Units unit {Units::NATIVE};

    TranslatorSetTraverseRateRequest();

    TranslatorSetTraverseRateRequest(
        int p_translatorId,
        double p_traverseRate,
        Units p_unit
    );

    bool operator==(const TranslatorSetTraverseRateRequest& other) const;

    bool operator!=(const TranslatorSetTraverseRateRequest& other) const {
        return !(*this == other);
    }

    int getTranslatorId() const;
    void setTranslatorId(int p_translatorId);

    double getTraverseRate() const;
    void setTraverseRate(double p_traverseRate);

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
