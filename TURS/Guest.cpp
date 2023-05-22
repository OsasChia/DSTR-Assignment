#include <iostream>
#include "Customer.cpp"
#include "Ranking.cpp"
#include <chrono> //time library
#include <time.h>

using namespace std;
using namespace std::chrono;

class Guest {
	public:
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
			cout << "Choose a number for further action:\n1. Display all university information\n2. Search university details\n3. Register an account\n4. Return to login menu\nSelect your option: ";
			cin >> guestOption;
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
				cout << "Time taken for Quick sort: " << durationn.count() << " microseconds." << endl;

				validOption = true;
				break;
			} else if (guestOption == 2) {
				// 2. Search university details
				validOption = true;
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
};
