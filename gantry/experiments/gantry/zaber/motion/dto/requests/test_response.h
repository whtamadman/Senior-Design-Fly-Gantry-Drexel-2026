// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class TestResponse: public Serializable {
public:
    std::string dataPong;

    TestResponse();

    TestResponse(
        std::string p_dataPong
    );

    bool operator==(const TestResponse& other) const;

    bool operator!=(const TestResponse& other) const {
        return !(*this == other);
    }

    std::string const& getDataPong() const;
    void setDataPong(std::string p_dataPong);

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
