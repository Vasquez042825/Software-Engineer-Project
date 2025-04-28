/*
Code Artifact: UserInterface
Description: Creates and manages User Interface displays for customers and admins
Programmer: Đạt Trịnh
Date Programmed: April 28, 2025
Variables: customerUI: stores the customer user interface message,
           adminUI: stores the admin user interface message
Files Accessed: None
Files Changed: None
*/
#include <iostream>
#include <string>
using namespace std;

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

    // Show Customer UI
    void showCustomerUI() {
        cout << customerUI << endl;
    }

    // Show Admin UI
    void showAdminUI() {
        cout << adminUI << endl;
    }
};

// Example usage
int main() {
    // Create a UserInterface object
    UserInterface ui;

    // Display both UIs
    ui.showCustomerUI();
    ui.showAdminUI();

    return 0;
}
