#include "exchange_manager.h"
#include "currency_repository.h"
#include "exchange_exceptions.h"
#include <sstream>
#include <iomanip>

// SummaryReport::generateReport — IReportable implementation
std::string SummaryReport::generateReport() const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "=== Summary Report ===\n";
    ss << "EUR Reserve : " << eurReserve  << " EUR\n";
    ss << "USD Reserve : " << usdReserve  << " USD\n";
    ss << "Total Profit: " << totalProfit << "\n";
    ss << "Orders      : " << orderCount  << "\n";
    ss << "=====================\n";
    return ss.str();
}


int ExchangeManager::processExchange(CurrencyPair pair, double amount) {
    // Precondition: amount must be positive
    if (amount <= 0)
        throw InvalidData("Amount must be positive.");

    double rate;
    double amountOut;

    if (pair == CurrencyPair::EUR_TO_USD) {
        rate = CurrencyRepository::getEurToUsdRate();
        amountOut = amount * rate;

        // Postcondition guard: result must be positive
        if (amountOut <= 0)
            throw LogicError("Conversion result invalid. Check exchange rate.");

        // Repository layer - throws InsufficientReserve if USD reserve too low
        CurrencyRepository::modifyUsdReserve(-amountOut);
        CurrencyRepository::modifyEurReserve(amount);
    } else {
        rate = CurrencyRepository::getUsdToEurRate();
        amountOut = amount * rate;

        //Postcondition guard: result must be positive
        if (amountOut <= 0)
            throw LogicError("Conversion result invalid. Check exchange rate.");

        // Repository layer - throws InsufficientReserve if EUR reserve too low
        CurrencyRepository::modifyEurReserve(-amountOut);
        CurrencyRepository::modifyUsdReserve(amount);
    }

    double commission = amountOut * 0.01; // 1% commission
    CurrencyRepository::addProfit(commission);

    int id = OrderRepository::addOrder(pair, amount, amountOut, rate);
    OrderRepository::completeOrder(id);

    return id;
}

std::vector<std::string> ExchangeManager::getOngoingOrderLines() {
    std::vector<Order>  ongoing = OrderRepository::getOngoingOrders();
    std::vector<std::string> lines;
    for (const Order& o : ongoing)
        lines.push_back(o.generateReport() + " [PENDING]");
    return lines;
}

std::vector<std::string> ExchangeManager::getReceiptLines() {
    std::vector<Order>  completed = OrderRepository::getCompletedOrders();
    std::vector<std::string> lines;
    for (const Order& o : completed)
        lines.push_back(o.generateReport() + " [COMPLETED]");
    return lines;
}

std::vector<std::string> ExchangeManager::getAllOrderLines() {
    const std::vector<Order>& all = OrderRepository::getAllOrders();
    std::vector<std::string> lines;
    for (const Order& o : all)
        lines.push_back(o.generateReport() +
                        (o.completed ? " [COMPLETED]" : " [PENDING]"));
    return lines;
}

std::vector<std::string> ExchangeManager::getReserveLines() {
    std::ostringstream eur, usd;
    eur << std::fixed << std::setprecision(2)
        << "EUR Reserve: " << CurrencyRepository::getEurReserve() << " EUR";
    usd << std::fixed << std::setprecision(2)
        << "USD Reserve: " << CurrencyRepository::getUsdReserve() << " USD";
    return { eur.str(), usd.str() };
}

SummaryReport ExchangeManager::buildSummaryReport() {
    SummaryReport report;
    report.eurReserve = CurrencyRepository::getEurReserve();
    report.usdReserve = CurrencyRepository::getUsdReserve();
    report.totalProfit = CurrencyRepository::getTotalProfit();
    report.orderCount = static_cast<int>(OrderRepository::getAllOrders().size());
    return report;
}

// Precondition:  newRate > 0 - throws InvalidData if violated
// Postcondition: stored rate == newRate
void ExchangeManager::setExchangeRate(CurrencyPair pair, double newRate) {
    if (newRate <= 0)
        throw InvalidData("Exchange rate must be positive.");

    if (pair == CurrencyPair::EUR_TO_USD)
        CurrencyRepository::setEurToUsdRate(newRate);
    else
        CurrencyRepository::setUsdToEurRate(newRate);
}

// Throws InsufficientReserve (propagated from Repository) if result < 0
void ExchangeManager::modifyReserve(CurrencyPair pair, double amount) {
    if (pair == CurrencyPair::EUR_TO_USD)
        CurrencyRepository::modifyEurReserve(amount);
    else
        CurrencyRepository::modifyUsdReserve(amount);
}

double ExchangeManager::computeCashierBonus() {
    return CurrencyRepository::getTotalProfit() * 0.05;
}
