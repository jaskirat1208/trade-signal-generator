#pragma once

#include "platform/event_handler.h"

namespace jas {
namespace strategy {
    
class SMAStrategy: public platform::FeedEventCallback
{
public:
    SMAStrategy();
    ~SMAStrategy();

    void handleEvent(jas::platform::FeedEventInfo);
};



} // namespace strategy
} // namespace jas
