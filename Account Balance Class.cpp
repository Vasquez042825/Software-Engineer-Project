/*
Code Artifact: AccountBalance
Description: Creates and manages Account Balance entities
Programmer: Đạt Trịnh
Date Programmed: April 26, 2025
Variables: currentBalance: stores the current balance of the account,
           balanceHolderID: stores the ID of the account holder
Files Accessed: None
Files Changed: None
*/

#include <iostream>
using namespace std;

// AccountBalance Class
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

    // Getter for current balance
    float getBalance() {
        return currentBalance;
    }

    // Getter for balance holder ID
    int getBalanceHolderID() {
        return balanceHolderID;
    }

    // Show balance details
    void showBalanceDetails() {
        cout << "Account Holder ID: " << balanceHolderID
            << ", Balance: $" << currentBalance << endl;
    }
};

// Example usage
int main() {
    // Create an AccountBalance object
    AccountBalance account(1500.75, 12345);

    // Display balance details
    account.showBalanceDetails();

    return 0;
}
