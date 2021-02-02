#include "utils.h"

#include <iostream>

#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H 

namespace signal_generator {
	
	/**
	 * @brief      Function to generate trading signals from the bars
	 *
	 * @param[in]  bars  The bars
	 */
	vector<TradingSignal> generate_trading_signals_from_bars(vector<Bar> bars) {
		double slow_ma = 0, slow_ma_sum = 0;
		double fast_ma = 0, fast_ma_sum = 0;

		bool state = false; 		// if slow_ma < fast_ma: true otherwise false 
		bool start = false;
		string buy_sell;

		std::vector<TradingSignal> result;

		// Double operations are costly, so not computing averages, Will keep a track of sums and to compute average, will divide by the sizes
		for (int i = 0; i < bars.size(); ++i)
		{
			buy_sell = "";
			fast_ma_sum += bars[i].close_price;
			slow_ma_sum += bars[i].close_price;

			int slow_excluded_idx = i - constants::slow_ma_period;

			if (slow_excluded_idx >= 0)
			{
				slow_ma_sum  = slow_ma_sum - bars[slow_excluded_idx].close_price;
				slow_ma 	 = slow_ma_sum/constants::slow_ma_period;
			}

			int fast_excluded_idx = i - constants::fast_ma_period;
			if (fast_excluded_idx >= 0)
			{
				fast_ma_sum  = fast_ma_sum - bars[fast_excluded_idx].close_price;
				fast_ma 	 = fast_ma_sum/constants::fast_ma_period;
			}

			if (slow_ma && fast_ma)
			{
				if( !state && slow_ma < fast_ma && start) {
					buy_sell = "BUY";
				}

				else if( state && slow_ma > fast_ma && start) {
					buy_sell = "SELL";
				}

				state = slow_ma < fast_ma;
				start = true;
			}
			TradingSignal signal;
			signal.bar = bars[i];
			signal.slow_sma = slow_ma;
			signal.fast_sma = fast_ma;
			signal.buy_sell = buy_sell;

			result.push_back(signal);
		}
		return result;
	}
}

#endif