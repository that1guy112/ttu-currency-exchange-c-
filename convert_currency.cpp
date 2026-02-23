#include <iostream>

#include "conversion_rate.h"
#include "convert_currency.h"
#include "client_user.h"

using namespace std;

client_user clientUser;

double convert_currency::convert_currency_func(
    const std::string& fromCurrency,
    const std::string& toCurrency,
    double amount)
{
    conversion_rate conversion;
    // example implementation: cover return on all paths
    if (fromCurrency == "USD" && toCurrency == "EUR") {
        clientUser.usdAmount -= amount;
        return amount * conversion.EUR_CONVERSION_RATE;
    } else if (fromCurrency == "EUR" && toCurrency == "USD") {
        clientUser.eurAmount -= amount;
        return amount * conversion.USD_CONVERSION_RATE;
    } else if (fromCurrency == "EUR")

    // fallback: if no conversion rule matched, return original amount (or throw)
    return amount;
}