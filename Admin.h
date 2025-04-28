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

	void setUsername(string adminUsername) {
		username = adminUsername;
	}

	string getPassword() {
		return password;
	}

	void setPassword(string adminPassword) {
		password = adminPassword;
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
		ofstream customerAccount;	//Access customer account file
		
		customerAccount.open("Cust_" + customerID + ".txt", ios_base::app);

		if (customerAccount.is_open()) {
			customerAccount.write("\nFREEZE USER ACCOUNT.", 20);
			cout << "Customer account has been frozen." << endl;
		}
	}

	//Erases customer's information from database
	void deactivateCustomerAccount(string customerID) {
		//If customer account file cannot be removed it is not in database, otherwise delete the file
		if ((remove(("Cust_info_" + customerID + ".txt").c_str())) != 0){
			cout << "Customer account does not exist in database." << endl;
		}
		else {
			cout << "Customer account has been deactivated." << endl;
		}
	}

	//Changes customer's password
	void resetCustomerPassword(string newPassword, string customerID) {
		fstream customerAccount;	//Access customer's account file
		fstream tempFile;		//Create new customer account file with updated contents
		string line;			//Store lines from file

		customerAccount.open("Cust_info_" + customerID + ".txt");
		tempFile.open("TEMP.txt", ios_base::out);

		//Verify customer account file is accessible and update password line if true
		if (customerAccount.is_open()) {
			while (getline(customerAccount, line)) {
				if (line[0] == 'P') {
					tempFile << "Password: " << newPassword << '\n';
					tempFile.flush();
					continue;
				}

				tempFile << line << '\n';
				tempFile.flush();

			}

			customerAccount.close();
			tempFile.close();

			//Close and reopen temp file and customer account file to truncate account file for updating
			tempFile.open("TEMP.txt", ios_base::in);
			customerAccount.open("Cust_info_" + customerID + ".txt", ios_base::trunc | ios::out);
			
			while (getline(tempFile, line)) {
				customerAccount << line << '\n';
			}
			
			customerAccount.close();
			tempFile.close();
			remove("TEMP.txt");
			cout << "Customer password has been updated." << endl;
		}
		else {
			cout << "Customer account does not exist in database." << endl;
		}

	}

};


#endif
