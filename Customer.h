/*
 Code Artifact : Customer
 Description: Defines Customer entity including personal information, 
              and login credentials.
 Programmer: Liza Tamang
 Date Programmed: April 27, 2025
 Variables: 
  - customerID: stores customer's unique ID
  - firstName: stores customer's first name
  - lastName: stores customer's last name
  - mobileNumber: stores customer's mobile number
  - address: stores customer's address
  - email: stores customer's email address
  - dateOfBirth: stores customer's date of birth
  - username: stores customer's login username
  - password: stores customer's login password
 Files Accessed: Cust_info_(customerID).txt
 Files Changed: Cust_info_(customerID).txt
*/

#pragma once

#include <iostream>
#include <string>
#include <fstream> 
#include "TransactionProcessing.h"
using namespace std;

class Customer {
private:
    string customerID = "N/A";      // Unique customer ID
    string firstName = "N/A";       // Customer's first name
    string lastName = "N/A";        // Customer's last name
    string mobileNumber = "N/A";    // Customer's contact number
    string address = "N/A";         // Customer's address
    string email = "N/A";           // Customer's email address
    string dateOfBirth = "N/A";     // Customer's date of birth
    string username = "N/A";        // Customer's username
    string password = "N/A";        // Customer's password
    fstream customerAccount;        // Access customer's account file

public:
    //Log-in constructor
    Customer(string ID) {
        customerAccount.open("Cust_info_" + ID + ".txt", ios_base::in);

        if (customerAccount.is_open()) {
            customerID = ID;    //Initialize customerID
            string line = "";   //Searching text from file

            while (customerAccount >> line) {
                //Initialize customer first name from file
                if (line == "First") {
                    customerAccount >> line;
                    customerAccount >> line;
                    firstName = line;
                }
                //Initialize customer last name from file
                else if (line == "Last") {
                    customerAccount >> line;
                    customerAccount >> line;
                    lastName = line;
                }
                //Initialize customer mobile number from file
                else if (line == "Mobile") {
                    getline(customerAccount, mobileNumber);
                }
                //Initialize customer address from file
                else if (line == "Address:") {
                    getline(customerAccount, address);
                }
                //Initialize customer email from file
                else if (line == "Email:") {
                    customerAccount >> line;
                    email = line;
                }
                //Initialize customer date of birth from file
                else if (line == "DOB:") {
                    customerAccount >> line;
                    dateOfBirth = line;
                }
                //Initialize customer username from file
                else if (line == "Username:") {
                    customerAccount >> line;
                    username = line;
                }
                //Initialize customer password from file
                else if (line == "Password:") {
                    customerAccount >> line;
                    password = line;
                }
            }
            customerAccount.clear();
            customerAccount.seekg(0);
        }

        else {
            cout << "Customer information could not be found." << endl;
        }
    }

    //Account Creation constructor
    Customer() {
        bool validInput = false;

        while (!validInput) {
            cout << "Please enter a Customer ID (####): ";
            cin >> customerID;

            customerAccount.open("Cust_info_" + customerID + ".txt", ios_base::in);

            //Check if Customer already exists in database
            if (customerAccount.is_open()) {
                cout << "Customer already exists in database. Please use another ID." << endl << endl;
                customerAccount.close();
            }
            //Else store Customer profile in database
            else if (customerID[0] >= 48 && customerID[0] <= 57 && customerID.length() == 4) {
                cout << "Creating Customer profile..." << endl;
                customerAccount.close();
                customerAccount.open("Cust_info_" + customerID + ".txt", ios_base::app);

                //Set Customer's first name and store to file
                cout << "Please set the Customer's" << endl << "First Name: ";
                cin >> firstName;
                customerAccount << "First Name: " << firstName << '\n';

                //Set Customer's last name and store to file
                cout << "\nLast Name: ";
                cin >> lastName;
                customerAccount << "Last Name: " << lastName << '\n';

                //Store Customer's customerID to file
                customerAccount << "CustomerID: " << customerID << '\n';

                //Set Customer's mobile number and store to file
                cout << "\nMobile Number: ";
                getline(cin >> ws, mobileNumber);
                customerAccount << "Mobile Number: " << mobileNumber << '\n';

                //Set Customer's address and store to file  
                cout << "\nAddress: ";
                getline(cin >> ws, address);
                customerAccount << "Address: " << address << '\n';

                //Set Customer's email and store to file
                cout << "\nEmail: ";
                cin >> email;
                customerAccount << "Email: " << email << '\n';

                //Set Customer's birth date and store to file
                cout << "\nDOB (mm/dd/yy): ";
                cin >> dateOfBirth;
                customerAccount << "DOB: " << dateOfBirth << '\n';

                //Set Customer's username and store to file
                cout << "\nUsername: ";
                cin >> username;
                customerAccount << "Username: " << username << '\n';

                //Set Customer's password and store to file
                cout << "\nPassword: ";
                cin >> password;
                customerAccount << "Password: " << password << '\n';
                cout << endl;

                customerAccount.clear();
                customerAccount.seekg(0);
                TransactionProcessing customerInfo(customerID);
                cout << "``````````````````````````````" << endl 
                     << "Account created successfully!" << endl
                     << "``````````````````````````````" << endl;
                validInput = true;
            }
            else {
                cout << "Invalid customer ID." << endl << endl;
            }
        }
    }

    ~Customer() {
        customerAccount.close();
    }

    //Check if user file exists in database
    bool checkDatabase() {
        if (!customerAccount.is_open()) {
            cout << "Customer is not in database." << endl;
            return false;
        }
        else {
            return true;
        }
    }

    // Getter for customerID
    string getCustomerID() const {
        return customerID;
    }

    // Getter and Setter for firstName
    string getFirstName() const {
        return firstName;
    }
    void setFirstName(const string& name) {
        firstName = name;

        fstream tempFile;			//Create new customer account file with updated contents
        string line;				//Store lines from file

        tempFile.open("TEMP.txt", ios_base::out);

        //Verify customer account file is accessible and update first name line if true
        if (customerAccount.is_open()) {
            while (getline(customerAccount, line)) {
                if (line[0] == 'F') {
                    tempFile << "First Name: " << firstName << '\n';
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
            customerAccount.open("Cust_info_" + customerID + ".txt", ios_base::in);
            cout << "Customer first name has been updated." << endl;
        }
        else {
            cout << "Customer account does not exist in database." << endl;
        }
    }

    // Getter and Setter for lastName
    string getLastName() const {
        return lastName;
    }
    void setLastName(const string& name) {
        lastName = name;

        fstream tempFile;			//Create new customer account file with updated contents
        string line;				//Store lines from file

        tempFile.open("TEMP.txt", ios_base::out);

        //Verify customer account file is accessible and update last name line if true
        if (customerAccount.is_open()) {
            while (getline(customerAccount, line)) {
                if (line[0] == 'L') {
                    tempFile << "Last Name: " << lastName << '\n';
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
            customerAccount.open("Cust_info_" + customerID + ".txt", ios_base::in);
            cout << "Customer last name has been updated." << endl;
        }
        else {
            cout << "Customer account does not exist in database." << endl;
        }
    }

    // Getter and Setter for mobileNumber
    string getMobileNumber() const {
        return mobileNumber;
    }
    void setMobileNumber(const string& number) {
        mobileNumber = number;

        fstream tempFile;			//Create new customer account file with updated contents
        string line;				//Store lines from file

        tempFile.open("TEMP.txt", ios_base::out);

        //Verify customer account file is accessible and update mobile number line if true
        if (customerAccount.is_open()) {
            while (getline(customerAccount, line)) {
                if (line[0] == 'M') {
                    tempFile << "Mobile Number: " << mobileNumber << '\n';
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
            customerAccount.open("Cust_info_" + customerID + ".txt", ios_base::in);
            cout << "Customer mobile number has been updated." << endl;
        }
        else {
            cout << "Customer account does not exist in database." << endl;
        }
    }

    // Getter and Setter for address
    string getAddress() const {
        return address;
    }
    void setAddress(const string& addr) {
        address = addr;

        fstream tempFile;			//Create new customer account file with updated contents
        string line;				//Store lines from file

        tempFile.open("TEMP.txt", ios_base::out);

        //Verify customer account file is accessible and update address line if true
        if (customerAccount.is_open()) {
            while (getline(customerAccount, line)) {
                if (line[0] == 'A') {
                    tempFile << "Address: " << address << '\n';
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
            customerAccount.open("Cust_info_" + customerID + ".txt", ios_base::in);
            cout << "Customer address has been updated." << endl;
        }
        else {
            cout << "Customer account does not exist in database." << endl;
        }
    }

    // Getter and Setter for email
    string getEmail() const {
        return email;
    }
    void setEmail(const string& mail) {
        email = mail;

        fstream tempFile;			//Create new customer account file with updated contents
        string line;				//Store lines from file

        tempFile.open("TEMP.txt", ios_base::out);

        //Verify customer account file is accessible and update email line if true
        if (customerAccount.is_open()) {
            while (getline(customerAccount, line)) {
                if (line[0] == 'E') {
                    tempFile << "Email: " << email << '\n';
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
            customerAccount.open("Cust_info_" + customerID + ".txt", ios_base::in);
            cout << "Customer email has been updated." << endl;
        }
        else {
            cout << "Customer account does not exist in database." << endl;
        }
    }

    // Getter and Setter for dateOfBirth
    string getDateOfBirth() const {
        return dateOfBirth;
    }
    void setDateOfBirth(const string& dob) {
        dateOfBirth = dob;

        fstream tempFile;			//Create new customer account file with updated contents
        string line;				//Store lines from file

        tempFile.open("TEMP.txt", ios_base::out);

        //Verify customer account file is accessible and update DOB line if true
        if (customerAccount.is_open()) {
            while (getline(customerAccount, line)) {
                if (line[0] == 'D') {
                    tempFile << "DOB: " << dateOfBirth << '\n';
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
            customerAccount.open("Cust_info_" + customerID + ".txt", ios_base::in);
            cout << "Customer date of birth has been updated." << endl;
        }
        else {
            cout << "Customer account does not exist in database." << endl;
        }
    }

    // Getter and Setter for username
    string getUsername() const {
        return username;
    }
    void setUsername(const string& user) {
        username = user;

        fstream tempFile;			//Create new customer account file with updated contents
        string line;				//Store lines from file

        tempFile.open("TEMP.txt", ios_base::out);

        //Verify customer account file is accessible and update username line if true
        if (customerAccount.is_open()) {
            while (getline(customerAccount, line)) {
                if (line[0] == 'U') {
                    tempFile << "Username: " << username << '\n';
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
            customerAccount.open("Cust_info_" + customerID + ".txt", ios_base::in);
            cout << "Customer username has been updated." << endl;
        }
        else {
            cout << "Customer account does not exist in database." << endl;
        }
    }

    // Getter and Setter for password
    string getPassword() const {
        return password;
    }
    void setPassword(const string& pass) {
        password = pass;
        fstream tempFile;			//Create new customer account file with updated contents
        string line;				//Store lines from file

        tempFile.open("TEMP.txt", ios_base::out);

        //Verify customer account file is accessible and update password line if true
        if (customerAccount.is_open()) {
            while (getline(customerAccount, line)) {
                if (line[0] == 'P') {
                    tempFile << "Password: " << password << '\n';
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
            customerAccount.open("Cust_info_" + customerID + ".txt", ios_base::in);
            cout << "Customer password has been updated." << endl;
        }
        else {
            cout << "Customer account does not exist in database." << endl;
        }
    }

    // display() - outputs all customer information in a neat, formatted manner
    void display() const {
        cout << "Customer Information:" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "ID:      " << customerID << endl;
        cout << "Name:    " << firstName << " " << lastName << endl;
        cout << "Mobile" << mobileNumber << endl;
        cout << "Address: " << address << endl;
        cout << "Email:   " << email << endl;
        cout << "DOB:     " << dateOfBirth << endl;
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
    }
};
