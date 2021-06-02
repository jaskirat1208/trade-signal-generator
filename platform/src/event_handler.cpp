#include "platform/event_handler.h"

namespace jas
{

namespace platform
{

EventHandler::EventHandler() {}


EventHandler::~EventHandler() {}

subscription_id_t EventHandler::registerSubscriber(EVENT_TYPE event_type, std::shared_ptr<FeedEventCallback> event_callback) {
    m_callbacks.push_back(event_callback);
    return m_callbacks.size() - 1;
}

void EventHandler::unregisterSubscriber(subscription_id_t) {}

/**
 * @brief Publish an event. Call the handleEvent Handlers for the corresponding classes
 * 
 * @param event 
 */
void EventHandler::publish(EVENT_TYPE event_type, FeedEventInfo feed_event_info) {
    for(auto event: m_callbacks) {
        event->handleEvent(feed_event_info);
    }
}


} // namespace platform

} // namespace jas
