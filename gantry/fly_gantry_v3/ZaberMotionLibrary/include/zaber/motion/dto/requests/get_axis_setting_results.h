// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/get_axis_setting_result.h"

namespace zaber {
namespace motion {
namespace requests {

class GetAxisSettingResults: public Serializable {
public:
    std::vector<ascii::GetAxisSettingResult> results;

    GetAxisSettingResults();

    GetAxisSettingResults(
        std::vector<ascii::GetAxisSettingResult> p_results
    );

    bool operator==(const GetAxisSettingResults& other) const;

    bool operator!=(const GetAxisSettingResults& other) const {
        return !(*this == other);
    }

    std::vector<ascii::GetAxisSettingResult> const& getResults() const;
    void setResults(std::vector<ascii::GetAxisSettingResult> p_results);

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
