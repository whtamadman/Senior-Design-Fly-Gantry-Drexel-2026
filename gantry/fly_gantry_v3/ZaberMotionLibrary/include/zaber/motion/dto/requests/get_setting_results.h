// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/get_setting_result.h"

namespace zaber {
namespace motion {
namespace requests {

class GetSettingResults: public Serializable {
public:
    std::vector<ascii::GetSettingResult> results;

    GetSettingResults();

    GetSettingResults(
        std::vector<ascii::GetSettingResult> p_results
    );

    bool operator==(const GetSettingResults& other) const;

    bool operator!=(const GetSettingResults& other) const {
        return !(*this == other);
    }

    std::vector<ascii::GetSettingResult> const& getResults() const;
    void setResults(std::vector<ascii::GetSettingResult> p_results);

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
