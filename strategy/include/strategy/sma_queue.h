#pragma once

#include <queue>

#include "strategy/types.h"

namespace jas {
namespace strategy {

class SMAQueue {
private:
    std::queue<jas::strategy::Bar> m_queue;
    const int m_max_size;
    platform::price_t m_sum;
public:
    SMAQueue(int max_size);
    void update(const jas::strategy::Bar& bar);
    jas::platform::price_t getSMA();
    ~SMAQueue();
};

}  // namespace strategy
}  // namespace jas
