#ifndef ORDER_REPOSITORY_H
#define ORDER_REPOSITORY_H

#include "ireportable.h"
#include <string>
#include <vector>

enum class CurrencyPair {
    EUR_TO_USD,
    USD_TO_EUR
};

struct Order : public IReportable {
    int id;
    CurrencyPair pair;
    double amountIn;
    double amountOut;
    double rate;
    bool completed;
    std::string receipt;

    // Postcondition: returns a non-empty summary string.
    std::string generateReport() const override { return receipt; }
};

class OrderRepository {
private:
    static std::vector<Order> orders;
    static int nextId;

public:
    // Precondition:  amountIn > 0, amountOut > 0, rate > 0
    // Postcondition: order added to internal store; returns new order id
    static int addOrder(CurrencyPair pair, double amountIn, double amountOut, double rate);

    // Precondition:  id refers to an existing order
    // Postcondition: order.completed == true
    static void completeOrder(int id);

    static std::vector<Order> getOngoingOrders();
    static std::vector<Order> getCompletedOrders();
    static const std::vector<Order>& getAllOrders();
};

#endif
