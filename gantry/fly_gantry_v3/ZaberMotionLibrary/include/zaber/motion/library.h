// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <optional>
#include <string>
#include <vector>
#include "zaber/motion/dto/device_db_source.h"
#include "zaber/motion/dto/device_db_source_type.h"
#include "zaber/motion/dto/log_output_mode.h"

namespace zaber {
namespace motion {


/**
 * Access class to general library information and configuration.
 */
class Library {
public:
    Library() = delete;

    /**
     * Sets library logging output.
     * @param mode Logging output mode.
     * @param filePath Path of the file to open.
     */
    static void setLogOutput(LogOutputMode mode, const std::optional<std::string>& filePath = {});
    /**
     * Sets source of Device DB data. Allows selection of a web service or a local file.
     * @param sourceType Source type.
     * @param urlOrFilePath URL of the web service or path to the local file.
     * Leave empty for the default URL of Zaber web service.
     */
    static void setDeviceDbSource(DeviceDbSourceType sourceType, const std::optional<std::string>& urlOrFilePath = {});
    /**
     * Sets a sequence of sources. When the library needs device information,
     * it will try each source in the order they are provided.
     * @param sources The list of sources the library will access data from.
     */
    static void setDeviceDbSources(const std::vector<DeviceDbSource>& sources);

    static void setDeviceDbSources(std::initializer_list<DeviceDbSource> sources);

    template<
        typename TIterator,
        typename = std::enable_if_t<
            std::is_base_of_v<
                std::input_iterator_tag,
                typename std::iterator_traits<TIterator>::iterator_category>>>
    static void setDeviceDbSources(TIterator begin, TIterator end) {
        return setDeviceDbSources(std::vector<DeviceDbSource>(begin,end));
    }

    template<typename... T>
    static void setDeviceDbSources(T&&... sources) {
        return setDeviceDbSources({std::forward<T>(sources)...});
    }
    /**
     * Enables Device DB store.
     * The store uses filesystem to save information obtained from the Device DB.
     * The stored data are later used instead of the Device DB.
     * @param storeLocation Specifies relative or absolute path of the folder used by the store.
     * If left empty defaults to a folder in user home directory.
     * Must be accessible by the process.
     */
    static void enableDeviceDbStore(const std::optional<std::string>& storeLocation = {});
    /**
     * Disables Device DB store.
     */
    static void disableDeviceDbStore();
    /**
     * Checks if the Device DB store is currently enabled.
     * @return True if the Device DB store is enabled.
     */
    static bool isDeviceDbStoreEnabled();
    /**
     * Clears the Device DB store on the local filesystem.
     * Note: If the device DB was enabled with a custom store location, store files will be removed in that location.
     */
    static void clearDeviceDbStore();
    /**
     * Disables certain customer checks (like FF flag).
     * @param mode Whether to turn internal mode on or off.
     */
    static void setInternalMode(bool mode);
    /**
     * Sets the period between polling for IDLE during movements.
     * Caution: Setting the period too low may cause performance issues.
     * @param period Period in milliseconds.
     * Negative value restores the default period.
     */
    static void setIdlePollingPeriod(int period);
    /**
     * Deprecated: Calling this function is no longer necessary as the check happens automatically.
     *
     * Throws an error if the version of the loaded shared library does not match the caller's version.
     */
    static void checkVersion();
    /**
     * For internal use only: tells zaber motion core which host application it is bundled in.
     * @param hostApplication String name of the host application with which ZML is bundled.
     */
    static void setHostApplication(const std::string& hostApplication);
protected:
};


}  // Namespace motion
}  // Namespace zaber
