#include <gtest/gtest.h>

#include "platform/event_handler.h"

class EventCB1: public jas::platform::FeedEventCallback {
    int m_count=0;
    void handleEvent(jas::platform::FeedEventInfo feed_event_info) override {
        m_count++;
        std::cout << "I am called " << m_count << " times." << std::endl;
        std::cout << feed_event_info.time << ", " << feed_event_info.price << std::endl;
    }
};

TEST(CustomTest, Test1) {
    jas::platform::EventHandler handler;
    std::shared_ptr<EventCB1> event1 = std::make_shared<EventCB1>();
    handler.registerSubscriber(jas::platform::EVENT_TYPE::FEED, event1);
    handler.publish(jas::platform::EVENT_TYPE::FEED, jas::platform::FeedEventInfo{{12, 0, 0}, 10});
    handler.publish(jas::platform::EVENT_TYPE::FEED, jas::platform::FeedEventInfo{{12, 0, 0}, 10.1});
}