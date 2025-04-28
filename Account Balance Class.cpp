#include <iostream>
using namespace std;

/*
Code Artifact: AccountBalance
Description: Creates and manages Account Balance entities
Programmer: Đạt Trịnh
Date Programmed: April 27, 2025
Variables: currentBalance: stores the current balance of the account,
           balanceHolderID: stores the ID of the account holder
Files Accessed: None
Files Changed: None
*/

// AccountBalance class
class AccountBalance {
private:
    float currentBalance;
    int balanceHolderID;

public:
    // Constructor
    AccountBalance(float balance, int holderID) {
        currentBalance = balance;
        balanceHolderID = holderID;
    }

    // Function to get the current balance
    float getBalance() {
        return currentBalance;
    }

    // Function to get the balance holder ID
    int getBalanceHolderID() {
        return balanceHolderID;
    }

    // Function to show balance details
    void showBalanceDetails() {
        cout << "Account Holder ID: " << balanceHolderID << endl;
        cout << "Current Balance: $" << currentBalance << endl;
    }
};

int main() {
    // Create an AccountBalance object
    AccountBalance account(1200.50, 1001);

    // Show the account details
    account.showBalanceDetails();

    return 0;
}

