#include "utils.h"
#include "data_parser.h"
#include "signal_generator.h"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	string input_filename = argv[1];
	string output_filename = argv[2];
	/** 
	 * - Reads the cvs file and groups the data into bars of length 1 minute 
	 * 
	 * Bar: data for a specific interval of length 1 minute 
	 * - Open(open_price), high(high_price), low(low_price), and close(close_price) prices
	 */
	vector<Bar> bars = data_parser::parse_from_file(input_filename);

	/** 
	 * Parses the data bars to generate trading signals
	 * 
	 * Trading signals: 
	 * - Timestamp, Open, high, low, close, fastSMA, slowSMA, buy_sell
	 */
	vector<TradingSignal> signals = signal_generator::generate_trading_signals_from_bars(bars);

	// Output all trading signals in stdout
	signal_generator::write_to_file(output_filename, signals);
	return 0;
}