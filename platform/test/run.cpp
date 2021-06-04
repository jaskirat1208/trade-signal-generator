#include <gtest/gtest.h>

#include "platform/event_module.h"
#include "event_loop/event_loop.h"


#define ASSERT_APPROX_EQ(a, b) ASSERT_NEAR(a, b, 0.001) 
class EventCB1: public jas::platform::FeedEventCallback {
public:
    int m_count=0;
    jas::platform::price_t last_feed_price;
    void handleEvent(const jas::platform::FeedEventInfo& feed_event_info) override {
        m_count++;
        last_feed_price = feed_event_info.price;
    }
};

TEST(CustomTest, IndividualPubSub) {
    jas::platform::EventHandler handler;
    std::shared_ptr<EventCB1> event1 = std::make_shared<EventCB1>();
    handler.registerSubscriber(jas::platform::EVENT_TYPE::FEED, event1);
    handler.publish(jas::platform::EVENT_TYPE::FEED, jas::platform::FeedEventInfo{{12, 0, 0}, 10});
    handler.publish(jas::platform::EVENT_TYPE::FEED, jas::platform::FeedEventInfo{{12, 0, 0}, 10.1});
    ASSERT_EQ(event1->m_count, 2);
}

/**
 * @brief Test for the events module
 * 
 */
TEST(EventModuleTest, EventModuleTest) {
    jas::platform::EventModule event_module;
    std::shared_ptr<EventCB1> event1 = std::make_shared<EventCB1>();
    event_module.registerSubscriber(jas::platform::EVENT_TYPE::FEED, event1);
    event_module.start();
    event_module.canTerminate();
    event_module.update();
    event_module.stop();

    ASSERT_EQ(event1->m_count, 1);
    ASSERT_APPROX_EQ(event1->last_feed_price, 100);
}


/**
 * @brief Construct a new TEST object
 * 
 */
TEST(EventLoopIntegration, EventLoopIntegrationTest) {
    jas::loop::EventLoop<jas::platform::EventModule> engine;
    std::shared_ptr<EventCB1> event1 = std::make_shared<EventCB1>();

    engine.registerSubscriber(jas::platform::EVENT_TYPE::FEED, event1);
    engine.loop();
    ASSERT_EQ(event1->m_count, 4);
    ASSERT_APPROX_EQ(event1->last_feed_price, 100.15);
}