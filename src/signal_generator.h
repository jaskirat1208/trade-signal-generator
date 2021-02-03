#include "utils.h"

#include <fstream>

#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H 

/**
 * Contains functions required to parse the \ref Bar vector and create \ref TradingSignal objects, 
 * and output them into a file
 */
namespace signal_generator {
	
	/**
	 * @brief      Function to generate trading signals from the bars
	 *
	 * @param[in]  bars  The bars
	 */
	vector<TradingSignal> generate_trading_signals_from_bars(vector<Bar> bars) {
		double slow_ma = 0, slow_ma_sum = 0;
		double fast_ma = 0, fast_ma_sum = 0;

		// Flag to start signal generation. Set to blocked until the first non zero entry of slow SMA
		bool start = false;

		// if slow_ma < fast_ma: true otherwise false 
		bool state = false;

		// Flag indicating the signal to buy or sell the stock
		string buy_sell;

		// Signal object where all the parameters are appended
		std::vector<TradingSignal> result;

		// Double operations are costly, so not computing averages, Will keep a track of sums and to compute average, will divide by the sizes
		for (int i = 0; i < bars.size(); ++i)
		{
			// flag to buy/sell or do nothing. Defaults to do nothing
			buy_sell = "";

			// Add the price of latest bar to both fast and slow moving sums
			fast_ma_sum += bars[i].close_price;
			slow_ma_sum += bars[i].close_price;

			// Remove the last element of slow moving average from the slow moving queue 
			int slow_excluded_idx = i - constants::slow_ma_period;
			if (slow_excluded_idx >= 0)
			{
				slow_ma_sum  = slow_ma_sum - bars[slow_excluded_idx].close_price;
				slow_ma 	 = slow_ma_sum/constants::slow_ma_period;
			}

			// Remove the last element of fast moving average from the slow moving queue 
			int fast_excluded_idx = i - constants::fast_ma_period;
			if (fast_excluded_idx >= 0)
			{
				fast_ma_sum  = fast_ma_sum - bars[fast_excluded_idx].close_price;
				fast_ma 	 = fast_ma_sum/constants::fast_ma_period;
			}

			// Generating trades
			if (slow_ma && fast_ma)
			{
				/*
				 * To have a check for JUST exceeds, used variable state.
				 * - If the state change(viz, the price corssover) happens,
				 * only then buy or sell, otherwise, no signal should be generated
				 * - If the moving averages are non zero for the first time, no signal 
				 * should be generated.
				 */

				// Buy the stock if fast MA just exceeds slow SMA 
				if( !state && slow_ma < fast_ma && start) {
					buy_sell = "BUY";
				}

				// Sell the stock if slow MA just exceeds fast SMA 
				else if( state && slow_ma > fast_ma && start) {
					buy_sell = "SELL";
				}

				// Store the current state into the state variable
				state = slow_ma < fast_ma;

				// Mark trade as started
				start = true;
			}

			// Create new TradingSignal object
			TradingSignal signal;

			// Update the required parameters
			signal.bar 		= bars[i];
			signal.slow_sma = slow_ma;
			signal.fast_sma = fast_ma;
			signal.buy_sell = buy_sell;

			// Push it into the result
			result.push_back(signal);
		}

		return result;
	}

	/**
	 * @brief      Write signals to the file 
	 *
	 * @param[in]  file_name  The file name
	 * @param[in]  signals    The signals
	 */
	void write_to_file(string file_addr, vector<TradingSignal> signals) {
		ofstream outfile(file_addr);

		for (int i = 0; i < signals.size(); ++i)
		{
			outfile << signals[i] << endl;
		}
		
		outfile.close();
	}
}

#endif