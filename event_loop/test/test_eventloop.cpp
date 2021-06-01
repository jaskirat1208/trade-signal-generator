#include <gtest/gtest.h>
#include "event_loop/event_loop.h"

class CustomTestModule
{
public:
    int m_call_count;
    CustomTestModule() : m_call_count(0) {};
    void start() { m_call_count++;}
    inline void update() {m_call_count++;}
    inline bool canTerminate() {return (m_call_count == 5);}
    inline void stop() {}
};


TEST(EventLoopModuleTest, CustomModule) {
    jas::loop::EventLoop<CustomTestModule> event_loop;
    ASSERT_EQ(event_loop.m_call_count, 0);
    event_loop.loop();
    ASSERT_EQ(event_loop.m_call_count, 5);
}