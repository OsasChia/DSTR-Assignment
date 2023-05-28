#include <iostream>
#include <string>

#include <chrono> //time library
#include <time.h>
#include <ctime>

#include "Customer.cpp"
#include "Ranking.cpp"
#include "Feedback.cpp"
#include "University.cpp"
#include "Guest.cpp"
#include "Favourite.cpp"
#include "InputHandler.cpp"

using namespace std;
using namespace std::chrono;

class Menu {
	InputHandler inputhandler;
	
	public:
	string custSessionEmail;
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
		cout << endl << endl;

		if (loginEmailTxt == "admin" && passwordTxt == "admin") {
			adminDashboard();
		}else if(loginEmailTxt != "admin" && passwordTxt != "admin") {
			custSession = customerList.loginCustomer(loginEmailTxt, passwordTxt);
			if (!custSession.empty()) {
			cout << "Hello " + custSession << endl << endl;
			custSessionEmail = loginEmailTxt;
			customerMenu();
			} else {
			startMenu();
			}
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
		CustomerList customerList;
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
			customerList.logoutCustomer(custSessionEmail);
			custSessionEmail = "";
			cout << "Successfully Logout!" << endl << endl;
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
		FeedbackList data = feedbackList.importFeedback();
		customerList.importCustomer();

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
			feedbackList.feedbackExists(data.getHead());
			feedbackMenu();
			break;
		case 0:
			// 3. Logout
			cout << "Successfully Logout!" << endl << endl;
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

		cout << "1. Search university by name\n2. Search university by country\n3. Two Pointer vs Binary Search (Time Complexity)\n0. Return to user menu\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// Search university by name
			cout << "Search University Name: ";
			cin.ignore();
			getline(cin, searchQuery);
			cout << endl;

			universityList.SearchUniByName(searchQuery);
			//rankingList.binarySearchUniByName(searchQuery);
			searchMenu();
			break;
		case 2:
			// Search university by country
			cout << "Search University Country: ";
			cin.ignore();
			getline(cin, searchQuery);
			cout << endl;
			universityList.SearchUniByCountry(searchQuery);
			//rankingList.binarySearchUniByName(searchQuery);
			searchMenu();
			break;
		case 3: {
			// Two Pointer vs Binary Search (Time Complexity)
			cout << "Search University Name: ";
			cin.ignore();
			getline(cin, searchQuery);
			cout << endl;

			auto start = high_resolution_clock::now();
			universityList.SearchUniByName(searchQuery);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken for Two Pointer Search: " << duration.count() << " microseconds." << endl << endl;

			auto startt = high_resolution_clock::now();
			rankingList.binarySearchUniByName(searchQuery);
			auto stopp = high_resolution_clock::now();
			auto durationn = duration_cast<microseconds>(stopp - startt);
			cout << "Time taken for Binary Search: " << durationn.count() << " microseconds." << endl << endl;

			searchMenu();
			break;
		}
		case 0:
			if (custSessionEmail.empty()) {
				// Return to guest menu
				guestMenu();
			} else if (!custSessionEmail.empty()) {
				customerMenu();
			} else {
				adminDashboard();
			}
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
			rankingList.QuickSortCompare(1);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken for Quick sort: " << duration.count() << " microseconds." << endl;

			auto startt = high_resolution_clock::now();
			rankingList.MergeSortCompare(1);
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
		FeedbackList feedbackList; 
		FeedbackList data = feedbackList.importFeedback();
		UniversityList universityList;

		universityList.importUniversity();

		string universityID, feedback, feedbackID, reply;
		time_t t = time(nullptr);
		tm now;
		char buffer[128];
		//customer side feedback menu
		if (!custSessionEmail.empty()) {
			cout << "1. Send feedback \n2. View Reply \n0. Return to customer menu\n";
			int option = inputhandler.handleUserInput();
			cout << endl;

			switch (option) {
			case 1:
				// Send feedback
				cout << "Enter University ID: ";
				cin.ignore();
				getline(cin,universityID);
				if (universityList.SearchUniByID(universityID)) {
					cout << "Enter your feedback: ";
					getline(cin, feedback);
					cout << endl;
					localtime_s(&now, &t);
					strftime(buffer, sizeof(buffer), "%d/%m/%Y", &now);
					feedbackList.addFeedback(data, custSessionEmail, universityID, feedback, buffer);
				} else {
					cout << "Invalid University ID. Cannot send feedback." << endl << endl;
					searchMenu();
					break;
				}
				searchMenu();
				break;
			case 2:
				// Reply feedback
				feedbackList.displayByReplyDate(data.getHead(), custSessionEmail);
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
		// admin side feedback menu
		else {
			cout << "1. Reply Feedback \n0. Return to Admin Dashboard\n";
			int option = inputhandler.handleUserInput();
			cout << endl;

			switch (option) {
			case 1:
				// Reply feedback
				cout << "Enter Feedback ID: ";
				cin.ignore();
				getline(cin, feedbackID);

				if (feedbackList.SearchFeedbackByID(data, feedbackID)) {
					cout << "Enter your reply: ";
					getline(cin, reply);
					cout << endl;
					localtime_s(&now, &t);
					strftime(buffer, sizeof(buffer), "%d/%m/%Y", &now);
					feedbackList.ReplyFeedback(data, feedbackID, reply, buffer);
				} else {
					cout << "Invalid Feedback ID." << endl << endl;
					feedbackMenu();
					break;
				}
				feedbackMenu();
				break;
			case 0:
				// Return to admin dashboard
				adminDashboard();
				break;
			default:
				// Error
				cout << "Error! Please enter a valid option!\n";
				feedbackMenu();
				break;
			}
		}
	}

	void favoriteMenu() {
		FavouriteList favouriteList;
		FavouriteList data = favouriteList.importFavourite();

		UniversityList universityList;
		universityList.importUniversity();

		string universityID, favID;

		cout << "1. View favorite university\n2. Add favorite university\n3. Remove favorite university\n0. Return to customer menu\n";
		int option = inputhandler.handleUserInput();
		cout << endl;
		
		switch (option) {
		case 1:
			// View favorite university
			favouriteList.favouriteExists(data.getHead(), custSessionEmail);
			favoriteMenu();
			break;
		case 2:
			// Add favorite university
			// Send feedback
			cout << "Enter University ID: ";
			cin.ignore();
			getline(cin, universityID);
			if (universityList.SearchUniByID(universityID)) {
				favouriteList.addFavourite(data, custSessionEmail, universityID);
			} else {
				cout << "Invalid University ID. Cannot save favourite." << endl << endl;
				favoriteMenu();
				break;
			}
			favoriteMenu();
			break;
		case 3:
			// Remove favorite university
			cout << "Enter favourite ID: ";
			cin.ignore();
			getline(cin, favID);

			if (favouriteList.SearchFavByID(data, favID)) {
				favouriteList.DeleteFav(favID);
			} else {
				cout << "Invalid Favourite ID." << endl << endl;
				favoriteMenu();
				break;
			}

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