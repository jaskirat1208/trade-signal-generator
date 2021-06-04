#include "strategy/sma_strategy.h"

namespace jas {
namespace strategy {

/**
 * @brief 
 * 
 * @param feed_info 
 */
void SMAStrategy::handleEvent(const platform::FeedEventInfo& feed_info) {
    // In case a new interval starts
    if(!this->cover_same_interval(m_interval_start, feed_info.time)) {
        if(m_interval_start.hour != 0) {
            handleBar(m_curr_bar);
        }
        
        m_interval_start = feed_info.time;
        m_curr_bar.open_price = feed_info.price;
        m_curr_bar.interval = m_interval_start;
        m_curr_bar.low_price = feed_info.price;
        m_curr_bar.high_price = feed_info.price;
    }
    m_curr_bar.close_price = feed_info.price;
    m_curr_bar.high_price = std::max(m_curr_bar.high_price, feed_info.price);
    m_curr_bar.low_price = std::min(m_curr_bar.low_price, feed_info.price);
}

/**
 * @brief      A helper function to the function \ref parse_from_file. Checks if the two Time objects are a part of the same interval
 *
 * @param[in]  interval_start  The interval start
 * @param[in]  curr            The curr interval
 *
 * @return     True if they are a part of the same interval, otherwise not
 */
bool SMAStrategy::cover_same_interval(const jas::platform::Time& interval_start, const jas::platform::Time& curr) {
    if (interval_start.hour == curr.hour && interval_start.min == curr.min) {
        return true;
    }
    return false;
}

/**
 * @brief 
 * 
 * @param bar 
 */
void SMAStrategy::handleBar(const jas::strategy::Bar& bar) {
    m_slow_sma_queue.update(bar);
    m_fast_sma_queue.update(bar);


    bool curr_state = m_slow_sma_queue.getSMA() < m_fast_sma_queue.getSMA();

    if(m_slow_sma_queue.getSMA() && m_fast_sma_queue.getSMA()) {
        if(m_start_signals && (m_prev_state ^ curr_state)) {
            if(curr_state) {
                std::cout << const_cast<strategy::Bar&>(bar) << ", BUY" << std::endl;
            } else {
                std::cout << const_cast<strategy::Bar&>(bar) << ", SELL" << std::endl;
            }
        }
        m_start_signals = true;
    }
    m_prev_state = curr_state;
}

/**
 * @brief Construct a new SMAStrategy::SMAStrategy object
 * 
 */
SMAStrategy::SMAStrategy() : 
    m_interval_start{0, 0, 0},
    m_slow_sma_queue(constants::slow_ma_period),
    m_fast_sma_queue(constants::fast_ma_period),
    m_prev_state(false),
    m_start_signals(false) {
}

SMAStrategy::~SMAStrategy() {}

} // namespace platform
} // namespace jas
