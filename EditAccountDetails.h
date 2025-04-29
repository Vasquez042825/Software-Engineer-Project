/*
Code Artifact: Edit Account Details
Description: Allows user to edit account details
Programmer: Jermal Sanders
Date Programmed: April 25, 2025
Variables:
	firstName: user's first name, lastName: user's last name,
	Address: user's physical address, mobileNumber: user's mobile number,
	emailAddress: user's email adress, Password: user's password
Files Access: fileName.txt
Files Changed: fileName.txt
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Edit_Account_Details
{
private:
	string firstName = "";
	string lastName = "";
	string Address = "";
	string mobileNumber = "";
	string emailAddress = "";
	string Password = "";
	fstream customerAccount;

public:
	struct customer
	{
		string fname;
		string lname;
		string addy;
		string mnum;
		string eaddy;
		string pass;
	};

	//Customer constructor
	customer* the_customer(const string& fname, const string& lname, const string& addy, const string& mnum, const string& eaddy)
	{
		return new customer{ fname,lname,addy,mnum,eaddy };
	}

	//Reading in customer data from file
	customer readCustomerData(const string& filename = "fileName.txt", const string& username = "johndoe")
	{
		customer cust;
		ifstream file(filename);
		if (!file)
		{
			cerr << "Error: Could not open file " << filename << endl;
			return cust;
		}

		string id, fname, lname, phone, address, email, dob, uname, pass;
		float balance;

		//Checking for formatting of file lines
		while (file >> id >> fname >> lname >> phone >> address >> email >> dob >> uname >> pass >> balance)
		{
			if (uname == username)
			{
				cust.fname = fname;
				cust.lname = lname;
				cust.mnum = phone;
				cust.addy = address;
				cust.eaddy = email;
				cust.pass = pass;
				break;
			}
		}

		file.close();
		return cust;
	}

	//Applying read data to a specific user
	void loadFromFile(const string& username, const string& filename = "fileName.txt")
	{
		ifstream file(filename);
		if (!file)
		{
			cerr << "Error: Could not open file " << filename << endl;
			return;
		}

		string id, fname, lname, phone, address, email, dob, uname, pass;
		float balance;

		while (file >> id >> fname >> lname >> phone >> address >> email >> dob >> uname >> pass >> balance)
		{
			if (uname == username)
			{
				firstName = fname;
				lastName = lname;
				mobileNumber = phone;
				Address = address;
				emailAddress = email;
				Password = pass;
				break;
			}
		}

		file.close();
	}

	//Writing edited data to the file
	void saveToFile(const string& username, const string& filename = "fileName.txt")
	{
		ifstream infile(filename);
		ofstream temp("temp.txt");
		if (!infile || !temp)
		{
			cerr << "Error: Could not open files for saving." << endl;
			return;
		}

		string id, fname, lname, phone, address, email, dob, uname, pass;
		float balance;

		while (infile >> id >> fname >> lname >> phone >> address >> email >> dob >> uname >> pass >> balance)
		{
			if (uname == username)
			{
				// Write updated values
				temp << id << " "
					<< firstName << " "
					<< lastName << " "
					<< mobileNumber << " "
					<< Address << " "
					<< emailAddress << " "
					<< dob << " "
					<< uname << " "
					<< Password << " "
					<< balance << endl;
			}
			else
			{
				// Write unchanged line
				temp << id << " " << fname << " " << lname << " " << phone << " " << address << " "
					<< email << " " << dob << " " << uname << " " << pass << " " << balance << endl;
			}
		}

		infile.close();
		temp.close();

		// Replace old file with updated one
		remove(filename.c_str());
		rename("temp.txt", filename.c_str());
	}

	//Account detail editor
	void edit()
	{
		int choice;

		do
		{
			cout << "\nAccount Editing Options:\n";
			cout << "1. First Name\n";
			cout << "2. Last Name\n";
			cout << "3. Address\n";
			cout << "4. Mobile Number\n";
			cout << "5. Email Address\n";
			cout << "6. Password\n";
			cout << "0. Exit Editing\n";
			cout << "Choose an option: ";
			cin >> choice;
			cin.ignore(); // Clear newline

			switch (choice)
			{
			case 1:
				cout << "Current First Name: " << firstName << "\nNew First Name: ";
				getline(cin, firstName);
				break;
			case 2:
				cout << "Current Last Name: " << lastName << "\nNew Last Name: ";
				getline(cin, lastName);
				break;
			case 3:
				cout << "Current Address: " << Address << "\nNew Address: ";
				getline(cin, Address);
				break;
			case 4:
				cout << "Current Mobile Number: " << mobileNumber << "\nNew Mobile Number: ";
				do {
					getline(cin, mobileNumber);
					if (!isValidNumber(mobileNumber))
						cout << "Invalid phone number format. Try again: ";
				} while (!isValidNumber(mobileNumber));
				break;

			case 5:
				cout << "Current Email: " << emailAddress << "\nNew Email Address: ";
				do {
					getline(cin, emailAddress);
					if (!isValidEmail(emailAddress))
						cout << "Invalid email format. Try again: ";
				} while (!isValidEmail(emailAddress));
				break;
			case 6:
				cout << "Current Password: " << Password << "\nNew Password: ";
				getline(cin, Password);
				break;
			case 0:
				cout << "Exiting edit mode.\n";
				break;
			default:
				cout << "Invalid option. Try again.\n";
			}

			if (choice != 0)
			{
				cout << "\nUpdated Account Info:\n";
				display();
			}

		} while (choice != 0);
	}

	//Format checker for phone number
	bool isValidNumber(const string& number)
	{
		for (char c : number)
		{
			if (!isdigit(c) && c != '-' && c != '(' && c != ')' && c != ' ')
				return false;
		}
		return !number.empty();
	}
	//Format checker for email
	bool isValidEmail(const string& email)
	{
		size_t atPos = email.find('@');
		size_t dotPos = email.find('.', atPos);
		return atPos != string::npos && dotPos != string::npos && dotPos > atPos;
	}

	//Deletes account entry
	void deleteAccount(const string& username, const string& filename = "fileName.txt")
	{
		ifstream infile(filename);
		ofstream temp("temp.txt");

		if (!infile || !temp)
		{
			cerr << "Error: Could not open files for deletion." << endl;
			return;
		}

		string id, fname, lname, phone, address, email, dob, uname, pass;
		float balance;
		bool found = false;

		while (infile >> id >> fname >> lname >> phone >> address >> email >> dob >> uname >> pass >> balance)
		{
			if (uname != username)
			{
				// Keep lines that do NOT match the username
				temp << id << " " << fname << " " << lname << " " << phone << " " << address << " "
					<< email << " " << dob << " " << uname << " " << pass << " " << balance << endl;
			}
			else
			{
				found = true;
			}
		}

		infile.close();
		temp.close();

		remove(filename.c_str());
		rename("temp.txt", filename.c_str());

		if (found)
		{
			cout << "Account successfully deleted from file." << endl;
		}
		else
		{
			cout << "Account not found in file." << endl;
		}
	}
	void deleteFromFile(const string& username, const string& filename = "fileName.txt")
	{
		ifstream infile(filename);
		ofstream temp("temp.txt");

		if (!infile || !temp)
		{
			cerr << "Error: Could not open files for deletion." << endl;
			return;
		}

		string id, fname, lname, phone, address, email, dob, uname, pass;
		float balance;
		bool found = false;

		while (infile >> id >> fname >> lname >> phone >> address >> email >> dob >> uname >> pass >> balance)
		{
			if (uname != username)
			{
				// Keep lines that do NOT match the username
				temp << id << " " << fname << " " << lname << " " << phone << " " << address << " "
					<< email << " " << dob << " " << uname << " " << pass << " " << balance << endl;
			}
			else
			{
				found = true;
			}
		}

		infile.close();
		temp.close();

		remove(filename.c_str());
		rename("temp.txt", filename.c_str());

		if (found)
		{
			cout << "Account successfully deleted from file." << endl;
		}
		else
		{
			cout << "Account not found in file." << endl;
		}
	}
	void display()
	{
		cout << "\nAccount Details:\n";
		cout << "First Name: " << firstName << endl;
		cout << "Last Name: " << lastName << endl;
		cout << "Address: " << Address << endl;
		cout << "Mobile Number: " << mobileNumber << endl;
		cout << "Email Address: " << emailAddress << endl;
	}

};
