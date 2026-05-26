// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class PvtLoadCsvRequest: public Serializable {
public:
    std::string path;

    PvtLoadCsvRequest();

    PvtLoadCsvRequest(
        std::string p_path
    );

    bool operator==(const PvtLoadCsvRequest& other) const;

    bool operator!=(const PvtLoadCsvRequest& other) const {
        return !(*this == other);
    }

    std::string const& getPath() const;
    void setPath(std::string p_path);

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
