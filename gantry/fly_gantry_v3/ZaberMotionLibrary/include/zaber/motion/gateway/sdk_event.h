#pragma once

#include <string>
#include <vector>
#include <memory>

#include "zaber/motion/dto/serializable.h"

namespace zaber { namespace motion {

class SdkEvent {
public:
    enum class EventType {
        INVALID = 0,
        UNKNOWN_RESPONSE,
        UNKNOWN_BINARY_RESPONSE,
        ALERT,
        BINARY_REPLY_ONLY,
        DISCONNECTED,
        TEST,
    };

    static constexpr std::string_view UNKNOWN_RESPONSE_STR = "interface/unknown_response";
    static constexpr std::string_view UNKNOWN_BINARY_RESPONSE_STR = "binary/interface/unknown_response";
    static constexpr std::string_view ALERT_STR = "interface/alert";
    static constexpr std::string_view BINARY_REPLY_ONLY_STR = "binary/interface/reply_only";
    static constexpr std::string_view DISCONNECTED_STR = "interface/disconnected";
    static constexpr std::string_view TEST_STR = "test/event";

    /*
        Empty default constructor is included to deal with a known conformity
        issue with MSVC 2017 and earlier. It should not be used otherwise.
        https://developercommunity.visualstudio.com/content/problem/60897/c-shared-state-futuresstate-default-constructs-the.html
    */
    // NOLINTNEXTLINE
    SdkEvent() {};

    SdkEvent(const std::vector<std::string>& responseBuffers);
    int getInterfaceId() const { return this->_interfaceId; }
    EventType getEventType() const { return this->_eventType; }
    std::shared_ptr<Serializable> getEventData() const { return this->_eventData; }

private:
    int _interfaceId {-1};
    EventType _eventType {EventType::INVALID};
    std::shared_ptr<Serializable> _eventData {nullptr};

    void unpackEventData(const std::string& eventName, const std::string& data);

    template<typename T>
    inline void initEventData(const std::string& data) {
        _eventData = std::make_shared<T>();
        _eventData->populateFromByteArray(data);
        _interfaceId = std::static_pointer_cast<T>(_eventData)->getInterfaceId();
    }
};

}  // namespace motion
}  // namespace zaber
