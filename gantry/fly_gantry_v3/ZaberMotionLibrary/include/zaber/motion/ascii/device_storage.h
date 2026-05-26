// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <vector>
#include "zaber/motion/ascii/axis.h"
#include "zaber/motion/ascii/device.h"
#include "zaber/motion/units.h"

namespace zaber {
namespace motion {
namespace ascii {


/**
 * Class providing access to device storage.
 * Requires at least Firmware 7.30.
 */
class DeviceStorage {
public:
    struct SetStringOptions {
        // Whether the stored value should be base64 encoded before being stored.
        // This makes the string unreadable to humans using the ASCII protocol,
        // however, values stored this way can be of any length and use non-ASCII and protocol reserved characters.
        bool encode {false};
    };

    struct GetStringOptions {
        // Whether the stored value should be decoded.
        // Only use this when reading values set by storage.set with "encode" true.
        bool decode {false};
    };

    struct ListKeysOptions {
        // Optional key prefix.
        std::optional<std::string> prefix {};
    };

    DeviceStorage(Device device);

    /**
     * Sets the device value stored at the provided key.
     * @param key Key to set the value at.
     * @param value Value to set.
     * @param encode Whether the stored value should be base64 encoded before being stored.
     * This makes the string unreadable to humans using the ASCII protocol,
     * however, values stored this way can be of any length and use non-ASCII and protocol reserved characters.
     */
    void setString(const std::string& key, const std::string& value, bool encode = false);

    /**
     * Sets the device value stored at the provided key.
     * @param key Key to set the value at.
     * @param value Value to set.
     * @param options A struct of type SetStringOptions. It has the following members:
     * * `encode`: Whether the stored value should be base64 encoded before being stored.
     *   This makes the string unreadable to humans using the ASCII protocol,
     *   however, values stored this way can be of any length and use non-ASCII and protocol reserved characters.
     */
    void setString(const std::string& key, const std::string& value, const DeviceStorage::SetStringOptions& options);
    /**
     * Gets the device value stored with the provided key.
     * @param key Key to read the value of.
     * @param decode Whether the stored value should be decoded.
     * Only use this when reading values set by storage.set with "encode" true.
     * @return Stored value.
     */
    std::string getString(const std::string& key, bool decode = false);

    /**
     * Gets the device value stored with the provided key.
     * @param key Key to read the value of.
     * @param options A struct of type GetStringOptions. It has the following members:
     * * `decode`: Whether the stored value should be decoded.
     *   Only use this when reading values set by storage.set with "encode" true.
     * @return Stored value.
     */
    std::string getString(const std::string& key, const DeviceStorage::GetStringOptions& options);
    /**
     * Sets the value at the provided key to the provided number.
     * @param key Key to set the value at.
     * @param value Value to set.
     */
    void setNumber(const std::string& key, double value);
    /**
     * Gets the value at the provided key interpreted as a number.
     * @param key Key to get the value at.
     * @return Stored value.
     */
    double getNumber(const std::string& key);
    /**
     * Sets the value at the provided key to the provided boolean.
     * @param key Key to set the value at.
     * @param value Value to set.
     */
    void setBool(const std::string& key, bool value);
    /**
     * Gets the value at the provided key interpreted as a boolean.
     * @param key Key to get the value at.
     * @return Stored value.
     */
    bool getBool(const std::string& key);
    /**
     * Erases the device value stored at the provided key.
     * @param key Key to erase.
     * @return A boolean indicating if the key existed.
     */
    bool eraseKey(const std::string& key);
    /**
     * Lists the device storage keys matching a given prefix.
     * Omit the prefix to list all the keys.
     * @param prefix Optional key prefix.
     * @return Storage keys matching the given prefix.
     */
    std::vector<std::string> listKeys(const std::optional<std::string>& prefix = {});

    /**
     * Lists the device storage keys matching a given prefix.
     * Omit the prefix to list all the keys.
     * @param options A struct of type ListKeysOptions. It has the following members:
     * * `prefix`: Optional key prefix.
     * @return Storage keys matching the given prefix.
     */
    std::vector<std::string> listKeys(const DeviceStorage::ListKeysOptions& options);
    /**
     * Determines whether a given key exists in device storage.
     * @param key Key which existence to determine.
     * @return True indicating that the key exists, false otherwise.
     */
    bool keyExists(const std::string& key);
protected:
    Device getDevice() const;
    Device _device;
};


}  // Namespace ascii
}  // Namespace motion
}  // Namespace zaber
