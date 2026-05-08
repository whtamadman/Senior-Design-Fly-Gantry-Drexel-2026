// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace requests {

class WdiGenericRequest: public Serializable {
public:
    int interfaceId {0};
    int registerId {0};
    int size {0};
    int count {0};
    int offset {0};
    std::string registerBank;
    std::vector<int> data;

    WdiGenericRequest();

    WdiGenericRequest(
        int p_interfaceId,
        int p_registerId,
        int p_size,
        int p_count,
        int p_offset,
        std::string p_registerBank,
        std::vector<int> p_data
    );

    bool operator==(const WdiGenericRequest& other) const;

    bool operator!=(const WdiGenericRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getRegisterId() const;
    void setRegisterId(int p_registerId);

    int getSize() const;
    void setSize(int p_size);

    int getCount() const;
    void setCount(int p_count);

    int getOffset() const;
    void setOffset(int p_offset);

    std::string const& getRegisterBank() const;
    void setRegisterBank(std::string p_registerBank);

    std::vector<int> const& getData() const;
    void setData(std::vector<int> p_data);

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
