#pragma once

#include "event_loop/base_module.h"
#include "platform/event_handler.h"
#include "platform/file_feed_getter.h"


namespace jas {

namespace platform {

class EventModule : public loop::BaseModule
{
private:
    EventHandler m_handler;
    FileFeedGetter feed_getter;
public:
    void publishFeedEvent(EVENT_TYPE event_type, FeedEventInfo info) {
        m_handler.publish(event_type, info);
    }

    subscription_id_t registerSubscriber(EVENT_TYPE event_type, std::shared_ptr<FeedEventCallback> callback) {
        return m_handler.registerSubscriber(event_type, callback);
    }

    void unregisterSubscriber(EVENT_TYPE event_type, subscription_id_t subscription_id) {
        (void)event_type;
        m_handler.unregisterSubscriber(subscription_id);
    }

    void update() {
        publishFeedEvent(EVENT_TYPE::FEED, feed_getter.parseFeedEventInfo());
    }

    bool canTerminate() {
        return !feed_getter.getFeedString();
    }

    EventModule() : feed_getter("./data/feed.txt") {}
};

} // namespace platform

} // namespace jas
