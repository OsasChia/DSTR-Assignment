//#include "Customer.cpp"
//# include "Favourite.cpp"
//#include "Feedback.cpp"
//#include "Ranking.cpp"
//#include "University.cpp"
//#include "TURS.h"
#include "Guest.cpp"
#include <iostream>

using namespace std;

int main() {

	// import all csv files here

	bool validOption = false;
	Guest guest; // declare and initialize the guest object outside the switch statement
	while (!validOption) {
		int option = 0;
		// Display login menu
		cout << "Choose a number for further action:\n1. View as Guest\n2. Login\n3. Register an account\nEnter your option: ";
		cin >> option;
		switch (option) {
		case 1:
			// 1. View as guest
			validOption = true;
			//create a Guest object
			//guest.GuestMenu(); // call the GuestMenu() function
			break;
		case 2:
			// 2. Login
			validOption = true;
			break;
		case 3:
			// 3. Register an account
			validOption = true;
			break;
		default:
			// handle invalid option
			cout << "Error! Please enter a valid option!\n";
		}
	}

	return 0;
}