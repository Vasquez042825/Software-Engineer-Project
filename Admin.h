/*
Code Artifact: Admin
Description: Creates and manages Admin entities
Programmer: Justin Vasquez
Date Programmed: April 25, 2025
Variables: employeeID: stores employee's ID, firstName: stores employee's first name, 
		   lastName: stores employee's last name, password: stores employee's password,
		   username: stores employee's username
Files Accessed: Cust_(customerID).txt, Admin_info_(employeeID).txt
Files Changed: Cust_(customerID).txt, Admin_info_(employeeID).txt
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
	string employeeID = "N/A";	// stores employee's ID as alphanumeric string
	string username = "N/A";	// stores employee's username
	string password = "N/A";	// stores employee's password
	fstream adminAccount;		// accesses employee's account file

public:
	//Log-in constructor
	Admin(string ID) {
		adminAccount.open("Admin_info_" + ID + ".txt", ios_base::in);

		if (adminAccount.is_open()) {
			employeeID = ID;		//Initialize employeeID
			string line = "";		//Searching text from file

			while (adminAccount >> line) {
				//Initialize admin first name from file
				if (line == "First") {
					adminAccount >> line;
					adminAccount >> line;
					firstName = line;
				}
				//Initialize admin last name from file
				else if (line == "Last") {
					adminAccount >> line;
					adminAccount >> line;
					lastName = line;
				}
				//Initialize admin username from file
				else if (line == "Username:") {
					adminAccount >> line;
					username = line;
				}
				//Initialize admin password from file
				else if (line == "Password:") {
					adminAccount >> line;
					password = line;
				}
			}
			adminAccount.clear();
			adminAccount.seekg(0);
		}

		else {
			cout << "admin information could not be found." << endl;
		}
	}

	//Account Creation constructor
	Admin() {
		bool validInput = false;

		while (!validInput) {
			cout << "Please enter an employeeID (####): ";
			cin >> employeeID;

			adminAccount.open("Admin_info_" + employeeID + ".txt", ios_base::in);

			//Check if Admin already exists in database
			if (adminAccount.is_open()) {
				cout << "Admin already exists in database. Please use another ID." << endl << endl;
				adminAccount.close();
			}
			//Else store Admin profile in database
			else if (employeeID[0] >= 'A' && employeeID[0] <= 'Z' && employeeID.length() == 4) {
				cout << "Creating Administrative profile..." << endl;
				adminAccount.close();
				adminAccount.open("Admin_info_" + employeeID + ".txt", ios_base::out);

				//Set Admin's first name and store to file
				cout << "Please set the Admin's" << endl << "First Name: ";
				cin >> firstName;
				adminAccount << "First Name: " << firstName << '\n';

				//Set Admin's last name and store to file
				cout << "\nLast Name: ";
				cin >> lastName;
				adminAccount << "Last Name: " << lastName << '\n';

				//Store Admin's employeeID to file
				adminAccount << "EmployeeID: " << employeeID << '\n';

				//Set Admin's username and store to file
				cout << "\nUsername: ";
				cin >> username;
				adminAccount << "Username: " << username << '\n';

				//Set Admin's password and store to file
				cout << "\nPassword: ";
				cin >> password;
				adminAccount << "Password: " << password << '\n';
				cout << endl;

				adminAccount.clear();
				adminAccount.seekg(0);

				cout << "``````````````````````````````" << endl
					<< "Account created successfully!" << endl
					<< "``````````````````````````````" << endl;
				validInput = true;
			}
			else {
				cout << "Invalid employee ID." << endl << endl;
			}
		}
	}

	~Admin() {
		adminAccount.close();
	}

	//Check if user file exists in database
	bool checkDatabase() {
		if (!adminAccount.is_open()) {
			cout << "Admin is not in database." << endl;
			return false;
		}
		else {
			return true;
		}
	}

	string getFirstName() {
		return firstName;
	}

	void setFirstName(string fName) {
		firstName = fName;

		fstream tempFile;			//Create temp file for replacing contents
		string line;				//Store lines from file

		tempFile.open("TEMP.txt", ios_base::out);

		//Verify admin account file is accessible and update first name line if true
		if (adminAccount.is_open()) {
			while (getline(adminAccount, line)) {
				if (line[0] == 'F') {
					tempFile << "First Name: " << firstName << '\n';
					tempFile.flush();
					continue;
				}

				tempFile << line << '\n';
				tempFile.flush();

			}

			adminAccount.close();
			tempFile.close();

			//Close and reopen temp file and admin account file to truncate account file for updating
			tempFile.open("TEMP.txt", ios_base::in);
			adminAccount.open("Admin_info_" + employeeID + ".txt", ios_base::trunc | ios::out);

			while (getline(tempFile, line)) {
				adminAccount << line << '\n';
			}

			adminAccount.close();
			tempFile.close();
			remove("TEMP.txt");
			cout << "Admin first name has been updated." << endl;
		}
		else {
			cout << "Admin account does not exist in database." << endl;
		}

	}

	string getLastName() {
		return lastName;
	}

	void setLastName(string lName) {
		lastName = lName;

		fstream tempFile;			//Create temp file for replacing contents
		string line;				//Store lines from file

		tempFile.open("TEMP.txt", ios_base::out);

		//Verify admin account file is accessible and update last name line if true
		if (adminAccount.is_open()) {
			while (getline(adminAccount, line)) {
				if (line[0] == 'L') {
					tempFile << "Last Name: " << lastName << '\n';
					tempFile.flush();
					continue;
				}

				tempFile << line << '\n';
				tempFile.flush();

			}

			adminAccount.close();
			tempFile.close();

			//Close and reopen temp file and admin account file to truncate account file for updating
			tempFile.open("TEMP.txt", ios_base::in);
			adminAccount.open("Admin_info_" + employeeID + ".txt", ios_base::trunc | ios::out);

			while (getline(tempFile, line)) {
				adminAccount << line << '\n';
			}

			adminAccount.close();
			tempFile.close();
			remove("TEMP.txt");
			cout << "Admin last name has been updated." << endl;
		}
		else {
			cout << "Admin account does not exist in database." << endl;
		}

	}

	string getEmployeeID() {
		return employeeID;
	}

	string getUsername() {
		return username;
	}

	void setUsername(string adminUsername) {
		username = adminUsername;

		fstream tempFile;			//Create temp file for replacing contents
		string line;				//Store lines from file

		tempFile.open("TEMP.txt", ios_base::out);

		//Verify admin account file is accessible and update username line if true
		if (adminAccount.is_open()) {
			while (getline(adminAccount, line)) {
				if (line[0] == 'U') {
					tempFile << "Username: " << username << '\n';
					tempFile.flush();
					continue;
				}

				tempFile << line << '\n';
				tempFile.flush();

			}

			adminAccount.close();
			tempFile.close();

			//Close and reopen temp file and admin account file to truncate account file for updating
			tempFile.open("TEMP.txt", ios_base::in);
			adminAccount.open("Admin_info_" + employeeID + ".txt", ios_base::trunc | ios::out);

			while (getline(tempFile, line)) {
				adminAccount << line << '\n';
			}

			adminAccount.close();
			tempFile.close();
			remove("TEMP.txt");
			cout << "Admin username has been updated." << endl;
		}
		else {
			cout << "Admin account does not exist in database." << endl;
		}

	}

	string getPassword() {
		return password;
	}

	void setPassword(string adminPassword) {
		password = adminPassword;

		fstream tempFile;			//Create temp file for replacing contents
		string line;				//Store lines from file

		tempFile.open("TEMP.txt", ios_base::out);

		//Verify admin account file is accessible and update password line if true
		if (adminAccount.is_open()) {
			while (getline(adminAccount, line)) {
				if (line[0] == 'P') {
					tempFile << "Password: " << password << '\n';
					tempFile.flush();
					continue;
				}

				tempFile << line << '\n';
				tempFile.flush();

			}

			adminAccount.close();
			tempFile.close();

			//Close and reopen temp file and admin account file to truncate account file for updating
			tempFile.open("TEMP.txt", ios_base::in);
			adminAccount.open("Admin_info_" + employeeID + ".txt", ios_base::trunc | ios::out);

			while (getline(tempFile, line)) {
				adminAccount << line << '\n';
			}

			adminAccount.close();
			tempFile.close();
			remove("TEMP.txt");
			cout << "Admin password has been updated." << endl;
		}
		else {
			cout << "Admin account does not exist in database." << endl;
		}

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
		if ((remove(("Cust_info_" + customerID + ".txt").c_str())) != 0 || (remove(("Cust_" + customerID + ".txt").c_str())) != 0){
			cout << "Customer account does not exist in database." << endl;
		}
		else {
			cout << "Customer account has been deactivated." << endl;
		}
	}

	//Changes customer's password
	void resetCustomerPassword(string newPassword, string customerID) {
		fstream customerAccount;	//Access customer's account file
		fstream tempFile;			//Create new customer account file with updated contents
		string line;				//Store lines from file

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
