#include "Guest.cpp"
#include "University.cpp"
#include "Customer.cpp"
#include "Ranking.cpp"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
	// import all csv files here
	bool validOption = false;
	Guest guest; // declare and initialize the guest object outside the switch statement
	UniversityList universityList;
	CustomerList customerList;
	RankingList rankingList;
	//universityList = universityList.importUniversity();
	//customerList = customerList.importCustomer();
	rankingList = rankingList.importRanking();
	while (!validOption) {
		//switch case
		int option = 0;
		//login variables
		string emailTxt;
		string passwordTxt;
		bool loginStatus;
		// Display login menu
		cout<< "Choose a number for further action:\n1. View as Guest\n2. Login\n3. Register an account\nEnter your option: ";
		cin >> option;
		switch (option) {
		case 1:
			// 1. View as guest
			validOption = true;
			// create a Guest object
			guest.GuestMenu(); // call the GuestMenu() function
			break;
		case 2:
			// 2. Login
			validOption = true;
			// login function
			// Display login menu
			cout << "Please enter your login details:\nEmail: ";
			cin >> emailTxt;
			cout << "Password: ";
			cin >> passwordTxt;
			loginStatus = customerList.loginCustomer(customerList, emailTxt, passwordTxt);
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