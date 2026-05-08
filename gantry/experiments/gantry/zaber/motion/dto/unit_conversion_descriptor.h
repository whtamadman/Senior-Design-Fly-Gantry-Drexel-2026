// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <optional>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {

/**
 * Information about unit conversion.
 */
class UnitConversionDescriptor: public Serializable {
public:
    std::string dimension;
    std::string conversionFunction;
    double scale {0.0};
    std::optional<int> resolution;

    UnitConversionDescriptor();

    UnitConversionDescriptor(
        std::string p_dimension,
        std::string p_conversionFunction,
        double p_scale,
        std::optional<int> p_resolution
    );

    UnitConversionDescriptor(
        std::string p_dimension,
        std::string p_conversionFunction,
        double p_scale
    );

    bool operator==(const UnitConversionDescriptor& other) const;

    bool operator!=(const UnitConversionDescriptor& other) const {
        return !(*this == other);
    }

    /**
     * Name of the dimension being converted.
     */
    std::string const& getDimension() const;
    void setDimension(std::string p_dimension);

    /**
     * Internal name of conversion function used.
     */
    std::string const& getConversionFunction() const;
    void setConversionFunction(std::string p_conversionFunction);

    /**
     * Scale factor used in conversion, if applicable.
     */
    double getScale() const;
    void setScale(double p_scale);

    /**
     * Microstep resolution used in conversion, if applicable.
     */
    std::optional<int> getResolution() const;
    void setResolution(std::optional<int> p_resolution);

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

} // namespace motion
} // namespace zaber
