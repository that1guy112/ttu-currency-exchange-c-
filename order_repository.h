#ifndef ORDER_REPOSITORY_H
#define ORDER_REPOSITORY_H

#include <string>
#include <vector>

enum class CurrencyPair {
    EUR_TO_USD,
    USD_TO_EUR
};

struct Order {
    int id;
    CurrencyPair pair;
    double amountIn;
    double amountOut;
    double rate;
    bool completed;
    std::string receipt;
};

class OrderRepository {
private:
    static std::vector<Order> orders;
    static int nextId;

public:
    static int addOrder(CurrencyPair pair, double amountIn, double amountOut, double rate);
    static void completeOrder(int id);

    static std::vector<Order> getOngoingOrders();
    static std::vector<Order> getCompletedOrders();
    static const std::vector<Order>& getAllOrders();
};

#endif
