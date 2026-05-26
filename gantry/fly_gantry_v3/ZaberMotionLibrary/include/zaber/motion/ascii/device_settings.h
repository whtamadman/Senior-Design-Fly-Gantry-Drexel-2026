// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/dto/ascii/get_setting.h"
#include "zaber/motion/dto/ascii/get_setting_result.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {


/**
 * Class providing access to various device settings and properties.
 */
class DeviceSettings {
public:
    DeviceSettings(Device device);

    /**
     * Returns any device setting or property.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_settings).
     * @param setting Name of the setting.
     * @param unit Units of setting.
     * @return Setting value.
     */
    double get(const std::string& setting, Units unit = Units::NATIVE);
    /**
     * Sets any device setting.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_settings).
     * @param setting Name of the setting.
     * @param value Value of the setting.
     * @param unit Units of setting.
     */
    void set(const std::string& setting, double value, Units unit = Units::NATIVE);
    /**
     * Returns any device setting or property as a string.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_settings).
     * @param setting Name of the setting.
     * @return Setting value.
     */
    std::string getString(const std::string& setting);
    /**
     * Sets any device setting as a string.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_settings).
     * @param setting Name of the setting.
     * @param value Value of the setting.
     */
    void setString(const std::string& setting, const std::string& value);
    /**
     * Returns any device setting or property as an integer.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_settings).
     * @param setting Name of the setting.
     * @return Setting value.
     */
    int64_t getInt(const std::string& setting);
    /**
     * Sets any device setting or property as an integer.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_settings).
     * @param setting Name of the setting.
     * @param value Value of the setting.
     */
    void setInt(const std::string& setting, const int64_t& value);
    /**
     * Returns any device setting or property as a boolean.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_settings).
     * @param setting Name of the setting.
     * @return Setting value.
     */
    bool getBool(const std::string& setting);
    /**
     * Sets any device setting as a boolean.
     * For more information refer to the [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_settings).
     * @param setting Name of the setting.
     * @param value Value of the setting.
     */
    void setBool(const std::string& setting, bool value);
    /**
     * Convert arbitrary setting value to Zaber native units.
     * @param setting Name of the setting.
     * @param value Value of the setting in units specified by following argument.
     * @param unit Units of the value.
     * @return Setting value.
     */
    double convertToNativeUnits(const std::string& setting, double value, Units unit);
    /**
     * Convert arbitrary setting value from Zaber native units.
     * @param setting Name of the setting.
     * @param value Value of the setting in Zaber native units.
     * @param unit Units to convert value to.
     * @return Setting value.
     */
    double convertFromNativeUnits(const std::string& setting, double value, Units unit);
    /**
     * Returns the default value of a setting.
     * @param setting Name of the setting.
     * @param unit Units of setting.
     * @return Default setting value.
     */
    double getDefault(const std::string& setting, Units unit = Units::NATIVE);
    /**
     * Returns the default value of a setting as a string.
     * @param setting Name of the setting.
     * @return Default setting value.
     */
    std::string getDefaultString(const std::string& setting);
    /**
     * Returns the default value of a setting as an integer.
     * @param setting Name of the setting.
     * @return Default setting value.
     */
    int64_t getDefaultInt(const std::string& setting);
    /**
     * Returns the default value of a setting as a boolean.
     * @param setting Name of the setting.
     * @return Default setting value.
     */
    bool getDefaultBool(const std::string& setting);
    /**
     * Indicates if given setting can be converted from and to native units.
     * @param setting Name of the setting.
     * @return True if unit conversion can be performed.
     */
    bool canConvertNativeUnits(const std::string& setting);
    /**
     * Retrieves unit conversion descriptor for a setting, allowing unit conversion without a device.
     * The descriptor can be used with the ConvertTo/FromNativeUnits methods of the UnitTable class.
     * @param setting Name of the setting.
     * @return The unit conversion descriptor for the setting.
     */
    UnitConversionDescriptor getUnitConversionDescriptor(const std::string& setting);
    /**
     * Gets the value of an axis scope setting for each axis on the device.
     * Values may be NaN where the setting is not applicable.
     * @param setting Name of the setting.
     * @return The setting values on each axis.
     */
    std::vector<double> getFromAllAxes(const std::string& setting);
    /**
     * Gets many setting values in as few device requests as possible.
     * @param settings The settings to read.
     * @return The setting values read.
     */
    std::vector<GetSettingResult> getMany(const std::vector<GetSetting>& settings);

    std::vector<GetSettingResult> getMany(std::initializer_list<GetSetting> settings);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    std::vector<GetSettingResult> getMany(TIterator begin, TIterator end) {
        return getMany(std::vector<GetSetting>(begin,end));
    }

    template<typename... T>
    std::vector<GetSettingResult> getMany(T&&... settings) {
        return getMany({std::forward<T>(settings)...});
    }
    /**
     * Gets many setting values in the same tick, ensuring their values are synchronized.
     * Requires at least Firmware 7.35.
     * @param settings The settings to read.
     * @return The setting values read.
     */
    std::vector<GetSettingResult> getSynchronized(const std::vector<GetSetting>& settings);

    std::vector<GetSettingResult> getSynchronized(std::initializer_list<GetSetting> settings);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    std::vector<GetSettingResult> getSynchronized(TIterator begin, TIterator end) {
        return getSynchronized(std::vector<GetSetting>(begin,end));
    }

    template<typename... T>
    std::vector<GetSettingResult> getSynchronized(T&&... settings) {
        return getSynchronized({std::forward<T>(settings)...});
    }
protected:
    Device getDevice() const;
    Device _device;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
