#include <gtest/gtest.h>

#include "platform/event_module.h"
#include "event_loop/event_loop.h"
#include "strategy/base_strategy_module.h"

#define ASSERT_APPROX_EQ(a, b) ASSERT_NEAR(a, b, 0.001) 

TEST(TestStrategy, TestSMAStrategy) {
    jas::loop::EventLoop<jas::strategy::SMAStrategyModule<jas::platform::EventModule>> engine;
    engine.loop();
}

TEST(TestSMAQueue, TestSMAQueue) {
    jas::strategy::SMAQueue queue(2);

    auto bar = jas::strategy::Bar{{17,15},101.45,101.45,101.45,101.45};
    queue.update(bar);

    ASSERT_APPROX_EQ(queue.getSMA(), 0);
    bar = jas::strategy::Bar{{17,16},101.35,101.35,101.35,101.35};
    queue.update(bar);
    ASSERT_APPROX_EQ(queue.getSMA(), 101.40);

    bar = jas::strategy::Bar{{17,17},101.45,101.45,101.45,101.45};
    queue.update(bar);
    ASSERT_APPROX_EQ(queue.getSMA(), 101.40);

}