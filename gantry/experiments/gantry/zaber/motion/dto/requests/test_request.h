// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class TestRequest: public Serializable {
public:
    bool returnError {false};
    std::string dataPing;
    bool returnErrorWithData {false};

    TestRequest();

    TestRequest(
        bool p_returnError,
        std::string p_dataPing,
        bool p_returnErrorWithData
    );

    bool operator==(const TestRequest& other) const;

    bool operator!=(const TestRequest& other) const {
        return !(*this == other);
    }

    bool getReturnError() const;
    void setReturnError(bool p_returnError);

    std::string const& getDataPing() const;
    void setDataPing(std::string p_dataPing);

    bool getReturnErrorWithData() const;
    void setReturnErrorWithData(bool p_returnErrorWithData);

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
