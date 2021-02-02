#include "data_parser.h"
#include "signal_generator.h"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	// From the input file, gets the prices and computes the minute average

	// TODO: instead of doing the entire copy operation on the vector, return the pointer to the vector
	
	/** 
	 * Bar: data for a specific interval of length 1 minute 
	 * - Open(open_price), high(high_price), low(low_price), and close(close_price) prices
	 */
	vector<Bar> bars = data_parser::parse_from_file(argv[1]);

	/** 
	 * Parses the data bars to generate trading signals
	 * Trading signals: 
	 * - Timestamp, Open, high, low, close, fastMA, slowMA, trade
	 */
	vector<TradingSignal> signals = signal_generator::generate_trading_signals_from_bars(bars);

	for (int i = 0; i < signals.size(); ++i)
	{
		cout << signals[i] << endl;
	}
	return 0;
}