#include <iostream>
#include "convert_currency.h"
#include "client_user.h"
#include "management.h"

using namespace std;
int weLooping = 1;
int roleSelection;

int clientAction; // VARIABLES RELATED TO CLIENT ACTIVITY
int clientCurrencyOption;
int clientOrderOption;

int cashierAction; // VARIABLES RELATED TO CASHIER ACTIVITY
int cashierOrderOption;
int cashierReservesOption;
int cashierSummaryOption;

int managementAction; // VARIABLES RELATED TO MANAGEMENT ACTIVITY
int managementReservesOption;
int managementAwardOption;

double amount; //CURRENCY CONVERSION SHENANIGANS
string fromCurrency, toCurrency;

convert_currency convertCurrency;
management management1;

bool exitOption = false;
bool finalExitOption = false;

void client() {
    while (exitOption == false) {
        cout << "You have selected 'Client'\nWhat would you like to do?\n1) Exchange Currency\n2) View Orders\n3) Exit\n------\n";
        cin >> clientAction;
        switch (clientAction) {
            case 1: {
                cout << "Apply for a currency exchange from the currencies listed below:\n  EUR  /  USD  /  JPY\nApply for an exchange by typing in the currencies one after another\n";
                cout << "x ---> y\n";
                cin >> fromCurrency >> toCurrency;
                cout << "Enter the amount of money you would like to convert\n";
                cin >> amount;
                cout << "You have converted " << amount << " " << fromCurrency << " to " << convertCurrency.convert_currency_func(fromCurrency, toCurrency, amount) << " " << toCurrency << "\n";
                break;
            }
            case 2: {
                cout << "What would you like to view?\n1) Ongoing orders\n2) Receipts\n------\n";
                cin >> clientOrderOption;
                break;
            }
            case 3: {
                exitOption = true;
                break;
            }
        }
    }
}

void cashier() {
    while (exitOption == false) {
        cout << "You have selected 'Cashier'\nWhat would you like to do?\n1) View Currency Exchange Orders\n2) View Currency Reserves\n3) Submit Summary Report\n4) Exit\n------\n";
        cin >> cashierAction;
        switch (cashierAction) {
            case 1: {
                cout << "Viewing orders for currency exchanges\n";
                break;
            }
            case 2: {
                cout << "Viewing reserves for currency exchanges\n";
                break;
            }
            case 3: {
                cout << "Creating daily summary report\n";
                break;
            }
            case 4: {
                exitOption = true;
                break;
            }
        }
    }
}


    int main () {
    // THE MAIN LOOP UNDER WHICH THE PROGRAM RUNS
    while (finalExitOption == false) {
        cout << "Welcome to the Home Page!\nPlease select your role:\n1) Client\n2) Cashier\n3) Management\n9) Exit the program.\n------\n";
        cin >> roleSelection;
        switch (roleSelection) {
            case 1: {
                client();
                break;
            }
            case 2: {
                cashier();
                break;
            }
        }
    }
    return 0;
}







/*int main () { // THE MAIN LOOP UNDER WHICH THE PROGRAM RUNS
    while (weLooping == 1) { // HOME PAGE ROLE SELECTION
        cout << "Welcome to the Home Page\nPlease select your role:\n1) Client\n2) Cashier\n3) Management\n9) Exit the program.\n------\n";
        cin >> roleSelection;
        if (roleSelection == 1) { // THE CLIENT VARIATION
            cout << "You have selected 'Client'\nWhat would you like to do?\n1) Exchange Currency\n2) View Orders\n------\n";
            cin >> clientAction;
            if (clientAction == 1) {
                cout << "Apply for a currency exchange from the currencies listed below:\n  EUR  /  USD  /  JPY\nApply for an exchange by typing in the currencies one after another\n";
                cout << "x ---> y\n";
                cin >> fromCurrency >> toCurrency;
                cout << "Enter the amount of money you would like to convert\n";
                cin >> amount;
                cout << "You have converted " << amount << " " << fromCurrency << " to " << convertCurrency.convert_currency_func(fromCurrency, toCurrency, amount) << " " << toCurrency << "\n";
            }
            else if (clientAction == 2) {
                cout << "What would you like to view?\n1) Ongoing orders\n2) Receipts\n------\n";
                cin >> clientOrderOption;
            }
        }
        else if (roleSelection == 2) { // THE CASHIER VARIATION
            cout << "You have selected 'Cashier'\nWhat would you like to do?\n1) View Currency Exchange Orders\n2) View Currency Reserves\n3) Submit Summary Report\n------\n";
            cin >> cashierAction;
            if (cashierAction == 1) {
                cout << "Viewing orders for currency exchanges\n";
                cin >> cashierOrderOption;
            }
            else if (cashierAction == 2) {
                cout << "Viewing reserves for currency exchanges\n";
                cin >> cashierReservesOption;
            }
            else if (cashierAction == 3) {
                cout << "Creating daily summary report\n";
                cin >> cashierSummaryOption;
            }
        }
        else if (roleSelection == 3) { // THE MANAGEMENT VARIATION
            cout << "You have selected 'Management'\nWhat would you like to do?\n1) Set exchange rates\n2) Modify reserves\n3) Award the Cashier a monthly bonus\n------\n";
            cin >> managementAction;
            if (managementAction == 1) {
                cout << "What currencies exchange rate would you like to change?\n---------------------\nEUR  /  USD   /  JPY\n---------------------\n";
                string rateChangeCurrency;
                double newExchangeRate;
                cin >> rateChangeCurrency;
                cout << "What would you like the new exchange rate to be?\n";
                cin >> newExchangeRate;
                cout << "The new exchange rate for " << rateChangeCurrency << " is " << newExchangeRate << "\n";
                management1.change_conversion_rate(rateChangeCurrency, newExchangeRate);

            }
            else if (managementAction == 2) {
                cout << "Which currencies reserves would you like to modify?\n1) EUR\n2) USD\n------\n";
                cin >> managementReservesOption;
            }
            else if (managementAction == 3) {
                cout << "Would you like to award the cashier a monthly bonus of 5% of the profits?\n1) Yes\n2) No\n------\n";
                cin >> managementAwardOption;
            }
        }
        else if (roleSelection == 9) { // EXITING THE PROGRAM
            weLooping = 0;
        }
        else {
            cout << "You have entered an incorrect option, please try again.\n";
        }
    }

return 0;
}*/