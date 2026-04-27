#ifndef CURRENCY_REPOSITORY_H
#define CURRENCY_REPOSITORY_H

#include "exchange_exceptions.h"
#include <string>

class CurrencyRepository {
private:
    static double eurToUsdRate;
    static double usdToEurRate;

    static double eurReserve;
    static double usdReserve;

    static double totalProfit;

public:
    // Exchange rates
    // Precondition:  rate > 0
    // Postcondition: stored rate == rate
    static double getEurToUsdRate();
    static double getUsdToEurRate();
    static void setEurToUsdRate(double rate);
    static void setUsdToEurRate(double rate);

    // Reserves
    // Precondition (modifyEurReserve / modifyUsdReserve):
    //   resulting reserve >= 0; throws InsufficientReserve otherwise
    // Postcondition: reserve updated by amount
    static double getEurReserve();
    static double getUsdReserve();
    static void modifyEurReserve(double amount);
    static void modifyUsdReserve(double amount);

    // Profit tracking
    static double getTotalProfit();

    // Precondition:  amount >= 0
    // Postcondition: totalProfit increased by amount
    static void addProfit(double amount);
};

#endif
