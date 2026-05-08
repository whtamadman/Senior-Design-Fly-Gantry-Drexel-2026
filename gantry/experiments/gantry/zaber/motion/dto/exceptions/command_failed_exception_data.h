// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {
namespace exceptions {

/**
 * Contains additional data for CommandFailedException.
 */
class CommandFailedExceptionData: public Serializable {
public:
    std::string command;
    std::string responseData;
    std::string replyFlag;
    std::string status;
    std::string warningFlag;
    int deviceAddress {0};
    int axisNumber {0};
    int id {0};

    CommandFailedExceptionData();

    CommandFailedExceptionData(
        std::string p_command,
        std::string p_responseData,
        std::string p_replyFlag,
        std::string p_status,
        std::string p_warningFlag,
        int p_deviceAddress,
        int p_axisNumber,
        int p_id
    );

    bool operator==(const CommandFailedExceptionData& other) const;

    bool operator!=(const CommandFailedExceptionData& other) const {
        return !(*this == other);
    }

    /**
     * The command that got rejected.
     */
    std::string const& getCommand() const;
    void setCommand(std::string p_command);

    /**
     * The data from the reply containing the rejection reason.
     */
    std::string const& getResponseData() const;
    void setResponseData(std::string p_responseData);

    /**
     * The flag indicating that the command was rejected.
     */
    std::string const& getReplyFlag() const;
    void setReplyFlag(std::string p_replyFlag);

    /**
     * The current device or axis status.
     */
    std::string const& getStatus() const;
    void setStatus(std::string p_status);

    /**
     * The highest priority warning flag on the device or axis.
     */
    std::string const& getWarningFlag() const;
    void setWarningFlag(std::string p_warningFlag);

    /**
     * The address of the device that rejected the command.
     */
    int getDeviceAddress() const;
    void setDeviceAddress(int p_deviceAddress);

    /**
     * The number of the axis which the rejection relates to.
     */
    int getAxisNumber() const;
    void setAxisNumber(int p_axisNumber);

    /**
     * The message ID of the reply.
     */
    int getId() const;
    void setId(int p_id);

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

} // namespace exceptions
} // namespace motion
} // namespace zaber
