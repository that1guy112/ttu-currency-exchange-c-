#include <iostream>

#include "conversion_rate.h"
#include "convert_currency.h"
using namespace std;

double convert_currency::convert_currency_func(
    const std::string& fromCurrency,
    const std::string& toCurrency,
    double amount)
{
    conversion_rate conversion;
    // example implementation: cover return on all paths
    if (fromCurrency == "USD" && toCurrency == "EUR") {
        return amount * conversion.EUR_CONVERSION_RATE;
    } else if (fromCurrency == "EUR" && toCurrency == "USD") {
        return amount * conversion.USD_CONVERSION_RATE;
    }

    // fallback: if no conversion rule matched, return original amount (or throw)
    return amount;
}