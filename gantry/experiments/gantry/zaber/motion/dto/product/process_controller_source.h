// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/product/process_controller_source_sensor.h"

namespace zaber {
namespace motion {
namespace product {

/**
 * The source used by a process in a closed-loop mode.
 */
class ProcessControllerSource: public Serializable {
public:
    ProcessControllerSourceSensor sensor {0};
    int port {0};

    ProcessControllerSource();

    ProcessControllerSource(
        ProcessControllerSourceSensor p_sensor,
        int p_port
    );

    bool operator==(const ProcessControllerSource& other) const;

    bool operator!=(const ProcessControllerSource& other) const {
        return !(*this == other);
    }

    /**
     * The type of input sensor.
     */
    ProcessControllerSourceSensor const& getSensor() const;
    void setSensor(ProcessControllerSourceSensor p_sensor);

    /**
     * The specific input to use.
     */
    int getPort() const;
    void setPort(int p_port);

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

} // namespace product
} // namespace motion
} // namespace zaber
