// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/requests/stream_segment_type.h"
#include "zaber/motion/dto/measurement.h"

namespace zaber {
namespace motion {
namespace requests {

class StreamLineRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int streamId {0};
    bool pvt {false};
    StreamSegmentType type {0};
    std::vector<Measurement> endpoint;
    std::vector<int> targetAxesIndices;

    StreamLineRequest();

    StreamLineRequest(
        int p_interfaceId,
        int p_device,
        int p_streamId,
        bool p_pvt,
        StreamSegmentType p_type,
        std::vector<Measurement> p_endpoint,
        std::vector<int> p_targetAxesIndices
    );

    bool operator==(const StreamLineRequest& other) const;

    bool operator!=(const StreamLineRequest& other) const {
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

    StreamSegmentType const& getType() const;
    void setType(StreamSegmentType p_type);

    std::vector<Measurement> const& getEndpoint() const;
    void setEndpoint(std::vector<Measurement> p_endpoint);

    std::vector<int> const& getTargetAxesIndices() const;
    void setTargetAxesIndices(std::vector<int> p_targetAxesIndices);

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
