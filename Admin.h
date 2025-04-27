/*
Code Artifact: Admin
Description: Creates and manages Admin entities
Programmer: Justin Vasquez
Date Programmed: April 25, 2025
Variables: employeeID: stores employee's ID, firstName: stores employee's first name, 
		   lastName: stores employee's last name, password: stores employee's password,
		   username: stores employee's username
Files Accessed: Cust_(customerID)
Files Changed: Cust_(customerID)
*/

#ifndef ADMIN
#define ADMIN
#include <iostream>
#include <fstream>
#include <string>
#include "Customer.h"
using namespace std;

class Admin {
private:
	string firstName = "N/A";	// stores employee's first name
	string lastName = "N/A";	// stores employee's last name
	string employeeID = "N/A";	// stores employee's ID
	string username = "N/A";	// stores employee's username
	string password = "N/A";	// stores employee's password

public:
	string getFirstName() {
		return firstName;
	}

	void setFirstName(string fName) {
		firstName = fName;
	}

	string getLastName() {
		return lastName;
	}

	void setLastName(string lName) {
		lastName = lName;
	}

	string getEmployeeID() {
		return employeeID;
	}

	void setEmployeeID(string identification) {
		employeeID = identification;
	}

	string getUsername() {
		return username;
	}

	void setUsername(string username) {
		username = username;
	}

	string getPassword() {
		return password;
	}

	void setPassword(string password) {
		password = password;
	}

	//Displays all info on Administrator
	void display() {
		cout << "\tADMIN" << endl << "\t~~~~~" << endl
			 << "Name: " << firstName << ' ' << lastName << endl
			 << "Employee ID: " << employeeID << endl
			 << "Username: " << username << endl
			 << "Password: " << password << endl;
	}

	//Freezes all transactions from occurring through customer's account
	void freezeCustomerAccount(string customerID) {
		fstream customerAccount;
		customerAccount.open("Cust_" + customerID, fstream::out, fstream::app);

		if (customerAccount.is_open()) {
			customerAccount.write("freeze user account.", 20);
		}
	}

	//Erases customer's information from database
	void deactivateCustomerAccount(string customerID) {
		fstream customerAccount;
		customerAccount.open("Cust_" + customerID);

		if (customerAccount.is_open()) {
			customerAccount.trunc;
			customerAccount.close();
		}
		else {
			cout << "Customer account does not exist in database." << endl;
		}
	}

	//Changes customer's password
	void resetCustomerPassword(string newPassword, string customerID) {
		fstream customerAccount;
		string line;
		customerAccount.open("Cust_" + customerID);

		if (customerAccount.is_open()) {
			while (getline(customerAccount, line)) {
				if (line == "Password:") {
					NULL; //in progress
				}
			}
		}
	}

};


#endif