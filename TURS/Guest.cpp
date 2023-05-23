#include <iostream>
#include "Customer.cpp"
#include "Ranking.cpp"
#include <chrono> //time library
#include <time.h>
#include <string>

using namespace std;
using namespace std::chrono;

class Guest {
	public:
	void startMenu(){ 
		int option;

		cout << "1. View as Guest\n2. Login\n3. Register an account\nEnter your option: ";
		cin >> option;
		cout << endl;

		switch (option) {
		case 1:
			// 1. View as guest
			GuestMenu();
			break;

		case 2:
			// 2. Login
			loginMenu();
			break;
		case 3:
			// 3. Register an account
			registerMenu();
			break;
		default:
			// handle invalid option
			cout << "Error! Please enter a valid option!" << endl;

			startMenu();
			break;
		}
	};

	void GuestMenu() {
		// 1. Display all university information
		RankingList rankingList;

		// 3. Register an account
		CustomerList customerList;

		bool validOption = false;
		while (!validOption) {
			int guestOption = 0;
			// register variables
			string regisEmailTxt;
			// Display guest menu
			cout << "1. Display all university information\n2. Search university details\n3. Return to login menu\nSelect your option: ";
			cin >> guestOption;
			cout << endl;
			if (guestOption == 1) {
				// 1. Display all university information
				auto start = high_resolution_clock::now();
				rankingList.MergeSortAndDisplayUniByOption(1);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "Time taken for Merge sort: " << duration.count() << " microseconds." << endl;

				auto startt = high_resolution_clock::now();
				rankingList.QuickSortAndDisplayUni(1);
				auto stopp = high_resolution_clock::now();
				auto durationn = duration_cast<microseconds>(stopp - startt);
				cout << "Time taken for Quick sort: " << durationn.count() << " microseconds." << endl << endl;

				validOption = true;
				
				GuestMenu();
				break;
			} else if (guestOption == 2) {
				// 2. Search university details
				string searchQuery;

				UniversityList universityList;
				universityList.importUniversity();

				cout << "Search University Name: ";
				cin.ignore();
				getline(cin, searchQuery);

				cout << searchQuery << endl;
				cout << endl << endl;

				universityList.SearchUniByName(searchQuery);
				break;
			} else if (guestOption == 3) {
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
			} else if (guestOption == 4) {
				// 4. Return to login menu
				validOption = true;
				break;
			} else {
				// handle invalid option
				cout << "Error! Please enter a valid option!\n";
				break;
			}
		}
	};

	// login function
	void loginMenu() {
		CustomerList customerList;

		// login variables
		string loginEmailTxt;
		string passwordTxt;
		string custSession;

		// Display login menu
		cout << "Please enter your login details:\nEmail: ";
		cin >> loginEmailTxt;
		cout << "Password: ";
		cin >> passwordTxt;
		cout << endl;


		if (loginEmailTxt == "admin" && passwordTxt == "admin") {
			adminDashboard();
		} 

		custSession = customerList.loginCustomer(loginEmailTxt, passwordTxt);

		if (!custSession.empty()) {
			cout << "Hello " + custSession << endl << endl;
		} else {
			startMenu();
		}

	}

	void registerMenu() {
		


	}

	void adminDashboard() {

	}
};
