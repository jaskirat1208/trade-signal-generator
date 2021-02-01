#include <string>

using namespace std;

#ifndef DATAPARSER_H
#define DATAPARSER_H

/**
 * @brief      Parses raw data and converts it into bars of fixed lengths
 */
class DataParser
{
	public:
		DataParser();
		parse_from_file(string);
		~DataParser();

	private:
		

};

#endif

#ifndef BAR_H
#define BAR_H

/**
 * @brief      A structure used to denote information for an interval
 */
struct Bar
{
	// Price at the start of the interval
	double open_price;

	// Price at the end of the interval 
	double close_price;

	// Maximum price during the interval
	double high_price;

	// Minimum Price during the interval
	double low_price;
};

#endif