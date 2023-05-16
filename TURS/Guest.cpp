#include <iostream>

using namespace std;
class Guest {
	public:
	void GuestMenu() {
		bool validOption = false;
		while (!validOption) {
			int option = 0;
			// Display guest menu
			cout << "Choose a number for further action:\n1. Display all university information\n2. Search university "
							"details\n3. Register an account\nReturn to login menu: ";
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
