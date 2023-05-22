#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include "University.cpp"
// #include "TURS.h"

using namespace std;

struct Customer {
	string custEmail;
	string custName;
	string custPassword;
	string custContactNo;
	string logoutTime;
	Customer* nextAddress;
	Customer* prevAddress;
};

class CustomerList {
	Customer* head = NULL;
	Customer* tail = NULL;

	public:
	// Methods
	Customer*
	CreateNewNode(string custEmail, string custName, string custPassword, string custContactNo, string logoutTime) {
		// create a empty new node first
		Customer* newnode = new Customer;
		newnode->custEmail = custEmail;
		newnode->custName = custName;
		newnode->custPassword = custPassword;
		newnode->custContactNo = custContactNo;
		newnode->logoutTime = logoutTime;
		newnode->nextAddress = NULL;

		// newnode address
		return newnode;
	};

	void InsertToEndList(string custEmail, string custName, string custPassword, string custContactNo, string logoutTime) {
		// call the create function to build a new single node first
		Customer* newnode = CreateNewNode(custEmail, custName, custPassword, custContactNo, logoutTime);

		// attach your node to the end of the list
		if (head == NULL) // list is the empty, always the newnode will be first node in list
		{
			head = tail = newnode;
		} else // if not empty list, just bring to the end of the list.
		{
			newnode->prevAddress = tail;
			tail->nextAddress = newnode;
			tail = newnode;
		}
	};
	
	void DisplayAllCustInfo() // Big O - O(n)
	{
		Customer* current = head;

		while (current != NULL) // means still not the end of the list
		{
			cout << "Customer Email: " << current->custEmail << endl;
			cout << "Customer Name: " << current->custName << endl;
			cout << "Customer Contact Number: " << current->custContactNo << endl;
			cout << "Customer logoutTime: " << current->logoutTime << endl << endl;
			current = current->nextAddress; // if you forgot this, will become a infinity loop
		}
		cout << "List is ended here! " << endl;
	};

	void ModifyCustInfo(string custEmail) {
		CustomerList customerList = importCustomer();

		Customer* current = customerList.head;
		bool isFound = false;

		while (current != NULL) {
			if (current->custEmail == custEmail) {
				isFound = true;
				break;
			}
			current = current->nextAddress;
		}

		if (isFound) {
			string newCustEmail, newCustName, newCustPassword, newCustContactNo, newLogoutTime;
			cout << "The chosen customer email is: " << current->custEmail << endl;
			cout << "Please write the updated customer details:" << endl;

			cout << "Customer Contact Number: ";
			cin >> newCustContactNo;
			current->custContactNo = newCustContactNo;

			exportCustomer(customerList);
			cout << "Customer information updated successfully." << endl;
		} else {
			cout << "Customer with email " << custEmail << " not found." << endl;
		}
	};

	bool DeleteCust(string email) {
		CustomerList customerList = importCustomer();
		// check if list is empty
		if (customerList.head == NULL) {
			cout << "List is empty!" << endl;
			return false;
		}

		// check if head node needs to be deleted
		if (customerList.head->custEmail == email) {
			Customer* temp = customerList.head;
			customerList.head = customerList.head->nextAddress;
			delete temp;
			return true;
		}

		// find node to delete
		Customer* current = customerList.head->nextAddress;
		Customer* prev = customerList.head;
		while (current != NULL) {
			if (current->custEmail == email) {
				prev->nextAddress = current->nextAddress;
				delete current;
				exportCustomer(customerList);
				return true;
			}
			prev = current;
			current = current->nextAddress;
		}

		// node not found
		cout << "Customer with email " << email << " not found in list." << endl;
		return false;
	};

	string loginCustomer(string custEmail, string custPassword) {

		CustomerList customerList = importCustomer();
		Customer* current = customerList.head;

		while (current != NULL) {
			if (current->custEmail == custEmail && current->custPassword == custPassword) {
				// Login successful
				cout << "Login successful." << endl;
				return current->custEmail;
			}
			current = current->nextAddress;
		}

		// Login failed
		cout << "Login failed. Invalid email or password." << endl;
		return "";
	}

	void logoutCustomer(string custEmail) {

		CustomerList customerList = importCustomer();

		// Get the current time
		time_t currentTime;
		time(&currentTime);

		// Convert the current time to string
		char timeString[26];
		ctime_s(timeString, sizeof(timeString), &currentTime);

		// Remove the newline character from timeString
		size_t len = strlen(timeString);
		if (len > 0 && timeString[len - 1] == '\n') {
			timeString[len - 1] = '\0';
		}

		if (customerList.head == NULL) {
			return;
		}

		Customer* current = customerList.head;

		while (current != NULL) {
			if (current->custEmail == custEmail) {
				current->logoutTime = timeString;
				cout << "Successfully logout!";
			}
			current = current->nextAddress;
		}

		exportCustomer(customerList);
	}

	void registerAccount(
		string custEmail) {
		string custName;
		string custPassword;
		string custContactNo;
		string logoutTime;

		CustomerList customerList = importCustomer();

		// Check if the customer email already exists
		Customer* current = customerList.head;
		while (current != NULL) {
			if (current->custEmail == custEmail) {
				cout << "Registration failed. Email already exists." << endl;
				return;
			}
			current = current->nextAddress;
		}

		//enter register info
		cout << "Customer Name: ";
		cin >> custName;
		cout << "Customer Password: ";
		cin >> custPassword;
		cout << "Customer Contact Number: ";
		cin >> custContactNo;

		customerList.InsertToEndList(custEmail, custName, custPassword, custContactNo, "null");
		exportCustomer(customerList);
	}

	CustomerList importCustomer() {
		CustomerList allCustomerList;
		string file_custEmail;
		string file_custName;
		string file_custPassword;
		string file_custContactNo;
		string file_logoutTime;
		ifstream file("Customer.csv");
		// skip the first line
		string str;
		getline(file, str);
		str.clear();
		while (file.good()) {
			getline(file, file_custEmail, ',');
			getline(file, file_custName, ',');
			getline(file, file_custPassword, ',');
			getline(file, file_custContactNo, ',');
			getline(file, file_logoutTime);
			if (file_custEmail == "custEmail") {
				continue;
			} else if (file_custEmail == "") {
				break;
			}
			allCustomerList.InsertToEndList(file_custEmail, file_custName, file_custPassword, file_custContactNo, file_logoutTime);
		}
		return allCustomerList;
	}

	void exportCustomer(CustomerList customerList) {
		ofstream ExportCustomerFile;
		ExportCustomerFile.open("Customer.csv");
		Customer* head = customerList.head;
		if (head == NULL) {
			return;
		}
		ExportCustomerFile << "custEmail,custName,custPassword,custContactNo, logoutTime" << endl;

		Customer* current = head;

		while (current != NULL) {
			ExportCustomerFile << current->custEmail << "," << current->custName << "," << current->custPassword << "," << current->custContactNo << "," <<current->logoutTime << endl;

			current = current->nextAddress;
		}
		ExportCustomerFile.close();
	}


};