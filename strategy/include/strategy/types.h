#pragma once

#include <iostream>
#include <iomanip>

#include "platform/types.h"

namespace jas {
namespace strategy {


/**
 * @brief Constants used for the strategy
 */
namespace constants {
	// Fast moving average length: 21 days
	constexpr int fast_ma_period = 21;	

	// Slow moving average length: 55 days
	constexpr int slow_ma_period = 55;

	// Decimal places for writing prices
	constexpr int default_dp = 2;

	// Decimal places for writing moving averages
	constexpr int ma_dp = 4;
}


/**
 * @brief      Measure of the following quantities for a time interval. For this case, the length of the time interval is 1 minute, starting from 9:00 am 
 * - Open price: Price at the start of the interval
 * - Close price: Price at the end of the interval
 * - Max price: Maximum stock price in the interval
 * - Min price: Lowest stock price in the interval
 */
struct Bar
{
	// Time at the start of the interval
	platform::Time interval;

	// Price at the start of the interval
	double open_price = 0;

	// Price at the end of the interval 
	double close_price = 0;

	// Maximum price during the interval
	double high_price = 0;

	// Minimum Price during the interval
	double low_price = 0;

	friend std::ostream &operator<<( std::ostream &output, Bar &bar ) {
		// Fix the decimal places of the output
		output << std::fixed << std::setprecision(constants::default_dp);

		output << bar.interval << ",";
		output << bar.open_price << ",";
		output << bar.close_price << ",";
		output << bar.high_price << ",";
		output << bar.low_price;

		return output; 
	}
};

} // namespace strategy
} // namespace jas
