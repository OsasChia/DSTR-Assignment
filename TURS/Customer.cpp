#include <fstream>
#include <iostream>
#include <string>
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

	void ModifyCustInfo() {
		string custEmail;
		cout << "Enter customer email to modify: ";
		cin >> custEmail;

		Customer* current = head;
		bool isFound = false;

		///////////////////can used the other search algorithm instead of this linear search
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

			cout << "Customer information updated successfully." << endl;
		} else {
			cout << "Customer with email " << custEmail << " not found." << endl;
		}
	};

	bool DeleteCust(string email) {
		// check if list is empty
		if (head == NULL) {
			cout << "List is empty!" << endl;
			return false;
		}

		// check if head node needs to be deleted
		if (head->custEmail == email) {
			Customer* temp = head;
			head = head->nextAddress;
			delete temp;
			return true;
		}

		// find node to delete
		Customer* current = head->nextAddress;
		Customer* prev = head;
		while (current != NULL) {
			if (current->custEmail == email) {
				prev->nextAddress = current->nextAddress;
				delete current;
				return true;
			}
			prev = current;
			current = current->nextAddress;
		}

		// node not found
		cout << "Customer with email " << email << " not found in list." << endl;
		return false;
	};

	bool loginCustomer(CustomerList customerList, string custEmail, string custPassword) {
		Customer* current = customerList.head;

		while (current != NULL) {
			if (current->custEmail == custEmail && current->custPassword == custPassword) {
				// Login successful
				cout << "Login successful." << endl;
				return true;
			}
			current = current->nextAddress;
		}

		// Login failed
		cout << "Login failed. Invalid email or password." << endl;
		return false;
	}

	void registerAccount(
		CustomerList customerList,
		string custEmail,
		string custName,
		string custPassword,
		string custContactNo,
		string logoutTime) {
		customerList.InsertToEndList(custEmail, custName, custPassword, custContactNo, "null");
	}

	CustomerList importCustomer() {
		CustomerList allCustomerList;
		string file_custEmail;
		string file_custName;
		string file_custPassword;
		string file_custContactNo;
		string file_logoutTime;
		int IDcounter = 1;
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
		//allCustomerList.InsertToEndList("vivian@gmail.com", "vivian Ho", "vivian", "016789012", "null");
		//allCustomerList.DisplayAllCustInfo();
		//exportCustomer(allCustomerList);
		return allCustomerList;
	};

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












// int main()
//{
//	//Call object and constructor
//	CustomerList custList;
//	//Define variable
//	string custEmail, custName, custPassword, custContactNo, logoutTime;
//	//input file
//	ifstream file("C://Users//cylin//Desktop//APU//APU2F2209SE//Semester 2//DSTR//Assignment//Customer.csv");
//	//skip the first line
//	string str;
//	getline(file, str);
//	str.clear();
//	while (file.good())
//	{
//		getline(file, custEmail, ',');
//		getline(file, custName, ',');
//		getline(file, custPassword, ',');
//		getline(file, custContactNo, ',');
//		getline(file, logoutTime, '\n');
//		if (custEmail == "custEmail")
//		{
//			continue;
//		}
//		else if (custEmail == "")
//		{
//			break;
//		}
//		//InsertToTheEndList(custEmail, custName, custPassword, custContactNo);
//		custList.InsertToTheEndList(custEmail, custName, custPassword, custContactNo, logoutTime);
//	}
//	file.close();
//
//	cout << "Final Customer List from the CSV file as below: " << endl << string(50, '=') << endl;
//	custList.DisplayAllCustInfo();
//	cout << endl << string(50, '=') << endl;
//
//	//Modify Customer Details
//	//custList.ModifyCustInfo();
//
//	//Delete Customer
//	//Ask the user for the email of the customer to delete
//	string emailToDelete;
//	cout << "Enter the email of the customer to delete: ";
//	cin >> emailToDelete;
//	//call delete method
//	// call the DeleteCustInfo function to delete the customer
//	bool deleted = custList.DeleteCust(emailToDelete);
//
//	// display the updated list of customers
//	if (deleted)
//	{
//		cout << "Customer with email " << emailToDelete << " deleted successfully." << endl;
//	}
//	else
//	{
//		cout << "Customer with email " << emailToDelete << " not found." << endl;
//	}
//
//	// Display updated list
//	cout << "Updated Customer List: " << endl << string(50, '=') << endl;
//	custList.DisplayAllCustInfo();
//	cout << endl << string(50, '=') << endl;
//	return 0;
// }
