// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <vector>
#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/requests/stream_segment_type.h"
#include "zaber/motion/dto/ascii/measurement_sequence.h"

namespace zaber {
namespace motion {
namespace requests {

class PvtPointsRequest: public Serializable {
public:
    int interfaceId {0};
    int device {0};
    int streamId {0};
    bool pvt {false};
    StreamSegmentType type {0};
    std::vector<ascii::MeasurementSequence> positions;
    std::vector<ascii::MeasurementSequence> velocities;
    ascii::MeasurementSequence times;

    PvtPointsRequest();

    PvtPointsRequest(
        int p_interfaceId,
        int p_device,
        int p_streamId,
        bool p_pvt,
        StreamSegmentType p_type,
        std::vector<ascii::MeasurementSequence> p_positions,
        std::vector<ascii::MeasurementSequence> p_velocities,
        ascii::MeasurementSequence p_times
    );

    bool operator==(const PvtPointsRequest& other) const;

    bool operator!=(const PvtPointsRequest& other) const {
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

    std::vector<ascii::MeasurementSequence> const& getPositions() const;
    void setPositions(std::vector<ascii::MeasurementSequence> p_positions);

    std::vector<ascii::MeasurementSequence> const& getVelocities() const;
    void setVelocities(std::vector<ascii::MeasurementSequence> p_velocities);

    ascii::MeasurementSequence const& getTimes() const;
    void setTimes(ascii::MeasurementSequence p_times);

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
