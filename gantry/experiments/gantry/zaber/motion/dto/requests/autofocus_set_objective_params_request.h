// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/named_parameter.h"

namespace zaber {
namespace motion {
namespace requests {

class AutofocusSetObjectiveParamsRequest: public Serializable {
public:
    int providerId {0};
    int interfaceId {0};
    int focusAddress {0};
    int focusAxis {0};
    int turretAddress {0};
    int objective {0};
    std::vector<NamedParameter> parameters;

    AutofocusSetObjectiveParamsRequest();

    AutofocusSetObjectiveParamsRequest(
        int p_providerId,
        int p_interfaceId,
        int p_focusAddress,
        int p_focusAxis,
        int p_turretAddress,
        int p_objective,
        std::vector<NamedParameter> p_parameters
    );

    bool operator==(const AutofocusSetObjectiveParamsRequest& other) const;

    bool operator!=(const AutofocusSetObjectiveParamsRequest& other) const {
        return !(*this == other);
    }

    int getProviderId() const;
    void setProviderId(int p_providerId);

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getFocusAddress() const;
    void setFocusAddress(int p_focusAddress);

    int getFocusAxis() const;
    void setFocusAxis(int p_focusAxis);

    int getTurretAddress() const;
    void setTurretAddress(int p_turretAddress);

    int getObjective() const;
    void setObjective(int p_objective);

    std::vector<NamedParameter> const& getParameters() const;
    void setParameters(std::vector<NamedParameter> p_parameters);

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
