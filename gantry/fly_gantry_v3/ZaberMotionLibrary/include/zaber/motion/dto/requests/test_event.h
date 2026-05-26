// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class TestEvent: public Serializable {
public:
    std::string data;

    TestEvent();

    TestEvent(
        std::string p_data
    );

    bool operator==(const TestEvent& other) const;

    bool operator!=(const TestEvent& other) const {
        return !(*this == other);
    }

    std::string const& getData() const;
    void setData(std::string p_data);

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
