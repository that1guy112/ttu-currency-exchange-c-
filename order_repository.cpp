#include "order_repository.h"
#include <sstream>

std::vector<Order> OrderRepository::orders;
int OrderRepository::nextId = 1;

int OrderRepository::addOrder(CurrencyPair pair, double amountIn, double amountOut, double rate) {
    std::ostringstream receipt;
    receipt << "Order #" << nextId << " | "
            << (pair == CurrencyPair::EUR_TO_USD ? "EUR to USD" : "USD to EUR")
            << "In: " << amountIn
            << "Out: " << amountOut
            << "Rate: " << rate;

    Order o;
    o.id = nextId++;
    o.pair = pair;
    o.amountIn = amountIn;
    o.amountOut = amountOut;
    o.rate = rate;
    o.completed = false;
    o.receipt = receipt.str();

    orders.push_back(o);
    return o.id;
}

void OrderRepository::completeOrder(int id) {
    for (Order& o : orders) {
        if (o.id == id) {
            o.completed = true;
            return;
        }
    }
}

std::vector<Order> OrderRepository::getOngoingOrders() {
    std::vector<Order> result;
    for (const Order& o : orders) {
        if (!o.completed) result.push_back(o);
    }
    return result;
}

std::vector<Order> OrderRepository::getCompletedOrders() {
    std::vector<Order> result;
    for (const Order& o : orders) {
        if (o.completed) result.push_back(o);
    }
    return result;
}

const std::vector<Order>& OrderRepository::getAllOrders() {
    return orders;
}
