#include "exchange_manager.h"
#include "currency_repository.h"
#include <iostream>
#include <iomanip>

int ExchangeManager::processExchange(CurrencyPair pair, double amount) {
    double rate;
    double amountOut;

    if (pair == CurrencyPair::EUR_TO_USD) {
        rate = CurrencyRepository::getEurToUsdRate();
        amountOut = amount * rate;
        CurrencyRepository::modifyEurReserve(amount);
        CurrencyRepository::modifyUsdReserve(-amountOut);
    } else {
        rate = CurrencyRepository::getUsdToEurRate();
        amountOut = amount * rate;
        CurrencyRepository::modifyUsdReserve(amount);
        CurrencyRepository::modifyEurReserve(-amountOut);
    }

    double commission = amountOut * 0.01; // 1% commission
    CurrencyRepository::addProfit(commission);

    int id = OrderRepository::addOrder(pair, amount, amountOut, rate);
    OrderRepository::completeOrder(id);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Exchange successful! You receive: " << amountOut
              << (pair == CurrencyPair::EUR_TO_USD ? " USD" : " EUR")
              << " (commission: " << commission << ")\n";

    return id;
}

void ExchangeManager::viewOngoingOrders() {
    std::vector<Order> ongoing = OrderRepository::getOngoingOrders();
    if (ongoing.empty()) {
        std::cout << "No ongoing orders.\n";
        return;
    }
    for (const Order& o : ongoing) {
        std::cout << o.receipt << " [PENDING]\n";
    }
}

void ExchangeManager::viewReceipts() {
    std::vector<Order> completed = OrderRepository::getCompletedOrders();
    if (completed.empty()) {
        std::cout << "No receipts available.\n";
        return;
    }
    for (const Order& o : completed) {
        std::cout << o.receipt << " [COMPLETED]\n";
    }
}

void ExchangeManager::viewAllOrders() {
    const std::vector<Order>& all = OrderRepository::getAllOrders();
    if (all.empty()) {
        std::cout << "No orders found.\n";
        return;
    }
    for (const Order& o : all) {
        std::cout << o.receipt
                  << (o.completed ? " [COMPLETED]" : " [PENDING]") << "\n";
    }
}

void ExchangeManager::viewReserves() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "EUR Reserve: " << CurrencyRepository::getEurReserve() << " EUR\n";
    std::cout << "USD Reserve: " << CurrencyRepository::getUsdReserve() << " USD\n";
}

void ExchangeManager::submitSummaryReport() {
    //TODO:
}

void ExchangeManager::setExchangeRate(CurrencyPair pair, double newRate) {
    if (pair == CurrencyPair::EUR_TO_USD) {
        CurrencyRepository::setEurToUsdRate(newRate);
        std::cout << "EUR to USD rate updated to " << newRate << "\n";
    } else {
        CurrencyRepository::setUsdToEurRate(newRate);
        std::cout << "USD to EUR rate updated to " << newRate << "\n";
    }
}

void ExchangeManager::modifyReserve(CurrencyPair pair, double amount) {
    if (pair == CurrencyPair::EUR_TO_USD) {
        CurrencyRepository::modifyEurReserve(amount);
        std::cout << "EUR reserve adjusted by " << amount << "\n";
    } else {
        CurrencyRepository::modifyUsdReserve(amount);
        std::cout << "USD reserve adjusted by " << amount << "\n";
    }
}

bool ExchangeManager::awardCashierBonus() {
    double bonus = CurrencyRepository::getTotalProfit() * 0.05;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Cashier bonus awarded: " << bonus << " (5% of total profit: "
              << CurrencyRepository::getTotalProfit() << ")\n";
    return true;
}
