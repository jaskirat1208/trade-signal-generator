#include <iostream>
#include <iomanip>

using namespace std;

#ifndef TIME_H
#define TIME_H

struct Time
{
	int hour = 0;
	int min = 0;
	double sec = 0;

	friend istream &operator>>( istream &input, Time &right ) { //input in hh:mm format
        input >> right.hour; // input hours
        input.ignore(); // skip :
        input >> right.min; // input minute part
        input.ignore();	// skip :
        input >> right.sec;
        return input;
	}

	friend ostream &operator<<( ostream &output, Time &right ) {
		output << setfill('0') << setw(2) << right.hour<<":";
		output << setfill('0') << setw(2) << right.min;
		return output; 
	}
	
};


#endif
