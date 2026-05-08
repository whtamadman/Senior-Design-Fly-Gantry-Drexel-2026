// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class TestRequestComplex: public Serializable {
public:
    std::vector<int> intArray;

    TestRequestComplex();

    TestRequestComplex(
        std::vector<int> p_intArray
    );

    bool operator==(const TestRequestComplex& other) const;

    bool operator!=(const TestRequestComplex& other) const {
        return !(*this == other);
    }

    std::vector<int> const& getIntArray() const;
    void setIntArray(std::vector<int> p_intArray);

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
