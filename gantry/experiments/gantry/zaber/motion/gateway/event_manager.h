#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <mutex>
#include <utility>
#include <functional>
#include <queue>
#include <thread>
#include <functional>
#include <condition_variable>

#include "zaber/motion/gateway/sdk_event.h"
#include "zaber/motion/gateway/event_handler.h"
#include "zaber/motion/dto/requests/test_event.h"

namespace zaber {
namespace motion {

class EventManager {
public:
    typedef std::function<void(const SdkEvent&)> SdkEventCallback;

    ~EventManager();
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    EventManager(EventManager&&) = delete;
    EventManager& operator=(EventManager&&) = delete;

    static EventManager& getSingleton();

    template<typename T>
    std::shared_ptr<EventHandler<T>> createEventHandler(const EventCallback<T>& callback,
        const EventFilter& filter, const EventMutator<T>& mutator) {

        auto handler = std::make_shared<EventHandler<T>>(callback, filter, mutator);
        {
            std::lock_guard<std::mutex> lock(_newHandlersMutex);
            _newHandlers.push_back(handler);
        }
        return handler;
    }

private:
    class EventCallbackRegistrar { public: EventCallbackRegistrar() noexcept; };
    friend EventCallbackRegistrar;
    const static EventCallbackRegistrar _registrar;

    std::vector<std::weak_ptr<EventHandlerBase>> _eventHandlers;
    std::mutex _newHandlersMutex;
    std::vector<std::weak_ptr<EventHandlerBase>> _newHandlers;
    std::mutex _eventQueueMutex;
    std::queue<SdkEvent> _eventQueue;
    std::condition_variable _workerThreadCondition;
    std::thread _eventThread;
    bool _handleEventQueue = true;

    EventManager();
    void processEvent(const std::string& responseBuffer);
    void handleEventQueue();
    inline void tryAddHandlers();
    inline void tryRemoveHandlers();

    static void handleEvent(void* responseData, int64_t /*unused*/);
};

} // namespace motion
} // namespace zaber

