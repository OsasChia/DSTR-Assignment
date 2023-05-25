#include <iostream>
#include <string>

#include <chrono> //time library
#include <time.h>

#include "Customer.cpp"
#include "Ranking.cpp"
#include "Feedback.cpp"
#include "University.cpp"
#include "Guest.cpp"
#include "InputHandler.cpp"

using namespace std;
using namespace std::chrono;

class Menu {
	InputHandler inputhandler;

	public:
	void Exit() { 
		cout << "ByeBye" << endl;
		exit(0);
	}

	void startMenu() {
		cout << "1. View as Guest\n2. Login\n3. Register an account\n0. Exit\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// 1. View as guest
			guestMenu();
			break;

		case 2:
			// 2. Login
			loginMenu();
			break;
		case 3:
			// 3. Register an account
			registerMenu();
			break;
		case 0:
			// 4. Exit
			Exit();
			break;
		default:
			// handle invalid option
			cout << "Error! Please enter a valid option!" << endl;

			startMenu();
			break;
		}
	};

	void guestMenu() { 
		// Import Ranking
		RankingList rankingList;
		rankingList.importRanking();

		cout << "1. Display all university information\n2. Search university\n3. Sort university\n0. Return to start menu\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// Display all university information
			
			// Start with the first page
			rankingList.DisplayRankingInfo(1);
			guestMenu();
			break;
		case 2:
			// Search university
			searchMenu();
			break;
		case 3:
			// Sort university
			sortMenu();
			break;
		case 0:
			// Return to start menu
			startMenu();
			break;
		default:
			// handle invalid option
			cout << "Error! Please enter a valid option!\n";
			guestMenu();
			break;
		}
	}

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
			customerMenu();
		} else {
			startMenu();
		}
	}

	void registerMenu() { 
		CustomerList customerList;
		
		string regisEmailTxt;

		cout << "Please enter your registration details:\nEmail: ";
		cin >> regisEmailTxt;

		// Check if the userEmail includes "@gmail.com"
		if (regisEmailTxt.find("@gmail.com") == string::npos) {
			cout << endl << "Registration failed. Email must include @gmail.com." << endl << endl;
			startMenu();
		}
		
		customerList.registerAccount(regisEmailTxt);
		startMenu();
	}

	void customerMenu() {
		RankingList rankingList;
		rankingList.importRanking();
		
		cout << "Welcome back!" << endl;
		cout << "1. View university\n2. Search university\n3. Sort university\n4. Favorite universities\n5. View feedbacks\n0. Logout\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// Start with the first page
			rankingList.DisplayRankingInfo(1);
			customerMenu();
			break;
		case 2:
			// Search university
			searchMenu();
			break;
		case 3:
			// Sort university
			sortMenu();
			break;
		case 4:
			// Save favorite universities
			favoriteMenu();
			break;
		case 5:
			// View feedbacks
			feedbackMenu();
			break;
		case 0:
			//  Logout
			startMenu();
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			customerMenu();
			break;
		}
	}

	void adminDashboard() {
		CustomerList customerList;
		FeedbackList feedbackList;

		// Display admin menu
		cout << "Welcome to admin menu!\n\n";
		cout << "1. Display all customer information\n2. Display all feedback\n0. Logout\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// 1. Display all customer information
			customerList.DisplayAllCustInfo();
			cout << "hello" << endl;
			adminDashboard();
			break;
		case 2:
			// 2. Display all feedback
			feedbackList.DisplayAllPendingFeedbackInfo();
			break;
		case 0:
			// 3. Logout
			cout << "Successfully Logout!\n";
			startMenu();
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			adminDashboard();
			break;
		}
	}

	void searchMenu() {
		UniversityList universityList;
		RankingList rankingList;

		universityList.importUniversity();
		rankingList.importRanking();
		
		string searchQuery;

		cout << "1. Search university by name\n2. Search university by country\n3. Two Pointer vs Binary Search (Time Complexity)\n0. Return to guest menu\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// Search university by name
			cout << "Search University Country: ";
			cin.ignore();
			getline(cin, searchQuery);
			cout << endl;

			universityList.SearchUniByName(searchQuery);
			searchMenu();
			break;
		case 2:
			// Search university by country
			cout << "Search University Country: ";
			cin.ignore();
			getline(cin, searchQuery);
			cout << endl;

			rankingList.binarySearchUniByName(searchQuery);
			searchMenu();
			break;
		case 3: {
			// Two Pointer vs Binary Search (Time Complexity)
			cout << "Search University Country: ";
			cin.ignore();
			getline(cin, searchQuery);
			cout << endl;

			auto start = high_resolution_clock::now();
			universityList.SearchUniByName(searchQuery);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken for Two Pointer Search: " << duration.count() << " microseconds." << endl;

			auto startt = high_resolution_clock::now();
			rankingList.binarySearchUniByName(searchQuery);
			auto stopp = high_resolution_clock::now();
			auto durationn = duration_cast<microseconds>(stopp - startt);
			cout << "Time taken for Binary Search: " << durationn.count() << " microseconds." << endl << endl;

			searchMenu();
			break;
		}
		case 0:
			// Return to guest menu
			guestMenu();
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			searchMenu();
			break;
		}
	}

	void sortMenu() {
		RankingList rankingList;
		UniversityList universityList;

		cout << "1. Sort university by name\n2. Sort university by ArScore\n3. Sort university by FsrScore\n4. Sort university by ErScore\n5. Quick Sort vs Merge Sort (Time Complexity)\n0. Return to start menu\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// Sort university by name
			rankingList.MergeSortAndDisplayUniByOption(1);
			searchMenu();
			break;
		case 2:
			// Sort university by ArScore
			rankingList.MergeSortAndDisplayUniByOption(2);
			searchMenu();
			break;
		case 3:
			// Sort university by FsrScore
			rankingList.MergeSortAndDisplayUniByOption(3);
			searchMenu();
			break;
		case 4:
			// Sort university by ErScore
			rankingList.MergeSortAndDisplayUniByOption(4);
			searchMenu();
			break;
		case 5: {
			// Quick Sort vs Merge Sort (Time Complexity)

			auto start = high_resolution_clock::now();
			rankingList.QuickSortAndDisplayUni(1);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken for Quick sort: " << duration.count() << " microseconds." << endl;

			auto startt = high_resolution_clock::now();
			rankingList.MergeSortForCompare(1);
			auto stopp = high_resolution_clock::now();
			auto durationn = duration_cast<microseconds>(stopp - startt);
			cout << "Time taken for Merge sort: " << durationn.count() << " microseconds." << endl << endl;

			searchMenu();
			break;
		}
		case 0:
			// Return 
			guestMenu();
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			searchMenu();
			break;
		}
	}

	void feedbackMenu() {
		cout << "1. Send feedback\n2. Reply feedback\n0. Return to customer menu\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// Send feedback
			// 

			searchMenu();
			break;
		case 2:
			// Reply feedback
			//

			searchMenu();
			break;
		case 0:
			// Return to customer menu
			customerMenu();
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			feedbackMenu();
			break;
		}
	}

	void favoriteMenu() {
		cout << "1. View favorite university\n2. Add favorite university\n3. Remove favorite university\n0. Return to customer menu\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// View favorite university
			//

			favoriteMenu();
			break;
		case 2:
			// Add favorite university
			//

			favoriteMenu();
			break;
		case 3:
			// Remove favorite university
			//

			favoriteMenu();
			break;
		case 0:
			// Return to customer menu
			customerMenu();
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			favoriteMenu();
			break;
		}
	}
};