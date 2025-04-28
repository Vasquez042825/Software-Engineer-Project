#pragma once

#include <iostream>
#include <string>
#include <fstream> 
using namespace std;

class Customer {
private:
    string customerID;      // Unique customer ID
    string firstName;       // Customer's first name
    string lastName;        // Customer's last name
    string mobileNumber;    // Customer's contact number
    string address;         // Customer's address
    string email;           // Customer's email address
    string dateOfBirth;     // Customer's date of birth
    string username;        // Customer's username
    string password;        // Customer's password
    float balance;

public:
    // Default constructor - initializes all member variables to "N/A"
    Customer() {
        customerID = "N/A";
        firstName = "N/A";
        lastName = "N/A";
        mobileNumber = "N/A";
        address = "N/A";
        email = "N/A";
        dateOfBirth = "N/A";
        username = "N/A";
        password = "N/A";
        balance = 0.0f;
    }

    // Getter and Setter for customerID
    string getCustomerID() const {
        return customerID;
    }
    void setCustomerID(const string& id) {
        customerID = id;
    }

    // Getter and Setter for firstName
    string getFirstName() const {
        return firstName;
    }
    void setFirstName(const string& name) {
        firstName = name;
    }

    // Getter and Setter for lastName
    string getLastName() const {
        return lastName;
    }
    void setLastName(const string& name) {
        lastName = name;
    }

    // Getter and Setter for mobileNumber
    string getMobileNumber() const {
        return mobileNumber;
    }
    void setMobileNumber(const string& number) {
        mobileNumber = number;
    }

    // Getter and Setter for address
    string getAddress() const {
        return address;
    }
    void setAddress(const string& addr) {
        address = addr;
    }

    // Getter and Setter for email
    string getEmail() const {
        return email;
    }
    void setEmail(const string& mail) {
        email = mail;
    }
    // Getter and Setter for dateOfBirth
    string getDateOfBirth() const {
        return dateOfBirth;
    }
    void setDateOfBirth(const string& dob) {
        dateOfBirth = dob;
    }

    // Getter and Setter for username
    string getUsername() const {
        return username;
    }
    void setUsername(const string& user) {
        username = user; 
    }

    // Getter and Setter for password
    string getPassword() const { 
        return password;
    }
    void setPassword(const string& pass) {
        password = pass;
    }

    // Getter for balance
    float getBalance() const {
        return balance;
    }

    // Setter for balance
    void setBalance(float newBalance) {
        balance = newBalance;
    }

      // Load customer information from file
void loadCustomerFromFile(ifstream& inputFile) {
    inputFile >> customerID
              >> firstName
              >> lastName
              >> mobileNumber
              >> address
              >> email
              >> dateOfBirth
              >> username
              >> password
        >> balance;
}
void saveCustomerToFile(ofstream& outputFile) const {
    outputFile << customerID << " " << firstName << " " << lastName << " "
        << mobileNumber << " " << address << " " << email << " "
        << dateOfBirth << " " << username << " " << password << " "
        << balance << endl;
}


    // display() - outputs all customer information in a neat, formatted manner
    void display() const {
        cout << "Customer Information:" << endl;
        cout << "ID:      " << customerID << endl;
        cout << "Name:    " << firstName << " " << lastName << endl;
        cout << "Mobile:  " << mobileNumber << endl;
        cout << "Address: " << address << endl;
        cout << "Email:   " << email << endl;
        cout << "DOB:        " << dateOfBirth << endl;
        cout << "Balance: $" << balance << endl;
    }
};

