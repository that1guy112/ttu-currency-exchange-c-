#ifndef CURRENCY_REPOSITORY_H
#define CURRENCY_REPOSITORY_H

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
    static double getEurToUsdRate();
    static double getUsdToEurRate();
    static void setEurToUsdRate(double rate);
    static void setUsdToEurRate(double rate);

    // Reserves
    static double getEurReserve();
    static double getUsdReserve();
    static void modifyEurReserve(double amount);
    static void modifyUsdReserve(double amount);

    // Profit tracking
    static double getTotalProfit();
    static void addProfit(double amount);
};

#endif
