#include "management.h"
#include "conversion_rate.h"

#include <iostream>
using namespace std;


conversion_rate conversion_rate;

// management class function to change conversion rate of currency
void management::change_conversion_rate(const std::string &Currency, const double value)
{
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