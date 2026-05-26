// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>
#include <utility>
#include <vector>
#include "zaber/motion/dto/firmware_version.h"
#include "zaber/motion/dto/microscopy/wdi_autofocus_provider_status.h"

namespace zaber {
namespace motion {
namespace microscopy {

/**
 * Default port number for TCP connections to WDI autofocus.
 */
constexpr int DEFAULT_TCP_PORT = 27;


/**
 * Class representing access to WDI Autofocus connection.
 */
class WdiAutofocusProvider {
public:
    struct GenericReadOptions {
        // Number of values to read (defaults to 1).
        int count {1};
        // Offset within the register (defaults to 0).
        int offset {0};
        // Register bank letter (defaults to U for user bank).
        std::string registerBank {"U"};
    };

    struct GenericWriteOptions {
        // Offset within the register (defaults to 0).
        int offset {0};
        // Register bank letter (defaults to U for user bank).
        std::string registerBank {"U"};
    };

    struct GenericReadFloatOptions {
        // Number of values to read (defaults to 1).
        int count {1};
        // Offset within the register (defaults to 0).
        int offset {0};
        // Register bank letter (defaults to U for user bank).
        std::string registerBank {"U"};
    };

    struct GenericWriteFloatOptions {
        // Offset within the register (defaults to 0).
        int offset {0};
        // Register bank letter (defaults to U for user bank).
        std::string registerBank {"U"};
    };

    WdiAutofocusProvider(int providerId);

    /**
     * Opens a TCP connection to WDI autofocus.
     * @param hostName Hostname or IP address.
     * @param port Optional port number (defaults to 27).
     * @return An object representing the autofocus connection.
     */
    static WdiAutofocusProvider openTcp(const std::string& hostName, int port = DEFAULT_TCP_PORT);
    /**
     * Close the connection.
     */
    void close();
    /**
     * Generic read operation.
     * @param registerId Register address to read from.
     * @param size Data size to read. Valid values are (1,2,4). Determines the data type (Byte, Word, DWord).
     * @param count Number of values to read (defaults to 1).
     * @param offset Offset within the register (defaults to 0).
     * @param registerBank Register bank letter (defaults to U for user bank).
     * @return Array of integers read from the device.
     */
    std::vector<int> genericRead(int registerId, int size, int count = 1, int offset = 0, const std::string& registerBank = "U");

    /**
     * Generic read operation.
     * @param registerId Register address to read from.
     * @param size Data size to read. Valid values are (1,2,4). Determines the data type (Byte, Word, DWord).
     * @param options A struct of type GenericReadOptions. It has the following members:
     * * `count`: Number of values to read (defaults to 1).
     * * `offset`: Offset within the register (defaults to 0).
     * * `registerBank`: Register bank letter (defaults to U for user bank).
     * @return Array of integers read from the device.
     */
    std::vector<int> genericRead(int registerId, int size, const WdiAutofocusProvider::GenericReadOptions& options);
    /**
     * Generic write operation.
     * @param registerId Register address to write to.
     * @param size Data size to write. Valid values are (0,1,2,4). Determines the data type (Nil, Byte, Word, DWord).
     * @param data Array of values to write to the register. Empty array is allowed.
     * @param offset Offset within the register (defaults to 0).
     * @param registerBank Register bank letter (defaults to U for user bank).
     */
    void genericWrite(int registerId, int size = 0, const std::vector<int>& data = {}, int offset = 0, const std::string& registerBank = "U");

    /**
     * Generic write operation.
     * @param registerId Register address to write to.
     * @param size Data size to write. Valid values are (0,1,2,4). Determines the data type (Nil, Byte, Word, DWord).
     * @param data Array of values to write to the register. Empty array is allowed.
     * @param options A struct of type GenericWriteOptions. It has the following members:
     * * `offset`: Offset within the register (defaults to 0).
     * * `registerBank`: Register bank letter (defaults to U for user bank).
     */
    void genericWrite(int registerId, int size, const std::vector<int>& data, const WdiAutofocusProvider::GenericWriteOptions& options);
    /**
     * Generic read operation.
     * @param registerId Register address to read from.
     * @param count Number of values to read (defaults to 1).
     * @param offset Offset within the register (defaults to 0).
     * @param registerBank Register bank letter (defaults to U for user bank).
     * @return Array of floats read from the device.
     */
    std::vector<double> genericReadFloat(int registerId, int count = 1, int offset = 0, const std::string& registerBank = "U");

    /**
     * Generic read operation.
     * @param registerId Register address to read from.
     * @param options A struct of type GenericReadFloatOptions. It has the following members:
     * * `count`: Number of values to read (defaults to 1).
     * * `offset`: Offset within the register (defaults to 0).
     * * `registerBank`: Register bank letter (defaults to U for user bank).
     * @return Array of floats read from the device.
     */
    std::vector<double> genericReadFloat(int registerId, const WdiAutofocusProvider::GenericReadFloatOptions& options);
    /**
     * Generic write operation.
     * @param registerId Register address to write to.
     * @param data Array of values to write to the register. Empty array is allowed.
     * @param offset Offset within the register (defaults to 0).
     * @param registerBank Register bank letter (defaults to U for user bank).
     */
    void genericWriteFloat(int registerId, const std::vector<double>& data = {}, int offset = 0, const std::string& registerBank = "U");

    /**
     * Generic write operation.
     * @param registerId Register address to write to.
     * @param data Array of values to write to the register. Empty array is allowed.
     * @param options A struct of type GenericWriteFloatOptions. It has the following members:
     * * `offset`: Offset within the register (defaults to 0).
     * * `registerBank`: Register bank letter (defaults to U for user bank).
     */
    void genericWriteFloat(int registerId, const std::vector<double>& data, const WdiAutofocusProvider::GenericWriteFloatOptions& options);
    /**
     * Enables the laser.
     */
    void enableLaser();
    /**
     * Disables the laser.
     */
    void disableLaser();
    /**
     * Gets the status of the autofocus.
     * @return The status of the autofocus.
     */
    WdiAutofocusProviderStatus getStatus();
    /**
     * Returns a string that represents the autofocus connection.
     * @return A string that represents the connection.
     */
    std::string toString() const;
    /**
     * The ID identifies the autofocus with the underlying library.
     */
    int getProviderId() const;
    /**
     * The firmware version of the connected autofocus.
     */
    FirmwareVersion getFirmwareVersion() const;
protected:
    /**
     * Frees the connection.
     * @param providerId The ID of the connection to free.
     */
    static void free(int providerId);
    /**
     * Returns FW version.
     * @return Firmware version.
     */
    FirmwareVersion retrieveFirmwareVersion() const;
    int _providerId;
public:
    WdiAutofocusProvider(): _providerId(-1) {}
    ~WdiAutofocusProvider();
    WdiAutofocusProvider(WdiAutofocusProvider&& other) noexcept;
    WdiAutofocusProvider& operator=(WdiAutofocusProvider&& other) noexcept;
};


}  // Namespace microscopy
}  // Namespace motion
}  // Namespace zaber
