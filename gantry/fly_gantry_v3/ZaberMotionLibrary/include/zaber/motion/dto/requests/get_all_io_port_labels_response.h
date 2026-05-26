// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/io_port_label.h"

namespace zaber {
namespace motion {
namespace requests {

class GetAllIoPortLabelsResponse: public Serializable {
public:
    std::vector<ascii::IoPortLabel> labels;

    GetAllIoPortLabelsResponse();

    GetAllIoPortLabelsResponse(
        std::vector<ascii::IoPortLabel> p_labels
    );

    bool operator==(const GetAllIoPortLabelsResponse& other) const;

    bool operator!=(const GetAllIoPortLabelsResponse& other) const {
        return !(*this == other);
    }

    std::vector<ascii::IoPortLabel> const& getLabels() const;
    void setLabels(std::vector<ascii::IoPortLabel> p_labels);

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
