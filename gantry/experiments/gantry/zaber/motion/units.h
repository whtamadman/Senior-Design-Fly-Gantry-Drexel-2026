// ===== THIS FILE IS GENERATED FROM ZABER DEVICE DB ===== //
// ================= DO NOT EDIT DIRECTLY ================ //

#pragma once

#include <string>

namespace zaber { namespace motion {

    /**
     * Units used by various functions.
     */
    enum class Units {
        // Native Device Units
        NATIVE = 0,

        // Dimension: Length, unit: metres
        LENGTH_METRES = 1,

        // Dimension: Length, unit: centimetres
        LENGTH_CENTIMETRES = 2,

        // Dimension: Length, unit: millimetres
        LENGTH_MILLIMETRES = 3,

        // Dimension: Length, unit: micrometres
        LENGTH_MICROMETRES = 4,

        // Dimension: Length, unit: nanometres
        LENGTH_NANOMETRES = 5,

        // Dimension: Length, unit: inches
        LENGTH_INCHES = 6,

        // Dimension: Velocity, unit: metres per second
        VELOCITY_METRES_PER_SECOND = 7,

        // Dimension: Velocity, unit: centimetres per second
        VELOCITY_CENTIMETRES_PER_SECOND = 8,

        // Dimension: Velocity, unit: millimetres per second
        VELOCITY_MILLIMETRES_PER_SECOND = 9,

        // Dimension: Velocity, unit: micrometres per second
        VELOCITY_MICROMETRES_PER_SECOND = 10,

        // Dimension: Velocity, unit: nanometres per second
        VELOCITY_NANOMETRES_PER_SECOND = 11,

        // Dimension: Velocity, unit: inches per second
        VELOCITY_INCHES_PER_SECOND = 12,

        // Dimension: Acceleration, unit: metres per second squared
        ACCELERATION_METRES_PER_SECOND_SQUARED = 13,

        // Dimension: Acceleration, unit: centimetres per second squared
        ACCELERATION_CENTIMETRES_PER_SECOND_SQUARED = 14,

        // Dimension: Acceleration, unit: millimetres per second squared
        ACCELERATION_MILLIMETRES_PER_SECOND_SQUARED = 15,

        // Dimension: Acceleration, unit: micrometres per second squared
        ACCELERATION_MICROMETRES_PER_SECOND_SQUARED = 16,

        // Dimension: Acceleration, unit: nanometres per second squared
        ACCELERATION_NANOMETRES_PER_SECOND_SQUARED = 17,

        // Dimension: Acceleration, unit: inches per second squared
        ACCELERATION_INCHES_PER_SECOND_SQUARED = 18,

        // Dimension: Angle, unit: degrees
        ANGLE_DEGREES = 19,

        // Dimension: Angle, unit: radians
        ANGLE_RADIANS = 20,

        // Dimension: Angular Velocity, unit: degrees per second
        ANGULAR_VELOCITY_DEGREES_PER_SECOND = 21,

        // Dimension: Angular Velocity, unit: radians per second
        ANGULAR_VELOCITY_RADIANS_PER_SECOND = 22,

        // Dimension: Angular Acceleration, unit: degrees per second squared
        ANGULAR_ACCELERATION_DEGREES_PER_SECOND_SQUARED = 23,

        // Dimension: Angular Acceleration, unit: radians per second squared
        ANGULAR_ACCELERATION_RADIANS_PER_SECOND_SQUARED = 24,

        // Dimension: AC Electric Current, unit: amperes peak
        AC_ELECTRIC_CURRENT_AMPERES_PEAK = 25,

        // Dimension: AC Electric Current, unit: amperes RMS
        AC_ELECTRIC_CURRENT_AMPERES_RMS = 26,

        // Dimension: Percent, unit: percent
        PERCENT_PERCENT = 27,

        // Dimension: DC Electric Current, unit: amperes
        DC_ELECTRIC_CURRENT_AMPERES = 28,

        // Dimension: Force, unit: newtons
        FORCE_NEWTONS = 29,

        // Dimension: Force, unit: millinewtons
        FORCE_MILLINEWTONS = 30,

        // Dimension: Force, unit: pounds-force
        FORCE_POUNDS_FORCE = 31,

        // Dimension: Force, unit: kilonewtons
        FORCE_KILONEWTONS = 32,

        // Dimension: Time, unit: seconds
        TIME_SECONDS = 33,

        // Dimension: Time, unit: milliseconds
        TIME_MILLISECONDS = 34,

        // Dimension: Time, unit: microseconds
        TIME_MICROSECONDS = 35,

        // Dimension: Torque, unit: newton metres
        TORQUE_NEWTON_METRES = 36,

        // Dimension: Torque, unit: newton centimetres
        TORQUE_NEWTON_CENTIMETRES = 37,

        // Dimension: Torque, unit: pound-force-feet
        TORQUE_POUND_FORCE_FEET = 38,

        // Dimension: Torque, unit: ounce-force-inches
        TORQUE_OUNCE_FORCE_INCHES = 39,

        // Dimension: Inertia, unit: grams
        INERTIA_GRAMS = 40,

        // Dimension: Inertia, unit: kilograms
        INERTIA_KILOGRAMS = 41,

        // Dimension: Inertia, unit: milligrams
        INERTIA_MILLIGRAMS = 42,

        // Dimension: Inertia, unit: pounds
        INERTIA_POUNDS = 43,

        // Dimension: Inertia, unit: ounces
        INERTIA_OUNCES = 44,

        // Dimension: Rotational Inertia, unit: gram-square metre
        ROTATIONAL_INERTIA_GRAM_SQUARE_METRE = 45,

        // Dimension: Rotational Inertia, unit: kilogram-square metre
        ROTATIONAL_INERTIA_KILOGRAM_SQUARE_METRE = 46,

        // Dimension: Rotational Inertia, unit: pound-square-feet
        ROTATIONAL_INERTIA_POUND_SQUARE_FEET = 47,

        // Dimension: Rotational Inertia, unit: gram-square millimetre
        ROTATIONAL_INERTIA_GRAM_SQUARE_MILLIMETRE = 48,

        // Dimension: Force Constant, unit: newtons per amp
        FORCE_CONSTANT_NEWTONS_PER_AMP = 49,

        // Dimension: Force Constant, unit: millinewtons per amp
        FORCE_CONSTANT_MILLINEWTONS_PER_AMP = 50,

        // Dimension: Force Constant, unit: kilonewtons per amp
        FORCE_CONSTANT_KILONEWTONS_PER_AMP = 51,

        // Dimension: Force Constant, unit: pounds-force per amp
        FORCE_CONSTANT_POUNDS_FORCE_PER_AMP = 52,

        // Dimension: Torque Constant, unit: newton metres per amp
        TORQUE_CONSTANT_NEWTON_METRES_PER_AMP = 53,

        // Dimension: Torque Constant, unit: millinewton metres per amp
        TORQUE_CONSTANT_MILLINEWTON_METRES_PER_AMP = 54,

        // Dimension: Torque Constant, unit: kilonewton metres per amp
        TORQUE_CONSTANT_KILONEWTON_METRES_PER_AMP = 55,

        // Dimension: Torque Constant, unit: pound-force-feet per amp
        TORQUE_CONSTANT_POUND_FORCE_FEET_PER_AMP = 56,

        // Dimension: Voltage, unit: volts
        VOLTAGE_VOLTS = 57,

        // Dimension: Voltage, unit: millivolts
        VOLTAGE_MILLIVOLTS = 58,

        // Dimension: Voltage, unit: microvolts
        VOLTAGE_MICROVOLTS = 59,

        // Dimension: Current Controller Proportional Gain, unit: volts per amp
        CURRENT_CONTROLLER_PROPORTIONAL_GAIN_VOLTS_PER_AMP = 60,

        // Dimension: Current Controller Proportional Gain, unit: millivolts per amp
        CURRENT_CONTROLLER_PROPORTIONAL_GAIN_MILLIVOLTS_PER_AMP = 61,

        // Dimension: Current Controller Proportional Gain, unit: microvolts per amp
        CURRENT_CONTROLLER_PROPORTIONAL_GAIN_MICROVOLTS_PER_AMP = 62,

        // Dimension: Current Controller Integral Gain, unit: volts per amp per second
        CURRENT_CONTROLLER_INTEGRAL_GAIN_VOLTS_PER_AMP_PER_SECOND = 63,

        // Dimension: Current Controller Integral Gain, unit: millivolts per amp per second
        CURRENT_CONTROLLER_INTEGRAL_GAIN_MILLIVOLTS_PER_AMP_PER_SECOND = 64,

        // Dimension: Current Controller Integral Gain, unit: microvolts per amp per second
        CURRENT_CONTROLLER_INTEGRAL_GAIN_MICROVOLTS_PER_AMP_PER_SECOND = 65,

        // Dimension: Current Controller Derivative Gain, unit: volts second per amp
        CURRENT_CONTROLLER_DERIVATIVE_GAIN_VOLTS_SECOND_PER_AMP = 66,

        // Dimension: Current Controller Derivative Gain, unit: millivolts second per amp
        CURRENT_CONTROLLER_DERIVATIVE_GAIN_MILLIVOLTS_SECOND_PER_AMP = 67,

        // Dimension: Current Controller Derivative Gain, unit: microvolts second per amp
        CURRENT_CONTROLLER_DERIVATIVE_GAIN_MICROVOLTS_SECOND_PER_AMP = 68,

        // Dimension: Resistance, unit: kiloohms
        RESISTANCE_KILOOHMS = 69,

        // Dimension: Resistance, unit: ohms
        RESISTANCE_OHMS = 70,

        // Dimension: Resistance, unit: milliohms
        RESISTANCE_MILLIOHMS = 71,

        // Dimension: Resistance, unit: microohms
        RESISTANCE_MICROOHMS = 72,

        // Dimension: Resistance, unit: nanoohms
        RESISTANCE_NANOOHMS = 73,

        // Dimension: Inductance, unit: henries
        INDUCTANCE_HENRIES = 74,

        // Dimension: Inductance, unit: millihenries
        INDUCTANCE_MILLIHENRIES = 75,

        // Dimension: Inductance, unit: microhenries
        INDUCTANCE_MICROHENRIES = 76,

        // Dimension: Inductance, unit: nanohenries
        INDUCTANCE_NANOHENRIES = 77,

        // Dimension: Voltage Constant, unit: volt seconds per radian
        VOLTAGE_CONSTANT_VOLT_SECONDS_PER_RADIAN = 78,

        // Dimension: Voltage Constant, unit: millivolt seconds per radian
        VOLTAGE_CONSTANT_MILLIVOLT_SECONDS_PER_RADIAN = 79,

        // Dimension: Voltage Constant, unit: microvolt seconds per radian
        VOLTAGE_CONSTANT_MICROVOLT_SECONDS_PER_RADIAN = 80,

        // Dimension: Absolute Temperature, unit: degrees Celsius
        ABSOLUTE_TEMPERATURE_DEGREES_CELSIUS = 81,

        // Dimension: Absolute Temperature, unit: kelvins
        ABSOLUTE_TEMPERATURE_KELVINS = 82,

        // Dimension: Absolute Temperature, unit: degrees Fahrenheit
        ABSOLUTE_TEMPERATURE_DEGREES_FAHRENHEIT = 83,

        // Dimension: Absolute Temperature, unit: degrees Rankine
        ABSOLUTE_TEMPERATURE_DEGREES_RANKINE = 84,

        // Dimension: Relative Temperature, unit: degrees Celsius
        RELATIVE_TEMPERATURE_DEGREES_CELSIUS = 85,

        // Dimension: Relative Temperature, unit: kelvins
        RELATIVE_TEMPERATURE_KELVINS = 86,

        // Dimension: Relative Temperature, unit: degrees Fahrenheit
        RELATIVE_TEMPERATURE_DEGREES_FAHRENHEIT = 87,

        // Dimension: Relative Temperature, unit: degrees Rankine
        RELATIVE_TEMPERATURE_DEGREES_RANKINE = 88,

        // Dimension: Frequency, unit: gigahertz
        FREQUENCY_GIGAHERTZ = 89,

        // Dimension: Frequency, unit: megahertz
        FREQUENCY_MEGAHERTZ = 90,

        // Dimension: Frequency, unit: kilohertz
        FREQUENCY_KILOHERTZ = 91,

        // Dimension: Frequency, unit: hertz
        FREQUENCY_HERTZ = 92,

        // Dimension: Frequency, unit: millihertz
        FREQUENCY_MILLIHERTZ = 93,

        // Dimension: Frequency, unit: microhertz
        FREQUENCY_MICROHERTZ = 94,

        // Dimension: Frequency, unit: nanohertz
        FREQUENCY_NANOHERTZ = 95,

    };

    std::string getUnitLongName(Units unit);
    Units getLongNameUnit(std::string name);

}  // namespace motion
}  // namespace zaber
