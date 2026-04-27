#include "console_ui.h"
#include "exchange_manager.h"
#include "currency_repository.h"
#include "order_repository.h"
#include "exchange_exceptions.h"
#include <iostream>
#include <limits>
#include <iomanip>


// Attempts to read one int from cin.
// Throws InvalidInput if the stream fails (non-numeric input).
static int tryReadInt() {
    int value;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInput("Please enter a valid number.");
    }
    return value;
}

// Attempts to read one positive double from cin.
// Throws InvalidInput if the stream fails or the value is not positive.
static double tryReadPositiveDouble() {
    double value;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInput("Please enter a valid number.");
    }
    if (value <= 0)
        throw InvalidInput("Please enter a positive number.");
    return value;
}

// Attempts to read any double (positive or negative) from cin.
// Throws InvalidInput if the stream fails.
static double tryReadAnyDouble() {
    double value;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInput("Please enter a valid number.");
    }
    return value;
}

static int readInt() {
    while (true) {
        try {
            return tryReadInt();
        } catch (const InvalidInput& e) {
            std::cout << e.what() << " Try again: ";
        }
    }
}

static double readPositiveDouble() {
    while (true) {
        try {
            return tryReadPositiveDouble();
        } catch (const InvalidInput& e) {
            std::cout << e.what() << " Try again: ";
        }
    }
}

static double readAnyDouble() {
    while (true) {
        try {
            return tryReadAnyDouble();
        } catch (const InvalidInput& e) {
            std::cout << e.what() << " Try again: ";
        }
    }
}

// Main loop

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
        Role role = static_cast<Role>(choice);

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
            case ClientAction::EXCHANGE_CURRENCY:
                handleClientExchange();
                break;
            case ClientAction::VIEW_ORDERS:
                handleClientOrders();
                break;
            case ClientAction::BACK:
                inMenu = false;
                break;
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

        int choice        = readInt();
        CurrencyOption co = static_cast<CurrencyOption>(choice);

        if (co == CurrencyOption::BACK) { inMenu = false; break; }

        CurrencyPair pair;
        if (co == CurrencyOption::EUR_TO_USD)
            pair = CurrencyPair::EUR_TO_USD;
        else if (co == CurrencyOption::USD_TO_EUR)
            pair = CurrencyPair::USD_TO_EUR;
        else {
            std::cout << "Invalid option.\n"; continue;
        }

        std::cout << "Enter amount to exchange: ";
        double amount = readPositiveDouble();

        //   InvalidData   — Logic rule violated (amount <= 0, bad rate)
        //   LogicError    — Postcondition failed (result <= 0)
        //   InsufficientReserve — Repository cannot fulfill the request
        try {
            int id = ExchangeManager::processExchange(pair, amount);
            const std::vector<Order>& all = OrderRepository::getAllOrders();
            for (const Order& o : all) {
                if (o.id == id) {
                    std::cout << std::fixed << std::setprecision(2);
                    std::cout << "Exchange successful!\n";
                    std::cout << o.generateReport() << "\n"; // polymorphic call
                    break;
                }
            }
        } catch (const InvalidData& e) {
            std::cout << "Check amount or currency. " << e.what() << "\n";
        } catch (const LogicError& e) {
            std::cout << "Operation could not be completed. " << e.what() << "\n";
        } catch (const InsufficientReserve& e) {
            std::cout << "Not enough cash in reserve. " << e.what() << "\n";
        }

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
            case ClientOrderView::ONGOING: {
                std::vector<std::string> lines = ExchangeManager::getOngoingOrderLines();
                if (lines.empty()) std::cout << "No ongoing orders.\n";
                else for (const std::string& l : lines) std::cout << l << "\n";
                inMenu = false;
                break;
            }
            case ClientOrderView::RECEIPTS: {
                std::vector<std::string> lines = ExchangeManager::getReceiptLines();
                if (lines.empty()) std::cout << "No receipts available.\n";
                else for (const std::string& l : lines) std::cout << l << "\n";
                inMenu = false;
                break;
            }
            case ClientOrderView::BACK:
                inMenu = false;
                break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

// ===========================================================================
// Cashier UI
// ===========================================================================

void ConsoleUI::handleCashier() {
    bool inMenu = true;
    while (inMenu) {
        std::cout << "\n[Cashier Menu]\n";
        std::cout << "1) View Currency Exchange Orders\n";
        std::cout << "2) View Currency Reserves\n";
        std::cout << "3) Submit Summary Report\n";
        std::cout << "9) Back\n";
        std::cout << "Choice: ";

        int choice       = readInt();
        CashierAction ca = static_cast<CashierAction>(choice);

        switch (ca) {
            case CashierAction::VIEW_ORDERS: {
                std::vector<std::string> lines = ExchangeManager::getAllOrderLines();
                if (lines.empty()) std::cout << "No orders found.\n";
                else for (const std::string& l : lines) std::cout << l << "\n";
                inMenu = false;
                break;
            }
            case CashierAction::VIEW_RESERVES: {
                std::vector<std::string> lines = ExchangeManager::getReserveLines();
                for (const std::string& l : lines) std::cout << l << "\n";
                inMenu = false;
                break;
            }
            case CashierAction::SUBMIT_REPORT: {
                // buildSummaryReport returns SummaryReport (IReportable).
                // Polymorphic call — UI uses the interface, not the concrete type.
                SummaryReport report = ExchangeManager::buildSummaryReport();
                std::cout << report.generateReport();
                inMenu = false;
                break;
            }
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
            case ManagementAction::AWARD_BONUS: {
                std::cout << "Award cashier 5% of profits?\n  1) Yes\n  2) No\nChoice: ";
                if (readInt() == 1) {
                    double bonus = ExchangeManager::computeCashierBonus();
                    std::cout << std::fixed << std::setprecision(2);
                    std::cout << "Cashier bonus awarded: " << bonus
                              << " (5% of total profit: "
                              << CurrencyRepository::getTotalProfit() << ")\n";
                }
                inMenu = false;
                break;
            }
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
    if (co == CurrencyOption::EUR_TO_USD)
        pair = CurrencyPair::EUR_TO_USD;
    else if (co == CurrencyOption::USD_TO_EUR)
        pair = CurrencyPair::USD_TO_EUR;
    else {
        std::cout << "Invalid option.\n"; return;
    }

    std::cout << "Enter new rate: ";
    double rate = readPositiveDouble();

    // InvalidData thrown by Logic if rate <= 0.
    // Caught here at UI layer — message shown, operation stopped.
    try {
        ExchangeManager::setExchangeRate(pair, rate);
        std::cout << "Rate updated to " << rate << "\n";
    } catch (const InvalidData& e) {
        std::cout << "Check amount or currency. " << e.what() << "\n";
    }
}

void ConsoleUI::handleManagementReserves() {
    std::cout << "\n[Modify Reserve]\n";
    std::cout << "1) EUR\n";
    std::cout << "2) USD\n";
    std::cout << "Choice: ";

    int choice = readInt();
    CurrencyOption co = static_cast<CurrencyOption>(choice);

    CurrencyPair pair;
    if (co == CurrencyOption::EUR_TO_USD)
        pair = CurrencyPair::EUR_TO_USD;
    else if (co == CurrencyOption::USD_TO_EUR)
        pair = CurrencyPair::USD_TO_EUR;
    else {
        std::cout << "Invalid option.\n"; return;
    }

    std::cout << "Enter amount to add (use negative to subtract): ";
    double amount = readAnyDouble();

    // InsufficientReserve thrown by Repository if result < 0.
    // Caught here at UI layer — message shown, operation stopped.
    try {
        ExchangeManager::modifyReserve(pair, amount);
        std::cout << "Reserve adjusted by " << amount << "\n";
    } catch (const InsufficientReserve& e) {
        std::cout << "Not enough cash in reserve. " << e.what() << "\n";
    }
}
