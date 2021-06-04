#pragma once

#include "strategy/sma_strategy.h"

namespace jas {
namespace strategy {

template<class BASE>
class SMAStrategyModule: public BASE {
    SMAStrategy strategy;
public:
    SMAStrategyModule();

    void start();

    void update();

    bool canTerminate();

    void stop(); 
    
    // /**
    //  * @brief Updates the state according to the signal generated
    //  * 
    //  */
    // void handleEvent(jas::platform::FeedEventInfo);
};


} // namespace strategy
} // namespace jas

#include "strategy/impl/base_strategy_module_impl.h"