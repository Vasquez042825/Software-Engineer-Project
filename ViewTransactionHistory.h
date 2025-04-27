/*
Code Artifact: View Transaction History
Description: Displays various aspects of a customer's transaction history
Programmer: Justin Vasquez
Date Programmed: April 25, 2025
Variables: customerInfo: file with customer transaction records, transactionRecord: stores read lines from file
Files Accessed: Cust_(customerID)
Files Changed: None
*/

#ifndef VIEW_TRANSACTION_HISTORY
#define VIEW_TRANSACTION_HISTORY
#include <iostream>
#include <fstream>
using namespace std;

class ViewTransactionHistory {
private:
	fstream customerInfo;			//For opening customer transaction record file
	string transactionRecord = "";	//For holding strings from customer file

public:
	//Constructor attempts to open customer information in database
	ViewTransactionHistory(string customerID) {
		customerInfo.open("Cust_" + customerID);

		if (!customerInfo.is_open()) {
			cout << "Customer's file could not be accessed." << endl;
		}
	}

	//Destructor closes customer file if open had been successful
	~ViewTransactionHistory() {
		if (customerInfo.is_open()) {
			customerInfo.close();
		}
	}

	//Locate all instances of withdrawals in customer file and display
	void getWithdrawals() {
		if (customerInfo.is_open()) {
			while (customerInfo >> transactionRecord)) {
			if (transactionRecord == "Withdrawal") {
				cout << "Withdrawals:" << endl;
				customerInfo >> transactionRecord;
				cout << transactionRecord;
				customerInfo >> transactionRecord;
				cout << transactionRecord;
			}
			}
		}
		else {
			cout << "Customer information could not be found." << endl;
		}
	}

	//Locate all instances of deposits in customer file and display
	void getDeposits() {
		if (customerInfo.is_open()) {
			while (customerInfo >> transactionRecord)) {
				if (transactionRecord == "Deposit") {
					cout << "Deposits:" << endl;
					customerInfo >> transactionRecord;
					cout << transactionRecord;
					customerInfo >> transactionRecord;
					cout << transactionRecord;
				}
			}
		}
		else {
			cout << "Customer information could not be found." << endl;
		}
	}

	//Display current balance in customer file
	void getCurrentBalance() {
		if (customerInfo.is_open()) {
			while (getline(customerInfo, transactionRecord)) {
				if (transactionRecord[0] == 'C') {
					cout << transactionRecord;
				}
			}
		}
		else {
			cout << "Customer information could not be found." << endl;
		}
	}

	//Display customer's entire transaction record with the bank
	void display() {
		while (getline(customerInfo, transactionRecord)) {
			cout << transactionRecord;
		}
	}
}

#endif