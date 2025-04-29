/*
Code Artifact: UserInterface
Description: Creates and manages User Interface displays for customers and admins
Programmer: Đạt Trịnh
Date Programmed: April 25, 2025
Modified by: Justin Vasquez
Date Modified: April 28, 2025
Files Accessed: None
Files Changed: None
*/

#ifndef  USER_INTERFACE
#define USER_INTERFACE
#include <iostream>
#include <string>
#include "TransactionProcessing.h"
#include "ViewTransactionHistory.h"
#include "Customer.h"
#include "Admin.h"
using namespace std;

class UserInterface {
public:
    // Main User Interface
	int mainInterface() {
		int choice = 0;				//Holds user choice
		string ID = "";				//Holds user inputted ID
		bool validInput = false;	//Validates user input

		while (!validInput) {
			//Display sign in screen
			cout << "Welcome to Team 9 Bank! Please choose an option: " << endl
				 << "(1) Log-in to existing account" << endl
				 << "(2) Sign up and create an account" << endl
			  	 << "(3) Exit Program" << endl;
			cin >> choice;

			//If user wishes to login to an existing account
			if (choice == 1) {
				while (!validInput) {
					cout << "Please provide your account ID (####): ";
					cin >> ID;

					//If user inputs an admin ID check if in database and ask user to login
					if (ID[0] >= 'A' && ID[0] <= 'Z') {
						Admin administrativeUser(ID);

						if (!administrativeUser.checkDatabase()) {
							return 0;
						}

						if (!loginAdmin(administrativeUser)) {
							return 0;
						}

						//Go to Administrative UI
						showAdminUI(administrativeUser, validInput, choice, ID);
					}

					//If user inputs a customer ID check if in database and ask user to login
					else if (ID[0] >= 0 && ID[0] <= 9) {
						Customer customerUser(ID);

						if (!customerUser.checkDatabase()) {
							return 0;
						}

						if (!loginCustomer(customerUser)) {
							return 0;
						}

						//Go to Customer UI
						showCustomerUI(customerUser, validInput, choice);
					}

					//Ask for ID again if input is invalid
					else {
						cout << "Please provide a valid ID." << endl;
					}
				}
			}

			//If user wishes to sign up
			else if (choice == 2) {
				Customer customerUser;	//Create customer account profile
				showCustomerUI(customerUser, validInput, choice, ID);
			}

			//If user wants to exit program
			else if (choice == 3) {
				return 0;
			}

			//If user inputs invalid option
			else {
				cout << "Please choose a valid option." << endl;
			}
		}
	};

	//Login for Admin ID
	bool loginAdmin(Admin& administrativeUser, string username = "", string password = "", int failedAttempts = 0) {
		cout << "Please provide your username and password: " << endl;
		cout << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;

		//Cross-reference appropriate admin file for username and password, allowing 5 attempts
		while (failedAttempts < 5) {
			if (username == administrativeUser.getUsername() && password == administrativeUser.getPassword()) {
				cout << "Login successful." << endl;
				return true;
			}
			else {
				cout << "Login Attempt Failed." << endl;
				failedAttempts++;
			}
		}
		cout << "Could not verify user." << endl;
		return false;

	};

	//Login for Customer ID
	bool loginCustomer(Customer& customerUser, string username = "", string password = "", int failedAttempts = 0) {
		cout << "Please provide your username and password: " << endl;
		cout << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;

		//Cross-reference appropriate customer file for username and password, allowing 5 attempts
		while (failedAttempts < 5) {
			if (username == customerUser.getUsername() && password == customerUser.getPassword()) {
				cout << "Login succesful." << endl;
				return true;
			}
			else {
				cout << "Login attempt failed." << endl;
				failedAttempts++;
			}
		}
		cout << "Could not verify user." << endl;
		return false;

	};

    // Function to show Customer UI
	int showCustomerUI(Customer& customerUser, bool& validInput, int& choice, string& ID) {
		validInput = false;

		//Display Customer options screen
		while (!validInput) {
			cout << "What would you like to do? Please choose an option: " << endl
				 << "(1) Make a deposit" << endl
				 << "(2) Make a withdrawal" << endl
				 << "(3) View Account Balance" << endl
			 	 << "(4) View Transaction History" << endl
				 << "(5) Change account details" << endl
				 << "(6) Exit Program" << endl;
			cin >> choice;

			if (choice == 1) {
				TransactionProcessing customerAccount(customerUser.getCustomerID());	//Attempt to access customer records
				float amount = 0.0;	//Amount to be deposited

				cout << "How much would you like to deposit?" << endl
					 << "$ ";
				cin >> amount;
				customerAccount.deposit(amount);
			}

			else if (choice == 2) {
				TransactionProcessing customerAccount(customerUser.getCustomerID());	//Attempt to access customer records
				float amount = 0.0;	//Amount to be withdrawn

				cout << "How much would you like to withdraw?" << endl
					<< "$ ";
				cin >> amount;
				customerAccount.withdraw(amount);
			}

			else if (choice == 3) {
				ViewTransactionHistory customerAccount(customerUser.getCustomerID());
				customerAccount.getCurrentBalance();
			}

			else if (choice == 4) {
				ViewTransactionHistory customerAccount(customerUser.getCustomerID());
				customerAccount.display();
			}

			else if (choice == 5) {
				string setter = "";	//For changing account details

				cout << "What would you like to change?" << endl
					 << "(1) First Name" << endl
					 << "(2) Last Name" << endl
					 << "(3) Username" << endl
					 << "(4) Password" << endl
					 << "(5) Mobile Number" << endl
					 << "(6) Address" << endl
					 << "(7) Email" << endl
					 << "(8) Date of Birth" << endl
					 << "(9) Quit" << endl;
				cin >> choice;

				if (choice == 1) {
					cout << "Please enter new first name: ";
					cin >> setter;
					customerUser.setFirstName(setter);
				}
				else if (choice == 2) {
					cout << "Please enter new last name: ";
					cin >> setter;
					customerUser.setLastName(setter);
				}
				else if (choice == 3) {
					cout << "Please enter new username: ";
					cin >> setter;
					customerUser.setUsername(setter);
				}
				else if (choice == 4) {
					cout << "Please enter new password: ";
					cin >> setter;
					customerUser.setPassword(setter);
				}
				else if (choice == 5) {
					cout << "Please enter new mobile number: ";
					cin >> setter;
					customerUser.setMobileNumber(setter);
				}
				else if (choice == 6) {
					cout << "Please enter new address: ";
					cin >> setter;
					customerUser.setAddress(setter);
				}
				else if (choice == 7) {
					cout << "Please enter new email: ";
					cin >> setter;
					customerUser.setEmail(setter);
				}
				else if (choice == 8) {
					cout << "Please enter correct date of birth: ";
					cin >> setter;
					customerUser.setDateOfBirth(setter);
				}
				else if (choice == 9) {
					continue;
				}
				else {
					cout << "Please choose a valid option." << endl;
				}
			}

			else if (choice == 6) {
				return 0;
			}

			else {
				cout << "Please choose a valid option." << endl;
			}

		}
	};

    // Function to show Admin UI
	int showAdminUI(Admin& adminUser, bool& validInput, int& choice, string& ID) {
		validInput = false;

		//Display Admin options screen
		while (!validInput) {
			cout << "What would you like to do? Please choose an option: " << endl
				 << "(1) Reset Customer Password" << endl
				 << "(2) Monitor Customer Transaction History" << endl
				 << "(3) Freeze User Account" << endl
				 << "(4) Deactivate Customer Account" << endl
				 << "(5) Change Account Details" << endl
				 << "(6) Exit Program" << endl;
			cin >> choice;

			if (choice == 1) {
				string newPassword = "";	//Password for reseting user account

				cout << "Please provide customerID for the user whose password you wish to reset." << endl;
				cin >> ID;

				cout << "Please input a new password for the user's account: ";
				cin >> newPassword;
				adminUser.resetCustomerPassword(newPassword, ID);
			}

			else if (choice == 2) {
				cout << "Please provide customerID for the user whose account you wish to monitor." << endl;
				cin >> ID;
				ViewTransactionHistory customer(ID);
				customer.display();

			}

			else if (choice == 3) {
				cout << "Please provide customerID for the user whose account is to be frozen." << endl;
				cin >> ID;
				adminUser.freezeCustomerAccount(ID);
			}

			else if (choice == 4) {
				cout << "Please provide customerID for the user to be deactivated." << endl;
				cin >> ID;
				adminUser.deactivateCustomerAccount(ID);
			}

			else if (choice == 5) {
				string setter = "";	//For changing account details

				cout << "What would you like to change?" << endl
					 << "(1) First Name" << endl
					 << "(2) Last Name" << endl
					 << "(3) Username" << endl
					 << "(4) Password" << endl
					 << "(5) Quit" << endl;
				cin >> choice;

				if (choice == 1) {
					cout << "Please enter new first name: ";
					cin >> setter;
					adminUser.setFirstName(setter);
				}
				else if (choice == 2) {
					cout << "Please enter new last name: ";
					cin >> setter;
					adminUser.setLastName(setter);
				}
				else if (choice == 3) {
					cout << "Please enter new username: ";
					cin >> setter;
					adminUser.setUsername(setter);
				}
				else if (choice == 4) {
					cout << "Please enter new password: ";
					cin >> setter;
					adminUser.setPassword(setter);
				}
				else if (choice == 5) {
					continue;
				}
				else {
					cout << "Please choose a valid option." << endl;
				}
			}

			else if (choice == 6) {
				return 0;
			}

			else {
				cout << "Please choose a valid option." << endl;
			}
		}
	};
};

#endif