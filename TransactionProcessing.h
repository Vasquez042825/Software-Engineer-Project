#include <iostream>
using namespace std;

class TransactionProcessing {
private:
    float balance = 0.0f; // Holds the customer's account balance

public:
    // Default constructor initializes balance
    TransactionProcessing() {
        balance = 0.0f;
    }

    // Constructor initializes balance with provided starting amount
    TransactionProcessing(float startingBalance) {
        balance = startingBalance;
    }

    // Destructor (no file handling needed)
    ~TransactionProcessing() {}

    // Process a deposit
    void deposit(float amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit of $" << amount << " successful." << endl;
            cout << "New Balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    // Process a withdrawal
    void withdraw(float amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << "Withdrawal of $" << amount << " successful." << endl;
            cout << "New Balance: $" << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient funds." << endl;
        }
    }

    // Validate a transaction amount against current balance
    bool validateTransaction(float amount) const {
        return balance >= amount;
    }

    // Display current account balance
    void displayBalance() const {
        cout << "Current Balance: $" << balance << endl;
    }

    // Get current balance (for internal use)
    float getBalance() const {
        return balance;
    }

    // Set balance manually (use carefully)
    void setBalance(float newBalance) {
        balance = newBalance;
    }
};
