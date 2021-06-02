#include <cstdint>
#include <iostream>
#include <iomanip>

namespace jas
{

namespace platform
{

using price_t = double;
using subscription_id_t = uint32_t;


enum EVENT_TYPE {
    FEED=0,
    NONE=1
};

/**
 * @brief      A way of storing timestamps 
 */
struct Time
{
	int hour = 0;
	int min = 0;
	double sec = 0;

	friend std::istream &operator>>( std::istream &input, Time &right ) { 
        //input in hh:mm:ss.sss format
		input >> right.hour; 	// input hours
		input.ignore(); 		// skip :
		input >> right.min; 	// input minute part
		input.ignore();			// skip :
		input >> right.sec;
		return input;
	}

	friend std::ostream &operator<<( std::ostream &output, Time &right ) {
		// Set a width of 2 digits, and fills the empty space with a zero
		output << std::setfill('0') << std::setw(2) << right.hour<<":";
		output << std::setfill('0') << std::setw(2) << right.min;
		return output; 
	}
};

/**
 * @brief Feed Event Information is stored in this way
 * 
 */
struct FeedEventInfo {
    Time time;
    price_t price;
};


} // namespace platform

} // namespace jas
