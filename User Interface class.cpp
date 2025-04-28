#include <iostream>
#include <string>
using namespace std;

/*
Code Artifact: UserInterface
Description: Creates and manages User Interface displays for customers and admins
Programmer: Đạt Trịnh
Date Programmed: April 25, 2025
Variables: customerUI: stores the customer user interface message,
           adminUI: stores the admin user interface message
Files Accessed: None
Files Changed: None
*/

// UserInterface Class
class UserInterface {
private:
    string customerUI;
    string adminUI;

public:
    // Constructor
    UserInterface() {
        customerUI = "Displaying Customer User Interface...";
        adminUI = "Displaying Admin User Interface...";
    }

    // Function to show Customer UI
    void showCustomerUI() {
        cout << customerUI << endl;
    }

    // Function to show Admin UI
    void showAdminUI() {
        cout << adminUI << endl;
    }
};

int main() {
    // Make an object
    UserInterface ui;

    // Show both UIs
    ui.showCustomerUI();
    ui.showAdminUI();

    return 0;
}

