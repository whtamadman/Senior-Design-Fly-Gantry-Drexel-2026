#pragma once

#include <type_traits>
#include <functional>
#include <memory>
#include <mutex>

#include "zaber/motion/gateway/sdk_event.h"

namespace zaber { namespace motion {

class EventHandlerBase {
public:
    EventHandlerBase() = default;
    virtual ~EventHandlerBase() = default;
    virtual void handleEvent(const SdkEvent&) { }
};

template <typename T>
using EventCallback = std::function<void(const T&)>;
using EventFilter = std::function<bool(const SdkEvent&)>;
template <typename T>
using EventMutator = std::function<T(const SdkEvent&)>;

template<typename T>
class EventHandler : public EventHandlerBase {
public:
    EventHandler() = delete;
    EventHandler(EventCallback<T> callback, EventFilter filter, EventMutator<T> mutator) :
        _callback(std::move(callback)), _filter(std::move(filter)), _mutator(std::move(mutator)) { }

    EventHandler& operator=(const EventHandler&) = delete;
    EventHandler(const EventHandler&) = delete;
    EventHandler(EventHandler&&) = delete;
    EventHandler& operator=(EventHandler&&) = delete;

    void setCallback(EventCallback<T> callback) {
        std::lock_guard<std::recursive_mutex> lock(_callbackMutex);
        _callback = std::move(callback);
    }

void handleEvent(const SdkEvent& event) override {
    if (!_filter(event)) {
        return;
    }

    std::lock_guard<std::recursive_mutex> lock(_callbackMutex);
    if (_callback) {
        auto callback = std::move(_callback);
        _callback = nullptr;

        callback(_mutator(event));
        if (!_callback) {
            _callback = std::move(callback);
        }
    }
}

private:
    EventCallback<T> _callback;
    EventFilter _filter;
    EventMutator<T> _mutator;
    std::recursive_mutex _callbackMutex;
};

}  // namespace motion
}  // namespace zaber
