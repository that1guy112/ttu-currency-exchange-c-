#include "console_ui.h"
#include "exchange_manager.h"
#include "currency_repository.h"
#include "order_repository.h"
#include <iostream>
#include <limits>

// Clears the terminal window
static void clearInvalidInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int readInt() {
    int value;
    while (!(std::cin >> value)) {
        clearInvalidInput();
        std::cout << "Invalid input. Please enter a number: ";
    }
    return value;
}

static double readDouble() {
    double value;
    while (!(std::cin >> value) || value <= 0) {
        clearInvalidInput();
        std::cout << "Invalid input. Please enter a positive number: ";
    }
    return value;
}

// What the user sees on startup
void ConsoleUI::run() {
    bool running = true;
    while (running) {
        std::cout << "Please select your role:\n";
        std::cout << "1) Client\n";
        std::cout << "2) Cashier\n";
        std::cout << "3) Management\n";
        std::cout << "9) Exit\n";
        std::cout << "-----------------\n";
        std::cout << "Choice: ";

        int choice = readInt();
        Role role  = static_cast<Role>(choice);

        switch (role) {
            case Role::CLIENT:
                handleClient();
                break;
            case Role::CASHIER:
                handleCashier();
                break;
            case Role::MANAGEMENT:
                handleManagement();
                break;
            case Role::EXIT:
                running = false;
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    }
}

// Client UI
void ConsoleUI::handleClient() {
    bool inMenu = true;
    while (inMenu) {
        std::cout << "\n[Client Menu]\n";
        std::cout << "1) Exchange Currency\n";
        std::cout << "2) View Orders\n";
        std::cout << "9) Back\n";
        std::cout << "Choice: ";

        int choice      = readInt();
        ClientAction ca = static_cast<ClientAction>(choice);

        switch (ca) {
            case ClientAction::EXCHANGE_CURRENCY: handleClientExchange(); break;
            case ClientAction::VIEW_ORDERS:       handleClientOrders();   break;
            case ClientAction::BACK:              inMenu = false;         break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }
}

void ConsoleUI::handleClientExchange() {
    bool inMenu = true;
    while (inMenu) {
        std::cout << "\n[Currency Exchange]\n";
        std::cout << "1) EUR to USD (rate: "
                  << CurrencyRepository::getEurToUsdRate() << ")\n";
        std::cout << "2) USD to EUR (rate: "
                  << CurrencyRepository::getUsdToEurRate() << ")\n";
        std::cout << "9) Back\n";
        std::cout << "Choice: ";

        int choice = readInt();
        CurrencyOption co = static_cast<CurrencyOption>(choice);

        if (co == CurrencyOption::BACK) { inMenu = false; break; }

        CurrencyPair pair;
        if (co == CurrencyOption::EUR_TO_USD)
            pair = CurrencyPair::EUR_TO_USD;
        else if (co == CurrencyOption::USD_TO_EUR)
            pair = CurrencyPair::USD_TO_EUR;
        else
        {
            std::cout << "Invalid option.\n"; continue;
        }

        std::cout << "Enter amount to exchange: ";
        double amount = readDouble();
        ExchangeManager::processExchange(pair, amount);
        inMenu = false;
    }
}

void ConsoleUI::handleClientOrders() {
    bool inMenu = true;
    while (inMenu) {
        std::cout << "\n[View Orders]\n";
        std::cout << "1) Ongoing orders\n";
        std::cout << "2) Receipts\n";
        std::cout << "9) Back\n";
        std::cout << "Choice: ";

        int choice = readInt();
        ClientOrderView cv = static_cast<ClientOrderView>(choice);

        switch (cv) {
            case ClientOrderView::ONGOING:
                ExchangeManager::viewOngoingOrders(); inMenu = false;
                break;
            case ClientOrderView::RECEIPTS:
                ExchangeManager::viewReceipts();
                inMenu = false;
                break;
            case ClientOrderView::BACK:
                inMenu = false;
                break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

// Cashier UI
void ConsoleUI::handleCashier() {
    bool inMenu = true;
    while (inMenu) {
        std::cout << "\n[Cashier Menu]\n";
        std::cout << "1) View Currency Exchange Orders\n";
        std::cout << "2) View Currency Reserves\n";
        std::cout << "3) Submit Summary Report\n";
        std::cout << "9) Back\n";
        std::cout << "Choice: ";

        int choice = readInt();
        CashierAction ca = static_cast<CashierAction>(choice);

        switch (ca) {
            case CashierAction::VIEW_ORDERS:
                ExchangeManager::viewAllOrders();
                inMenu = false;
                break;
            case CashierAction::VIEW_RESERVES:
                ExchangeManager::viewReserves();
                inMenu = false;
                break;
            case CashierAction::SUBMIT_REPORT:
                ExchangeManager::submitSummaryReport();
                inMenu = false;
                break;
            case CashierAction::BACK:
                inMenu = false;
                break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

// Management UI
void ConsoleUI::handleManagement() {
    bool inMenu = true;
    while (inMenu) {
        std::cout << "\n[Management Menu]\n";
        std::cout << "1) Set Exchange Rates\n";
        std::cout << "2) Modify Reserves\n";
        std::cout << "3) Award Cashier Bonus\n";
        std::cout << "9) Back\n";
        std::cout << "Choice: ";

        int choice = readInt();
        ManagementAction ma = static_cast<ManagementAction>(choice);

        switch (ma) {
            case ManagementAction::SET_RATES:
                handleManagementRates();
                inMenu = false;
                break;
            case ManagementAction::MODIFY_RESERVES:
                handleManagementReserves();
                inMenu = false;
                break;
            case ManagementAction::AWARD_BONUS:
                std::cout << "Award cashier 5% of profits?\n  1) Yes\n  2) No\nChoice: ";
                if (readInt() == 1) ExchangeManager::awardCashierBonus();
                inMenu = false;
                break;
            case ManagementAction::BACK:
                inMenu = false;
                break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

void ConsoleUI::handleManagementRates() {
    std::cout << "\n[Set Exchange Rate]\n";
    std::cout << "1) EUR to USD\n";
    std::cout << "2) USD to EUR\n";
    std::cout << "Choice: ";

    int choice = readInt();
    CurrencyOption co = static_cast<CurrencyOption>(choice);

    CurrencyPair pair;
    if (co == CurrencyOption::EUR_TO_USD) {
        pair = CurrencyPair::EUR_TO_USD;
    }
    else if (co == CurrencyOption::USD_TO_EUR) {
        pair = CurrencyPair::USD_TO_EUR;
    }
    else {
        std::cout << "Invalid option.\n"; return;
    }

    std::cout << "Enter new rate: ";
    double rate = readDouble();
    ExchangeManager::setExchangeRate(pair, rate);
}

void ConsoleUI::handleManagementReserves() {
    std::cout << "\n[Modify Reserve]\n";
    std::cout << "1) EUR\n";
    std::cout << "2) USD\n";
    std::cout << "Choice: ";

    int choice = readInt();
    CurrencyOption co = static_cast<CurrencyOption>(choice);

    CurrencyPair pair;
    if (co == CurrencyOption::EUR_TO_USD) {
        pair = CurrencyPair::EUR_TO_USD;
    }
    else if (co == CurrencyOption::USD_TO_EUR) {
        pair = CurrencyPair::USD_TO_EUR;
    }
    else {
        std::cout << "Invalid option.\n"; return;
    }

    std::cout << "Enter amount to add (use negative to subtract): ";
    double amount;
    std::cin >> amount;
    ExchangeManager::modifyReserve(pair, amount);
}
