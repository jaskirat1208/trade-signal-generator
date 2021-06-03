#include "strategy/sma_strategy.h"

namespace jas {
namespace strategy {

/**
 * @brief 
 * 
 * @param feed_info 
 */
void SMAStrategy::handleEvent(platform::FeedEventInfo feed_info) {
    std::cout << "Handling feed event" << std::endl;
    (void)feed_info;
}


SMAStrategy::SMAStrategy(/* args */)
{
}

SMAStrategy::~SMAStrategy()
{
}
} // namespace platform
} // namespace jas
