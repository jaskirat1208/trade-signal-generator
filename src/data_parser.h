#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "utils.h"

using namespace std;

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
		output << "Start: " << bar.interval << ", ";
		output << "Open: " << bar.open_price << ", ";
		output << "Close: " << bar.close_price << ", ";
		output << "High: " << bar.high_price << ", ";
		output << "Low: " << bar.low_price<<endl;
		return output; 
	}
};

#endif

#ifndef DATAPARSER_H
#define DATAPARSER_H

/**
 * @brief      Parses raw data and converts it into bars of fixed lengths
 */
class DataParser
{
	public:
		DataParser() {
		};
		
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

			Bar bar;
			Time interval_start{0, 0, 0};
			while(getline(infile, str)) {
				// Initialize a stringstream
				stringstream ss(str);
				
				ss >> t;
				ss.ignore();
				ss >> price;

				// If they don't cover the same interval
				if(!this->cover_same_interval(interval_start, t)) {
					
					// Push the previous bar into the result
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
		
		~DataParser() {
		};

	private:
		bool cover_same_interval(Time interval_start, Time curr) {
			if (interval_start.hour == curr.hour && interval_start.min == curr.min)
			{
				return true;
			}
			return false;
		}

};

#endif