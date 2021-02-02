#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "utils.h"

using namespace std;

#ifndef DATAPARSER_H
#define DATAPARSER_H

namespace data_parser {
	
	/**
	 * @brief      Checks if the two Time objects are a part of the same interval
	 *
	 * @param[in]  interval_start  The interval start
	 * @param[in]  curr            The curr interval
	 *
	 * @return     True if they are a part of the same interval, otherwise not
	 */
	bool cover_same_interval(Time interval_start, Time curr) {
		if (interval_start.hour == curr.hour && interval_start.min == curr.min)
		{
			return true;
		}
		return false;
	}
	
	/**
	 * @brief      Read the file to get the timestamps and prices
	 * Why vector instead of vector*: Refer the following FAQ: http://www.cplusplus.com/forum/general/56177/
	 * 
	 * @param[in]  file_addr  The file address
 	*/
	vector<Bar> parse_from_file(string file_addr) {
		
		// Open the file in readable mode
		ifstream infile(file_addr);
		
		// String to store line 
		string str;

		// Time, a structure containing hours, min and seconds
		Time t;

		// Price of stock
		double price;

		// Result of the function
		vector<Bar> result;

		// Bar: collection of option price data(open, high, low, close) over the interval of 1 minute
		Bar bar;

		// Keep a track of the starting point of the interval
		Time interval_start{0, 0, 0};

		while (getline(infile, str)) {
			// Initialize a stringstream
			stringstream ss(str);
			
			ss >> t;
			ss.ignore();
			ss >> price;

			// If they don't cover the same interval
			if (!data_parser::cover_same_interval(interval_start, t)) {
				
				// Push the previous bar into the result if it is not the first interval
				if(interval_start.hour != 0)
					result.push_back(bar);

				// Mark the start of new interval
				interval_start = t;

				// Update the interval and start, high, low price of the new bar created
				bar.open_price = price;
				bar.interval = interval_start;
				bar.low_price = price;
				bar.high_price = price;
			}

			// Update the closing price of the bar
			bar.close_price = price;
			
			// Update the high price
			if (bar.high_price < price)
			{
				bar.high_price = price;
			}
			
			// Update low price
			if (bar.low_price > price)
			{
				bar.low_price = price;
			}
		}

		// Push the last bar into the result
		result.push_back(bar);	

		// Close the file
		infile.close();

		return result;
	}

}

#endif