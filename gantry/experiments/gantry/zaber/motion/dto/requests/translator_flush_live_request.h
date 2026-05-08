// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class TranslatorFlushLiveRequest: public Serializable {
public:
    int translatorId {0};
    bool waitUntilIdle {false};

    TranslatorFlushLiveRequest();

    TranslatorFlushLiveRequest(
        int p_translatorId,
        bool p_waitUntilIdle
    );

    bool operator==(const TranslatorFlushLiveRequest& other) const;

    bool operator!=(const TranslatorFlushLiveRequest& other) const {
        return !(*this == other);
    }

    int getTranslatorId() const;
    void setTranslatorId(int p_translatorId);

    bool getWaitUntilIdle() const;
    void setWaitUntilIdle(bool p_waitUntilIdle);

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
