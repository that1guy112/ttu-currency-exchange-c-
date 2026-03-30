#ifndef EXCHANGE_MANAGER_H
#define EXCHANGE_MANAGER_H

#include "order_repository.h"

class ExchangeManager {
public:
    // Client operations
    static int processExchange(CurrencyPair pair, double amount);
    static void viewOngoingOrders();
    static void viewReceipts();

    // Cashier operations
    static void viewAllOrders();
    static void viewReserves();
    static void submitSummaryReport();

    // Management operations
    static void setExchangeRate(CurrencyPair pair, double newRate);
    static void modifyReserve(CurrencyPair pair, double amount);
    static bool awardCashierBonus();
};

#endif
