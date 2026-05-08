// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * The tuning of this axis represented by PID parameters.
 */
class PidTuning: public Serializable {
public:
    std::string type;
    int version {0};
    double p {0.0};
    double i {0.0};
    double d {0.0};
    double fc {0.0};

    PidTuning();

    PidTuning(
        std::string p_type,
        int p_version,
        double p_p,
        double p_i,
        double p_d,
        double p_fc
    );

    bool operator==(const PidTuning& other) const;

    bool operator!=(const PidTuning& other) const {
        return !(*this == other);
    }

    /**
     * The tuning algorithm used to tune this axis.
     */
    std::string const& getType() const;
    void setType(std::string p_type);

    /**
     * The version of the tuning algorithm used to tune this axis.
     */
    int getVersion() const;
    void setVersion(int p_version);

    /**
     * The positional tuning argument.
     */
    double getP() const;
    void setP(double p_p);

    /**
     * The integral tuning argument.
     */
    double getI() const;
    void setI(double p_i);

    /**
     * The derivative tuning argument.
     */
    double getD() const;
    void setD(double p_d);

    /**
     * The frequency cutoff for the tuning.
     */
    double getFc() const;
    void setFc(double p_fc);

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
