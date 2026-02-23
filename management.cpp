#include "management.h"
#include "conversion_rate.h"

#include <iostream>
using namespace std;


conversion_rate conversion_rate;

void management::change_conversion_rate(const std::string &Currency, const double value)
{ // THE MAIN LOOP UNDER WHICH THE PROGRAM RUNS
    if (Currency == "USD") {
        conversion_rate.USD_CONVERSION_RATE = value;
    }
    else if (Currency == "EUR") {
        conversion_rate.EUR_CONVERSION_RATE = value;
    }
    else if (Currency == "JPY") {
        conversion_rate.JPY_CONVERSION_RATE = value;
    }
    else {
        cout << "Unrecognized conversion type" << endl;
    }
}