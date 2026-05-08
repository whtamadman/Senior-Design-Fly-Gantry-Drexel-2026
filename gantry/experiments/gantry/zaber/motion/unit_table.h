// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/dto/unit_conversion_descriptor.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {


/**
 * Helper for working with units of measure.
 */
class UnitTable {
public:
    UnitTable() = delete;

    UnitTable(const UnitTable& other) = delete;
    UnitTable& operator=(const UnitTable& other) = delete;

    /**
     * Gets the standard symbol associated with a given unit.
     * @param unit Unit of measure.
     * @return Symbols corresponding to the given unit. Throws NoValueForKey if no symbol is defined.
     */
    static std::string getSymbol(Units unit);
    /**
     * Gets the unit enum value associated with a standard symbol.
     * Note not all units can be retrieved this way.
     * @param symbol Symbol to look up.
     * @return The unit enum value with the given symbols. Throws NoValueForKey if the symbol is not supported for lookup.
     */
    static Units getUnit(const std::string& symbol);
    /**
     * Converts a value from one unit to a different unit of the same dimension.
     * Note that this function does not support native unit conversions.
     * @param value The value to be converted.
     * @param fromUnit The unit which the value is being converted from.
     * @param toUnit The unit which the value is being converted to.
     * @return The converted value. Throws ConversionFailedException if unit is incompatible.
     */
    static double convertUnits(double value, Units fromUnit, Units toUnit);
    /**
     * Converts a value from one unit to native units given unit conversion descriptor.
     * @param conversion The unit conversion data retrieved from device or axis.
     * @param value The value to be converted.
     * @param fromUnit The unit which the value is being converted from.
     * @return The converted value. Throws ConversionFailedException if unit is incompatible.
     */
    static double convertToNativeUnits(const UnitConversionDescriptor& conversion, double value, Units fromUnit);
    /**
     * Converts a value from native units to the specified unit given unit conversion descriptor.
     * @param conversion The unit conversion data retrieved from device or axis.
     * @param value The value to be converted.
     * @param toUnit The unit which the value is being converted to.
     * @return The converted value. Throws ConversionFailedException if unit is incompatible.
     */
    static double convertFromNativeUnits(const UnitConversionDescriptor& conversion, double value, Units toUnit);
    /**
     * Converts values from one unit to native units given unit conversion descriptor.
     * @param conversion The unit conversion data retrieved from device or axis.
     * @param values The value to be converted.
     * @param fromUnit The unit which the value is being converted from.
     * @return The converted values. Throws ConversionFailedException if unit is incompatible.
     */
    static std::vector<double> convertToNativeUnitsBatch(const UnitConversionDescriptor& conversion, const std::vector<double>& values, Units fromUnit);
    /**
     * Converts values from native units to the specified unit given unit conversion descriptor.
     * @param conversion The unit conversion data retrieved from device or axis.
     * @param values The value to be converted.
     * @param toUnit The unit which the value is being converted to.
     * @return The converted values. Throws ConversionFailedException if unit is incompatible.
     */
    static std::vector<double> convertFromNativeUnitsBatch(const UnitConversionDescriptor& conversion, const std::vector<double>& values, Units toUnit);
protected:
};


}  // Namespace motion
}  // Namespace zaber
