// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class TranslatorTranslateRequest: public Serializable {
public:
    int translatorId {0};
    std::string block;

    TranslatorTranslateRequest();

    TranslatorTranslateRequest(
        int p_translatorId,
        std::string p_block
    );

    bool operator==(const TranslatorTranslateRequest& other) const;

    bool operator!=(const TranslatorTranslateRequest& other) const {
        return !(*this == other);
    }

    int getTranslatorId() const;
    void setTranslatorId(int p_translatorId);

    std::string const& getBlock() const;
    void setBlock(std::string p_block);

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
