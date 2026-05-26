// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class UnitGetEnumRequest: public Serializable {
public:
    std::string symbol;

    UnitGetEnumRequest();

    UnitGetEnumRequest(
        std::string p_symbol
    );

    bool operator==(const UnitGetEnumRequest& other) const;

    bool operator!=(const UnitGetEnumRequest& other) const {
        return !(*this == other);
    }

    std::string const& getSymbol() const;
    void setSymbol(std::string p_symbol);

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
