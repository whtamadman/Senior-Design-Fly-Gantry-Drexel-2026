// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class OscilloscopeDataIdentifier: public Serializable {
public:
    int dataId {0};

    OscilloscopeDataIdentifier();

    OscilloscopeDataIdentifier(
        int p_dataId
    );

    bool operator==(const OscilloscopeDataIdentifier& other) const;

    bool operator!=(const OscilloscopeDataIdentifier& other) const {
        return !(*this == other);
    }

    int getDataId() const;
    void setDataId(int p_dataId);

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
