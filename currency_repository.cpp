#include "currency_repository.h"

// Default exchange rates (only hardcoded values allowed)
double CurrencyRepository::eurToUsdRate = 1.08;
double CurrencyRepository::usdToEurRate = 0.93;

// Starting reserves
double CurrencyRepository::eurReserve = 10000.0;
double CurrencyRepository::usdReserve = 10000.0;

double CurrencyRepository::totalProfit = 0.0;

double CurrencyRepository::getEurToUsdRate() { return eurToUsdRate; }
double CurrencyRepository::getUsdToEurRate() { return usdToEurRate; }

void CurrencyRepository::setEurToUsdRate(double rate) { eurToUsdRate = rate; }
void CurrencyRepository::setUsdToEurRate(double rate) { usdToEurRate = rate; }

double CurrencyRepository::getEurReserve() { return eurReserve; }
double CurrencyRepository::getUsdReserve() { return usdReserve; }

void CurrencyRepository::modifyEurReserve(double amount) { eurReserve += amount; }
void CurrencyRepository::modifyUsdReserve(double amount) { usdReserve += amount; }

double CurrencyRepository::getTotalProfit() { return totalProfit; }
void CurrencyRepository::addProfit(double amount) { totalProfit += amount; }
