#ifndef    TRANSACTION_PROCESSING
#define    TRANSACTION_PROCESSING
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class TransactionProcessing {
private:
    fstream customerInfo;           // Accesses customer banking data
    string transactionRecord = "";	// For holding strings from customer file
    float balance = 0.0f;           // Holds the customer's account balance

public:
    // Default constructor opens customer account balance file
    TransactionProcessing(string customerID) {
        customerInfo.open("Cust_" + customerID + ".txt");

        if (!customerInfo.is_open()) {
            cout << "Customer account file not in database. Creating new file..." << endl;

            customerInfo.close();
            customerInfo.open("Cust_" + customerID + ".txt", ios_base::out);
            customerInfo << "-----------------------------\n" << "Current Balance : $\t" << "0.00";

            customerInfo.close();
            customerInfo.open("Cust_" + customerID + ".txt", ios_base::in);
        }
        else {
            while (customerInfo >> transactionRecord) {
                if (transactionRecord == "Balance:$") {
                    customerInfo >> transactionRecord;
                    balance = stof(transactionRecord);
                }
            }
            customerInfo.clear();
            customerInfo.seekg(0);
        }
    }

    //Destructor closes customer file if open had been successful
    ~TransactionProcessing() {
        if (customerInfo.is_open()) {
            customerInfo.close();
        }
    }

    // Process a deposit
    void deposit(float amount, string ID) {
        bool frozen = false;

        if (customerInfo.is_open()) {
            while (customerInfo >> transactionRecord) {
                if (transactionRecord == "FREEZE") {
                    frozen = true;
                }
            }
            customerInfo.clear();
            customerInfo.seekg(0);
        }

        if (amount > 0 && !frozen) {
            fstream tempFile;			//Create new customer account file with updated contents
            string line;				//Store lines from file

            balance += amount;
            cout << fixed << setprecision(2);
            cout << "Deposit of $" << amount << " successful." << endl;
            cout << "New Balance: $" << balance << endl;

            tempFile.open("TEMP.txt", ios_base::out);

            if (customerInfo.is_open()) {
                while (getline(customerInfo, line)) {
                    tempFile << line << '\n';
                    tempFile.flush();

                }

                customerInfo.close();
                tempFile.close();

                //Close and reopen temp file and customer account file to truncate account file for updating
                tempFile.open("TEMP.txt", ios_base::in);
                customerInfo.open("Cust_" + ID + ".txt", ios_base::trunc | ios::out);

                customerInfo << fixed << setprecision(2) << "Deposit\t\t" << '$' << amount << "\t\t" << '$' << balance << '\n';

                while (getline(tempFile, line)) {
                    if (line[0] == 'C') {
                        customerInfo << "Current Balance:$\t" << balance;
                        break;
                    }
                    customerInfo << line << '\n';
                }

                customerInfo.close();
                tempFile.close();
                remove("TEMP.txt");
                customerInfo.open("Cust_" + ID + ".txt", ios_base::in);
                cout << "Deposit recieved." << endl;
            }
            else {
                cout << "Customer account does not exist in database." << endl;
            }

        } else {
            cout << "Invalid deposit amount or account frozen." << endl;
        }
    }

    // Process a withdrawal
    void withdraw(float amount, string ID) {
        bool frozen = false;

        if (customerInfo.is_open()) {
            while (customerInfo >> transactionRecord) {
                if (transactionRecord == "FREEZE") {
                    frozen = true;
                }
            }
            customerInfo.clear();
            customerInfo.seekg(0);
        }

        if (amount > 0 && balance >= amount && !frozen) {
            fstream tempFile;
            string line;

            balance -= amount;
            cout << fixed << setprecision(2);
            cout << "Withdrawal of $" << amount << " successful." << endl;
            cout << "New Balance: $" << balance << endl;
            tempFile.open("TEMP.txt", ios_base::out);

            if (customerInfo.is_open()) {
                while (getline(customerInfo, line)) {
                    tempFile << line << '\n';
                    tempFile.flush();

                }

                customerInfo.close();
                tempFile.close();

                //Close and reopen temp file and customer account file to truncate account file for updating
                tempFile.open("TEMP.txt", ios_base::in);
                customerInfo.open("Cust_" + ID + ".txt", ios_base::trunc | ios::out);

                customerInfo << fixed << setprecision(2) << "Withdrawal\t" << '$' << amount << "\t\t" << '$' << balance << '\n';

                while (getline(tempFile, line)) {
                    if (line[0] == 'C') {
                        customerInfo << "Current Balance:$\t" << balance;
                        break;
                    }
                    customerInfo << line << '\n';
                }

                customerInfo.close();
                tempFile.close();
                remove("TEMP.txt");
                customerInfo.open("Cust_" + ID + ".txt", ios_base::in);
                cout << "Amount successfully withdrawn." << endl;
            }

        } else {
            cout << "Invalid withdrawal amount or insufficient funds or account frozen." << endl;
        }
    }

    // Validate a transaction amount against current balance
    bool validateTransaction(float amount) const {
        return balance >= amount;
    }

    // Display current account balance
    void displayBalance() const {
        cout << fixed << setprecision(2) << "Current Balance: $" << balance << endl;
    }

    // Get current balance (for internal use)
    float getBalance() const {
        return balance;
    }
};

#endif
