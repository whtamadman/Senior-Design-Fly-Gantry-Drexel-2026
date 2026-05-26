// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/oscilloscope_data_source.h"
#include "zaber/motion/dto/ascii/io_port_type.h"

namespace zaber {
namespace motion {
namespace ascii {

/**
 * The public properties of one channel of recorded oscilloscope data.
 */
class OscilloscopeCaptureProperties: public Serializable {
public:
    OscilloscopeDataSource dataSource {0};
    std::string setting;
    int axisNumber {0};
    IoPortType ioType {0};
    int ioChannel {0};

    OscilloscopeCaptureProperties();

    OscilloscopeCaptureProperties(
        OscilloscopeDataSource p_dataSource,
        std::string p_setting,
        int p_axisNumber,
        IoPortType p_ioType,
        int p_ioChannel
    );

    bool operator==(const OscilloscopeCaptureProperties& other) const;

    bool operator!=(const OscilloscopeCaptureProperties& other) const {
        return !(*this == other);
    }

    /**
     * Indicates whether the data came from a setting or an I/O pin.
     */
    OscilloscopeDataSource const& getDataSource() const;
    void setDataSource(OscilloscopeDataSource p_dataSource);

    /**
     * The name of the recorded setting.
     */
    std::string const& getSetting() const;
    void setSetting(std::string p_setting);

    /**
     * The number of the axis the data was recorded from, or 0 for the controller.
     */
    int getAxisNumber() const;
    void setAxisNumber(int p_axisNumber);

    /**
     * Which kind of I/O port data was recorded from.
     */
    IoPortType const& getIoType() const;
    void setIoType(IoPortType p_ioType);

    /**
     * Which I/O pin within the port was recorded.
     */
    int getIoChannel() const;
    void setIoChannel(int p_ioChannel);

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
