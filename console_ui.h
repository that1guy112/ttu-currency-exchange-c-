#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

enum class Role {
    CLIENT     = 1,
    CASHIER    = 2,
    MANAGEMENT = 3,
    EXIT       = 9
};

enum class ClientAction {
    EXCHANGE_CURRENCY = 1,
    VIEW_ORDERS       = 2,
    BACK              = 9
};

enum class ClientOrderView {
    ONGOING  = 1,
    RECEIPTS = 2,
    BACK     = 9
};

enum class CashierAction {
    VIEW_ORDERS   = 1,
    VIEW_RESERVES = 2,
    SUBMIT_REPORT = 3,
    BACK          = 9
};

enum class ManagementAction {
    SET_RATES       = 1,
    MODIFY_RESERVES = 2,
    AWARD_BONUS     = 3,
    BACK            = 9
};

enum class CurrencyOption {
    EUR_TO_USD = 1,
    USD_TO_EUR = 2,
    BACK       = 9
};

class ConsoleUI {
public:
    void run();

private:
    void handleClient();
    void handleCashier();
    void handleManagement();

    void handleClientExchange();
    void handleClientOrders();

    void handleManagementRates();
    void handleManagementReserves();
};

#endif
