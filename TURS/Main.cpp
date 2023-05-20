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
	customerList = customerList.importCustomer();
	//rankingList = rankingList.importRanking();
	while (!validOption) {
		//switch case
		int option = 0;
		//login variables
		string loginEmailTxt;
		string passwordTxt;
		bool loginStatus;
		//register variables
		string regisEmailTxt;
		// Display main menu
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
			cin >> loginEmailTxt;
			cout << "Password: ";
			cin >> passwordTxt;
			loginStatus = customerList.loginCustomer(customerList, loginEmailTxt, passwordTxt);
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
			customerList.registerAccount(customerList, regisEmailTxt);
			break;
		default:
			// handle invalid option
			cout << "Error! Please enter a valid option!\n";
		}
	}

	return 0;
}