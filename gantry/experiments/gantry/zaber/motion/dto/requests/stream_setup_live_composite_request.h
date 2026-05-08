// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/ascii/stream_axis_definition.h"
#include "zaber/motion/dto/ascii/pvt_axis_definition.h"

namespace zaber {
namespace motion {
namespace requests {

class StreamSetupLiveCompositeRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int streamId {0};
    bool pvt {false};
    std::vector<ascii::StreamAxisDefinition> axes;
    std::vector<ascii::PvtAxisDefinition> pvtAxes;

    StreamSetupLiveCompositeRequest();

    StreamSetupLiveCompositeRequest(
        int p_interfaceId,
        int p_device,
        int p_streamId,
        bool p_pvt,
        std::vector<ascii::StreamAxisDefinition> p_axes,
        std::vector<ascii::PvtAxisDefinition> p_pvtAxes
    );

    bool operator==(const StreamSetupLiveCompositeRequest& other) const;

    bool operator!=(const StreamSetupLiveCompositeRequest& other) const {
        return !(*this == other);
    }

    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    int getDevice() const;
    void setDevice(int p_device);

    int getStreamId() const;
    void setStreamId(int p_streamId);

    bool getPvt() const;
    void setPvt(bool p_pvt);

    std::vector<ascii::StreamAxisDefinition> const& getAxes() const;
    void setAxes(std::vector<ascii::StreamAxisDefinition> p_axes);

    std::vector<ascii::PvtAxisDefinition> const& getPvtAxes() const;
    void setPvtAxes(std::vector<ascii::PvtAxisDefinition> p_pvtAxes);

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

} // namespace requests
} // namespace motion
} // namespace zaber
