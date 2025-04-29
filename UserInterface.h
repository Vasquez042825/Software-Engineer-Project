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
			cout << "\nWelcome to Team 9 Bank! Please choose an option: " << endl
				 << "(1) Log-in to existing account" << endl
				 << "(2) Sign up and create an account" << endl
			  	 << "(3) Exit Program" << endl;
			cin >> choice;

			//If user wishes to login to an existing account
			if (choice == 1) {
				cout << "Please provide your account ID (####): ";
				cin >> ID;

				//If user inputs an admin ID check if in database and ask user to login
				if (ID[0] >= 'A' && ID[0] <= 'Z' && ID.length() == 4) {
					Admin administrativeUser(ID);

					if (!administrativeUser.checkDatabase()) {
						continue;
					}

					if (!loginAdmin(administrativeUser)) {
						return 0;
					}

					//Go to Administrative UI
					showAdminUI(administrativeUser, validInput, choice, ID);
				}

				//If user inputs a customer ID check if in database and ask user to login
				else if (ID[0] >= 48 && ID[0] <= 57 && ID.length() == 4) {
					Customer customerUser(ID);

					if (!customerUser.checkDatabase()) {
						continue;
					}

					if (!loginCustomer(customerUser)) {
						return 0;
					}

					//Go to Customer UI
					showCustomerUI(customerUser, validInput, choice, ID);
				}

				//Ask for ID again if input is invalid
				else {
					cout << "Please provide a valid ID." << endl;
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
	bool loginAdmin(Admin& administrativeUser, string username = "", string password = "", int failedAttempts = 5) {
		//Cross-reference appropriate admin file for username and password, allowing 5 attempts
		while (failedAttempts != 0) {
			cout << "\nPlease provide your username and password: " << endl;
			cout << "Username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;

			if (username == administrativeUser.getUsername() && password == administrativeUser.getPassword()) {
				cout << "\nLogin successful." << endl;
				return true;
			}
			else {
				failedAttempts--;
				cout << "\nLogin Attempt Failed." << endl
					 << failedAttempts << " attempts remaining" << endl << endl;
			}
		}
		cout << "\nCould not verify user." << endl;
		return false;

	};

	//Login for Customer ID
	bool loginCustomer(Customer& customerUser, string username = "", string password = "", int failedAttempts = 5) {
		//Cross-reference appropriate customer file for username and password, allowing 5 attempts
		while (failedAttempts != 0) {
			cout << "\nPlease provide your username and password: " << endl;
			cout << "Username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;

			if (username == customerUser.getUsername() && password == customerUser.getPassword()) {
				cout << "\nLogin succesful." << endl;
				return true;
			}
			else {
				failedAttempts--;
				cout << "\nLogin attempt failed." << endl
					 << failedAttempts << " attempt(s) remaining" << endl << endl;
			}
		}
		cout << "\nCould not verify user." << endl;
		return false;

	};

    // Function to show Customer UI
	int showCustomerUI(Customer& customerUser, bool& validInput, int& choice, string& ID) {
		//Display Customer options screen
		while (!validInput) {
			cout << "\nWhat would you like to do? Please choose an option: " << endl
				 << "(1) Make a deposit" << endl
				 << "(2) Make a withdrawal" << endl
				 << "(3) View Account Balance" << endl
			 	 << "(4) View Transaction History" << endl
				 << "(5) View account details" << endl
				 << "(6) Change account details" << endl
				 << "(7) Exit Program" << endl;
			cin >> choice;

			if (choice == 1) {
				TransactionProcessing customerAccount(customerUser.getCustomerID());	//Attempt to access customer records
				float amount = 0.0;	//Amount to be deposited

				cout << "How much would you like to deposit?" << endl
					 << "$ ";
				cin >> amount;
				customerAccount.deposit(amount, ID);
			}

			else if (choice == 2) {
				TransactionProcessing customerAccount(customerUser.getCustomerID());	//Attempt to access customer records
				float amount = 0.0;	//Amount to be withdrawn

				cout << "How much would you like to withdraw?" << endl
					<< "$ ";
				cin >> amount;
				customerAccount.withdraw(amount, ID);
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
				customerUser.display();
			}

			else if (choice == 6) {
				string setter = "";	//For changing account details

				cout << "\nWhat would you like to change?" << endl
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
					getline(cin >> ws, setter);
					customerUser.setMobileNumber(setter);
				}
				else if (choice == 6) {
					cout << "Please enter new address: ";
					getline(cin >> ws, setter);
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

			else if (choice == 7) {
				return 0;
			}

			else {
				cout << "Please choose a valid option." << endl;
			}a

		}
		validInput = true;
	};

    // Function to show Admin UI
	int showAdminUI(Admin& adminUser, bool& validInput, int& choice, string& ID) {
		//Display Admin options screen
		while (!validInput) {
			cout << "\nWhat would you like to do? Please choose an option: " << endl
				 << "(1) Reset Customer Password" << endl
				 << "(2) Monitor Customer Transaction History" << endl
				 << "(3) Freeze User Account" << endl
				 << "(4) Deactivate Customer Account" << endl
			 	 << "(5) View account details" << endl
				 << "(6) Change Account Details" << endl
				 << "(7) Exit Program" << endl;
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
				adminUser.display();
			}

			else if (choice == 6) {
				string setter = "";	//For changing account details

				cout << "\nWhat would you like to change?" << endl
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

			else if (choice == 7) {
				return 0;
			}

			else {
				cout << "Please choose a valid option." << endl;
			}
		}
		validInput = true;
	};
};

#endif
