#include "strategy/sma_queue.h"

namespace jas {
namespace strategy {

/**
 * @brief Construct a new SMAQueue::SMAQueue object
 * 
 * @param max_size 
 */
SMAQueue::SMAQueue(int max_size) : m_max_size(max_size), m_queue(), m_sum(0) {}

/**
 * @brief 
 * 
 * @param bar 
 */
void SMAQueue::update(const jas::strategy::Bar& bar) {
    m_queue.push(bar);
    m_sum += bar.close_price;
    if(m_queue.size() > m_max_size) {
        Bar front_bar = m_queue.front();
        m_sum -= front_bar.close_price;
        m_queue.pop();
    }
}

/**
 * @brief 
 * 
 * @return jas::platform::price_t 
 */
jas::platform::price_t SMAQueue::getSMA() {
    if(m_queue.size() < m_max_size) return 0;
    return m_sum/m_queue.size();
}

SMAQueue::~SMAQueue() {}


} // namespace strategy
} // namespace jas
