#include <iostream>
#include "Customer.cpp"

using namespace std;
class Guest {
	public:
	void GuestMenu() {
		bool validOption = false;

		CustomerList customerList;

		while (!validOption) {
			int option = 0;

			// register variables
			string regisEmailTxt;
			// Display guest menu
			cout << "Choose a number for further action:\n1. Display all university information\n2. Search university details\n3. Register an account\n4. Return to login menu\nSelect your option: ";
			cin >> option;
			switch (option) {
			case 1:
				//// 1. Display all university information
				validOption = true;
				break;
			case 2:
				// 2. Search university details
				validOption = true;
				break;
			case 3:
				// 3. Register an account
				validOption = true;
				cout << "Please enter your registration details:\nEmail: ";
				cin >> regisEmailTxt;
				// Check if the userEmail includes "@gmail.com"
				if (regisEmailTxt.find("@gmail.com") == string::npos) {
					cout << "Registration failed. Email must include @gmail.com." << endl;
					break;
				}
				customerList.registerAccount(regisEmailTxt);
				break;
			case 4:
				// 4. Return to login menu
				validOption = true;
				break;
			default:
				// handle invalid option
				cout << "Error! Please enter a valid option!\n";
			}
		}
	};
};
