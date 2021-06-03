#pragma once

#include "platform/event_handler.h"
#include "strategy/types.h"

namespace jas {
namespace strategy {
    
class SMAStrategy: public platform::FeedEventCallback
{
public:
    SMAStrategy();
    ~SMAStrategy();

    virtual void handleEvent(const jas::platform::FeedEventInfo&);
private:
    bool cover_same_interval(const jas::platform::Time& interval_start, const jas::platform::Time& curr);
    void handleBar(const jas::strategy::Bar&);

private:
    jas::platform::Time m_interval_start;
    jas::strategy::Bar m_curr_bar;
};



} // namespace strategy
} // namespace jas
