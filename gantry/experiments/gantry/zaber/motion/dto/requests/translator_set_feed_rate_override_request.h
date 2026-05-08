// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class TranslatorSetFeedRateOverrideRequest: public Serializable {
public:
    int translatorId {0};
    double coefficient {0.0};

    TranslatorSetFeedRateOverrideRequest();

    TranslatorSetFeedRateOverrideRequest(
        int p_translatorId,
        double p_coefficient
    );

    bool operator==(const TranslatorSetFeedRateOverrideRequest& other) const;

    bool operator!=(const TranslatorSetFeedRateOverrideRequest& other) const {
        return !(*this == other);
    }

    int getTranslatorId() const;
    void setTranslatorId(int p_translatorId);

    double getCoefficient() const;
    void setCoefficient(double p_coefficient);

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
