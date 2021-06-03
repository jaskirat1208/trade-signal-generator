#include <gtest/gtest.h>

#include "platform/event_module.h"
#include "event_loop/event_loop.h"
#include "strategy/base_strategy_module.h"

TEST(TestStrategy, TestSMAStrategy) {
    jas::loop::EventLoop<jas::strategy::SMAStrategyModule<jas::platform::EventModule>> engine;
    engine.loop();
}