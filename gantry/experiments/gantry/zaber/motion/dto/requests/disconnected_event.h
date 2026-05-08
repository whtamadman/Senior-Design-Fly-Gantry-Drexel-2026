// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"
#include "zaber/motion/dto/requests/errors.h"

namespace zaber {
namespace motion {
namespace requests {

/**
 * Event that is sent when a connection is lost.
 */
class DisconnectedEvent: public Serializable {
public:
    int interfaceId {0};
    int sessionId {0};
    Errors errorType {0};
    std::string errorMessage;

    DisconnectedEvent();

    DisconnectedEvent(
        int p_interfaceId,
        int p_sessionId,
        Errors p_errorType,
        std::string p_errorMessage
    );

    bool operator==(const DisconnectedEvent& other) const;

    bool operator!=(const DisconnectedEvent& other) const {
        return !(*this == other);
    }

    /**
     * The id of the interface that was disconnected.
     */
    int getInterfaceId() const;
    void setInterfaceId(int p_interfaceId);

    /**
     * The id of the connection session.
     */
    int getSessionId() const;
    void setSessionId(int p_sessionId);

    /**
     * The type of error that caused the disconnection.
     */
    Errors const& getErrorType() const;
    void setErrorType(Errors p_errorType);

    /**
     * The message describing the error.
     */
    std::string const& getErrorMessage() const;
    void setErrorMessage(std::string p_errorMessage);

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
