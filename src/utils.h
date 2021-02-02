#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Constants used in the script
#ifndef CONSTANTS_H
#define CONSTANTS_H

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
 * @brief      A structure used to denote information for an interval
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