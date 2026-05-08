// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/servo_tuning_param.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * The raw parameters currently saved to a given paramset.
 */
class ParamsetInfo: public Serializable {
public:
    std::string type;
    int version {0};
    std::vector<ServoTuningParam> params;

    ParamsetInfo();

    ParamsetInfo(
        std::string p_type,
        int p_version,
        std::vector<ServoTuningParam> p_params
    );

    bool operator==(const ParamsetInfo& other) const;

    bool operator!=(const ParamsetInfo& other) const {
        return !(*this == other);
    }

    /**
     * The tuning algorithm used for this axis.
     */
    std::string const& getType() const;
    void setType(std::string p_type);

    /**
     * The version of the tuning algorithm used for this axis.
     */
    int getVersion() const;
    void setVersion(int p_version);

    /**
     * The raw tuning parameters of this device.
     */
    std::vector<ServoTuningParam> const& getParams() const;
    void setParams(std::vector<ServoTuningParam> p_params);

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

} // namespace ascii
} // namespace motion
} // namespace zaber
