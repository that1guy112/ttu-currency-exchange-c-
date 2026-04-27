#ifndef EXCHANGE_MANAGER_H
#define EXCHANGE_MANAGER_H

#include "ireportable.h"
#include "order_repository.h"
#include <string>
#include <vector>

class SummaryReport : public IReportable {
public:
    double eurReserve;
    double usdReserve;
    double totalProfit;
    int orderCount;

    // Postcondition: returns a non-empty, human-readable report string.
    std::string generateReport() const override;
};

class ExchangeManager {
public:
    // Client operations

    static int processExchange(CurrencyPair pair, double amount);

    // Postcondition: returns formatted list of ongoing orders (may be empty)
    static std::vector<std::string> getOngoingOrderLines();

    // Postcondition: returns formatted list of completed orders (may be empty)
    static std::vector<std::string> getReceiptLines();

    // Cashier operations

    // Postcondition: returns formatted list of all orders (may be empty)
    static std::vector<std::string> getAllOrderLines();

    // Postcondition: returns current reserve values as formatted strings
    static std::vector<std::string> getReserveLines();

    // Postcondition: returns a SummaryReport populated with current system state
    static SummaryReport buildSummaryReport();

    // Management operations

    // Precondition: newRate > 0
    // Postcondition: rate stored in CurrencyRepository updated
    static void setExchangeRate(CurrencyPair pair, double newRate);

    // Precondition: resulting reserve >= 0
    // Postcondition: reserve adjusted by amount
    // Throws: InsufficientReserve (Repository) - result would go negative
    static void modifyReserve(CurrencyPair pair, double amount);

    // Postcondition: returns bonus amount (5% of totalProfit); does not deduct from profit
    static double computeCashierBonus();
};

#endif
