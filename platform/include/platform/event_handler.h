#include <iostream>
#include <vector>
#include <queue>
#include <memory>

#include "platform/types.h"

namespace jas {

namespace platform {


class FeedEventCallback {
public:
    virtual void handleEvent(FeedEventInfo) = 0;
};

using EventCallbacks = std::vector<std::shared_ptr<FeedEventCallback>>; 

class EventHandler {
private:
    EventCallbacks m_callbacks;
    
public:
    EventHandler();
    subscription_id_t registerSubscriber(EVENT_TYPE, std::shared_ptr<FeedEventCallback>);
    void unregisterSubscriber(subscription_id_t);

    void publish(EVENT_TYPE event_type, FeedEventInfo);
    ~EventHandler();
};




} // namespace platform

} // namespace jas
