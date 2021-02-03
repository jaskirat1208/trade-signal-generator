#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Constants used in the script
#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @brief Constants used for the project
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

#endif

#ifndef TIME_H
#define TIME_H

/**
 * @brief      A way of storing timestamps 
 */
struct Time
{
	int hour = 0;
	int min = 0;
	double sec = 0;

	friend istream &operator>>( istream &input, Time &right ) { //input in hh:mm format
		input >> right.hour; 	// input hours
		input.ignore(); 		// skip :
		input >> right.min; 	// input minute part
		input.ignore();			// skip :
		input >> right.sec;
		return input;
	}

	friend ostream &operator<<( ostream &output, Time &right ) {
		// Set a width of 2 digits, and fills the empty space with a zero
		output << setfill('0') << setw(2) << right.hour<<":";
		output << setfill('0') << setw(2) << right.min;
		return output; 
	}
};


#endif


#ifndef BAR_H
#define BAR_H

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
	Time interval;

	// Price at the start of the interval
	double open_price = 0;

	// Price at the end of the interval 
	double close_price = 0;

	// Maximum price during the interval
	double high_price = 0;

	// Minimum Price during the interval
	double low_price = 0;

	friend ostream &operator<<( ostream &output, Bar &bar ) {
		// Fix the decimal places of the output
		output << fixed << std::setprecision(constants::default_dp);

		output << bar.interval << ",";
		output << bar.open_price << ",";
		output << bar.close_price << ",";
		output << bar.high_price << ",";
		output << bar.low_price;

		return output; 
	}
};

#endif

#ifndef TRADING_SIGNAL_H
#define TRADING_SIGNAL_H

/**
 * @brief      For each bar, this displays fast and slow moving averages, also displays a buy/sell signal in case of a crossover.
 * - Fast simple moving average: The moving average corresponding to last 21 bars
 * - Slow simple moving average: Moving average corresponding to last 55 intervals
 */
struct TradingSignal
{
	// Bar corresponding to the interval specific information
	Bar bar;

	// Slow simple moving average
	double slow_sma;

	// Fast simple moving average
	double fast_sma;

	// Buy or sell signal
	string buy_sell;

	friend ostream&operator<<( ostream &output, TradingSignal &signal) {
		// Output the bar using the overloaded operator
		output << signal.bar << ",";
		
		// Set number of decimal places
		output << fixed << std::setprecision(constants::ma_dp);

		output << signal.fast_sma << ",";
		output << signal.slow_sma << ",";
		output << signal.buy_sell;

		return output;
	}
};

#endif