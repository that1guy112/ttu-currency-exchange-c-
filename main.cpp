#include <iostream>
#include "convert_currency.h"
#include "client_user.h"
#include "management.h"

using namespace std;
int weLooping = 1;
int roleSelection;

int clientAction; // VARIABLES RELATED TO CLIENT ACTIVITY

int cashierAction; // VARIABLES RELATED TO CASHIER ACTIVITY

int managementAction; // VARIABLES RELATED TO MANAGEMENT ACTIVITY

convert_currency convertCurrency;
management managementConversion;

bool exitOption = false;
bool finalExitOption = false;

void client() {
    while (exitOption == false) {
        cout << "------\nYou have selected 'Client'\nWhat would you like to do?\n1) Exchange Currency\n2) View Orders\n9) Exit\n------\n";
        cin >> clientAction;
        switch (clientAction) {
            case 1: {
                double amount;
                string fromCurrency, toCurrency;
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
                break;
            }
            case 9: {
                exitOption = true;
                break;
            }
        }
    }
}

void cashier() {
    while (exitOption == false) {
        cout << "------\nYou have selected 'Cashier'\nWhat would you like to do?\n1) View Currency Exchange Orders\n2) View Currency Reserves\n3) Submit Summary Report\n9) Exit\n------\n";
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
            case 9: {
                exitOption = true;
                break;
            }
        }
    }
}

void management() {
    while (exitOption == false) {
        cout << "------\nYou have selected 'Management'\nWhat would you like to do?\n1) Set exchange rates\n2) Modify reserves\n3) Award the Cashier a monthly bonus\n9) Exit\n------\n";
        cin >> managementAction;
        switch (managementAction) {
            case 1: {
                string rateChangeCurrency;
                double newExchangeRate;
                cout << "What currencies exchange rate would you like to change?\n---------------------\nEUR  /  USD   /  JPY\n---------------------\n";
                cin >> rateChangeCurrency;
                cout << "What would you like the new exchange rate to be?\n";
                cin >> newExchangeRate;
                cout << "The new exchange rate for " << rateChangeCurrency << " is " << newExchangeRate << "\n";
                managementConversion.change_conversion_rate(rateChangeCurrency, newExchangeRate);
                break;
            }
            case 2: {
                cout << "Which currencies reserves would you like to modify?\n1) EUR\n2) USD\n------\n";
                break;
            }
            case 3: {
                cout << "Would you like to award the cashier a monthly bonus of 5% of the profits?\n1) Yes\n2) No\n------\n";
                break;
            }
            case 9: {
                exitOption = true;
                break;
            }
        }
    }
}

    int main () {
    // THE MAIN LOOP UNDER WHICH THE PROGRAM RUNS
    while (finalExitOption == false) {
        exitOption = false;
        cout << "------\nWelcome to the Home Page!\nPlease select your role:\n1) Client\n2) Cashier\n3) Management\n9) Exit the program.\n------\n";
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
            case 3: {
                management();
                break;
            }
            case 9: {
                finalExitOption = true;
                break;
            }
        }
    }
    return 0;
}