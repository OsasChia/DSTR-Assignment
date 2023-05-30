#include <iostream>
#include <string>

#include <chrono> //time library
#include <time.h>
#include <ctime>

#include "Customer.cpp"
#include "Ranking.cpp"
#include "Feedback.cpp"
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
		//import customer data
		CustomerList customerList;
		CustomerList custData = customerList.importCustomer();

		//import favourite data
		FavouriteList favouriteList;
		FavouriteList favData = favouriteList.importFavourite();

		//import feedback data
		FeedbackList feedbackList;
		FeedbackList feedbackData = feedbackList.importFeedback();

		//import ranking data
		RankingList rankingList;
		RankingList rankingData = rankingList.importRanking();

		cout << "1. View as Guest\n2. Login\n3. Register an account\n0. Exit\n";
		int option = inputhandler.handleUserInput();
		cout << endl;
		
		switch (option) {
		case 1:
			// 1. View as guest
			guestMenu(custData, favData, feedbackData, rankingData);
			break;
		case 2:
			// 2. Login
			loginMenu(custData, favData, feedbackData, rankingData);
			break;
		case 3:
			// 3. Register an account
			registerMenu(custData);
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

	void guestMenu(
		CustomerList& custData,
		FavouriteList& favData,
		FeedbackList& feedbackData,
		RankingList& rankingData) { 
		RankingList rankingList;

		cout << "1. Display all university information\n2. Search university\n3. Sort university\n4. Register an account\n0. Return to start menu\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// Display all university information sorting by ranking
			// Start with the first page
			rankingList.MergeSortAndDisplayUniByOption(rankingData, 5);
			guestMenu(custData, favData, feedbackData, rankingData);
			break;
		case 2:
			// Search university
			searchMenu(custData, favData, feedbackData, rankingData);
			break;
		case 3:
			// Sort university
			sortMenu(custData, favData, feedbackData, rankingData);
			break;
		case 4:
			//Register an account
			registerMenu(custData);
			break;
		case 0:
			// Return to start menu
			startMenu();
			break;
		default:
			// handle invalid option
			cout << "Error! Please enter a valid option!\n";
			guestMenu(custData, favData, feedbackData, rankingData);
			break;
		}
	}

	// login function
	void loginMenu(
		CustomerList& custData,
		FavouriteList& favData,
		FeedbackList& feedbackData,
		RankingList& rankingData) {
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

		if (loginEmailTxt == "admin@gmail.com" && passwordTxt == "admin") {
			adminDashboard(custData, favData, feedbackData, rankingData);
		}else if(loginEmailTxt != "admin@gmail.com" && passwordTxt != "admin") {
			custSession = customerList.loginCustomer(custData, loginEmailTxt, passwordTxt);
			
			if (!custSession.empty()) {
			cout << "Hello " + custSession << endl << endl;
			custSessionEmail = loginEmailTxt;

			customerMenu(custData, favData, feedbackData, rankingData);
			} else {
				startMenu();
			}
		} else {
			cout << "Incorrect email or password." << endl << endl;
			startMenu();
		}
	}

	void registerMenu(CustomerList& custData) { 
		CustomerList customerList;
		
		string regisEmailTxt;

		cout << "Please enter your registration details:\nEmail: ";
		cin >> regisEmailTxt;

		// Check if the userEmail includes "@gmail.com"
		if (regisEmailTxt.find("@gmail.com") == string::npos) {
			cout << endl << "Registration failed. Email must include @gmail.com." << endl << endl;
			startMenu();
		}
		
		customerList.registerAccount(custData,regisEmailTxt);
		startMenu();
	}

	void customerMenu(
		CustomerList& custData,
		FavouriteList& favData,
		FeedbackList& feedbackData,
		RankingList& rankingData) {
		CustomerList customerList;
		FeedbackList feedbackList;
		FavouriteList favouriteList;
		RankingList rankingList;
		
		cout << "Welcome back!" << endl;
		cout << "1. View university\n2. Search university\n3. Sort university\n4. View favorite universities\n5. View feedbacks\n0. Logout\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// Start with the first page
			rankingList.MergeSortAndDisplayUniByOption(rankingData, 5);
			customerMenu(custData, favData, feedbackData, rankingData);
			break;
		case 2:
			// Search university
			searchMenu(custData, favData, feedbackData, rankingData);
			break;
		case 3:
			// Sort university
			sortMenu(custData, favData, feedbackData, rankingData);
			break;
		case 4:
			// Save favorite universities
			favoriteMenu(custData, favData, feedbackData, rankingData);
			break;
		case 5:
			// View feedbacks
			feedbackMenu(custData, favData, feedbackData, rankingData);
			break;
		case 0:
			//  Logout
			customerList.logoutCustomer(custData, custSessionEmail);
			customerList.exportCustomer(custData);
			favouriteList.exportFavourite(favData);
			feedbackList.exportFeedback(feedbackData);

			custSessionEmail = "";
			
			cout << "Successfully Logout!" << endl << endl;
			startMenu();
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			customerMenu(custData, favData, feedbackData, rankingData);
			break;
		}
	}

	void adminDashboard(
		CustomerList& custData,
		FavouriteList& favData,
		FeedbackList& feedbackData,
		RankingList& rankingData) {
		CustomerList customerList;
		FeedbackList feedbackList;
		FavouriteList favouriteList;

		// Display admin menu
		cout << "Welcome to admin menu!\n\n";
		cout << "1. Display all customer information\n2. Display all feedback\n3. Top 10 favourite universities\n0. Logout\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// 1. Display all customer information
			customerList.DisplayAllCustInfo(custData);
			modifyCustomerMenu(custData, favData, feedbackData, rankingData);
			break;
		case 2:
			// 2. Display all feedback
			feedbackList.feedbackExists(feedbackData);
			feedbackMenu(custData, favData, feedbackData, rankingData);
			break;
		case 3: {
			// 3. Top 10 favourite universities
			favouriteList.countTopTenFavorites(favData);
			adminDashboard(custData, favData, feedbackData, rankingData);
			break;
		}
		case 0:
			// 3. Logout
			customerList.exportCustomer(custData);
			favouriteList.exportFavourite(favData);
			feedbackList.exportFeedback(feedbackData);

			cout << "Successfully Logout!" << endl << endl;
			startMenu();
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			adminDashboard(custData, favData, feedbackData, rankingData);
			break;
		}
	}

	void searchMenu(
		CustomerList& custData,
		FavouriteList& favData,
		FeedbackList& feedbackData,
		RankingList& rankingData) {
		RankingList rankingList;
		
		string searchQuery;

		cout << "1. Search university by ranking\n2. Search university by name\n3. Search university by country\n4. Two Pointer vs Binary Search (Time Complexity)\n0. Return to user menu\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// Search university by ranking
			cout << "Search University Ranking: ";
			
			// !!!! THIS ONE MUST INPUT AN INTEGER BUT I LAZY PUT VALIDATION !!!! //
			// !!!! CAN CHECK THE binarySearchUniByRanking FUNCTION INSIDE !!!! //
			cin.ignore();
			getline(cin, searchQuery);
			cout << endl;

			rankingList.binarySearchUniByRanking(rankingData, searchQuery);
			searchMenu(custData, favData, feedbackData, rankingData);
			break;
		case 2:
			// Search university by name
			cout << "Search University Name: ";
			cin.ignore();
			getline(cin, searchQuery);
			cout << endl;

			rankingList.searchUniByName(rankingData, searchQuery);
			searchMenu(custData, favData, feedbackData, rankingData);
			break;
		case 3:
			// Search university by country
			cout << "Search University Country: ";
			cin.ignore();
			getline(cin, searchQuery);
			cout << endl;

			rankingList.searchUniByCountry(rankingData,searchQuery);
			searchMenu(custData, favData, feedbackData, rankingData);
			break;
		case 4: {
			// Two Pointer vs Binary Search (Time Complexity)
			cout << "Search University Ranking: ";
			
			// !!!! THIS ONE MUST INPUT AN INTEGER BUT I LAZY PUT VALIDATION !!!! //
			// !!!! CAN CHECK BOTH FUNCTIONS INSIDE !!!! //
			cin.ignore();
			getline(cin, searchQuery);
			cout << endl;

			auto start = high_resolution_clock::now();
			rankingList.searchUniByRankingForCompare(rankingData, searchQuery);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken for Two Pointer Search: " << duration.count() << " microseconds." << endl << endl;

			auto startt = high_resolution_clock::now();
			rankingList.binarySearchUniByRanking(rankingData, searchQuery);
			auto stopp = high_resolution_clock::now();
			auto durationn = duration_cast<microseconds>(stopp - startt);
			cout << "Time taken for Binary Search: " << durationn.count() << " microseconds." << endl << endl;

			searchMenu(custData, favData, feedbackData, rankingData);
			break;
		}
		case 0:
			if (custSessionEmail.empty()) {
				// Return to guest menu
				guestMenu(custData, favData, feedbackData, rankingData);
			} else if (!custSessionEmail.empty()) {
				customerMenu(custData, favData, feedbackData, rankingData);
			} else {
				adminDashboard(custData, favData, feedbackData, rankingData);
			}
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			searchMenu(custData, favData, feedbackData, rankingData);
			break;
		}
	}

	void sortMenu(
		CustomerList& custData,
		FavouriteList& favData,
		FeedbackList& feedbackData,
		RankingList& rankingData) {
		RankingList rankingList;

		cout << "1. Sort university by name\n2. Sort university by ArScore\n3. Sort university by FsrScore\n4. Sort university by ErScore\n5. Quick Sort vs Merge Sort (Time Complexity)\n0. Return to start menu\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// Sort university by name
			rankingList.MergeSortAndDisplayUniByOption(rankingData,1);
			sortMenu(custData, favData, feedbackData, rankingData);
			break;
		case 2:
			// Sort university by ArScore
			rankingList.MergeSortAndDisplayUniByOption(rankingData,2);
			sortMenu(custData, favData, feedbackData, rankingData);
			break;
		case 3:
			// Sort university by FsrScore
			rankingList.MergeSortAndDisplayUniByOption(rankingData,3);
			sortMenu(custData, favData, feedbackData, rankingData);
			break;
		case 4:
			// Sort university by ErScore
			rankingList.MergeSortAndDisplayUniByOption(rankingData,4);
			sortMenu(custData, favData, feedbackData, rankingData);
			break;
		case 5: {
			// Quick Sort vs Merge Sort (Time Complexity)
			rankingList.MergeSortCompare(rankingData, 3);

			auto start = high_resolution_clock::now();
			rankingList.QuickSortCompare(rankingData,1);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken for Quick sort: " << duration.count() << " microseconds." << endl;

			auto startt = high_resolution_clock::now();
			rankingList.MergeSortCompare(rankingData,1);
			auto stopp = high_resolution_clock::now();
			auto durationn = duration_cast<microseconds>(stopp - startt);
			cout << "Time taken for Merge sort: " << durationn.count() << " microseconds." << endl << endl;

			sortMenu(custData, favData, feedbackData, rankingData);
			break;
		}
		case 0:
			// Return 
			if (custSessionEmail.empty()) {
				// Return to guest menu
				guestMenu(custData, favData, feedbackData, rankingData);
			} else if (!custSessionEmail.empty()) {
				customerMenu(custData, favData, feedbackData, rankingData);
			} else {
				adminDashboard(custData, favData, feedbackData, rankingData);
			}
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			searchMenu(custData, favData, feedbackData, rankingData);
			break;
		}
	}

	void feedbackMenu(
		CustomerList& custData,
		FavouriteList& favData,
		FeedbackList& feedbackData,
		RankingList& rankingData) {
		FeedbackList feedbackList; 
		RankingList rankingList;

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
				if (rankingList.SearchUniByID(rankingData,universityID)) {
					cout << "Enter your feedback: ";
					getline(cin, feedback);
					cout << endl;
					localtime_s(&now, &t);
					strftime(buffer, sizeof(buffer), "%d/%m/%Y", &now);
					feedbackList.addFeedback(feedbackData, custSessionEmail, universityID, feedback, buffer);
				} else {
					cout << "Invalid University ID. Cannot send feedback." << endl << endl;
					feedbackMenu(custData, favData, feedbackData, rankingData);
					break;
				}
				feedbackMenu(custData, favData, feedbackData, rankingData);
				break;
			case 2:
				// Reply feedback
				feedbackList.displayByReplyDate(feedbackData, custSessionEmail);
				feedbackMenu(custData, favData, feedbackData, rankingData);
				break;
			case 0:
				// Return to customer menu
				customerMenu(custData, favData, feedbackData, rankingData);
				break;
			default:
				// Error
				cout << "Error! Please enter a valid option!\n";
				feedbackMenu(custData, favData, feedbackData, rankingData);
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

				if (feedbackList.SearchFeedbackByID(feedbackData, feedbackID)) {
					cout << "Enter your reply: ";
					getline(cin, reply);
					cout << endl;
					localtime_s(&now, &t);
					strftime(buffer, sizeof(buffer), "%d/%m/%Y", &now);
					feedbackList.ReplyFeedback(feedbackData, feedbackID, reply, buffer);
				} else {
					cout << "Invalid Feedback ID." << endl << endl;
					feedbackMenu(custData, favData, feedbackData, rankingData);
					break;
				}
				feedbackMenu(custData, favData, feedbackData, rankingData);
				break;
			case 0:
				// Return to admin dashboard
				adminDashboard(custData, favData, feedbackData, rankingData);
				break;
			default:
				// Error
				cout << "Error! Please enter a valid option!\n";
				feedbackMenu(custData, favData, feedbackData, rankingData);
				break;
			}
		}
	}

	void favoriteMenu(
		CustomerList& custData,
		FavouriteList& favData,
		FeedbackList& feedbackData,
		RankingList& rankingData) {
		FavouriteList favouriteList;
		RankingList rankingList;

		string universityID, favID;
		
		cout << "1. View favorite university\n2. Add favorite university\n3. Remove favorite university\n0. Return to customer menu\n";
		int option = inputhandler.handleUserInput();
		cout << endl;
		
		switch (option) {
		case 1:
			// View favorite university
			favouriteList.favouriteExists(favData, custSessionEmail);
			favoriteMenu(custData, favData, feedbackData, rankingData);
			break;
		case 2:
			// Add favorite university
			cout << "Enter University ID: ";
			cin.ignore();
			getline(cin, universityID);

			if (rankingList.SearchUniByID(rankingData,universityID)) {
				favouriteList
					.addFavourite(favData, custSessionEmail, universityID, rankingList.getUniNameByID(rankingData, universityID));
			} else {
				cout << "Invalid University ID. Cannot save favourite." << endl << endl;
				favoriteMenu(custData, favData, feedbackData, rankingData);
				break;
			}
			favoriteMenu(custData, favData, feedbackData, rankingData);
			break;
		case 3:
			// Remove favorite university
			cout << "Enter University ID: ";
			cin.ignore();
			getline(cin, universityID);

			if (rankingList.SearchUniByID(rankingData,universityID)) {
				favouriteList.deleteFav(favData, custSessionEmail, universityID);
			} else {
				cout << "Invalid University ID. Cannot delete favourite." << endl << endl;
				favoriteMenu(custData, favData, feedbackData, rankingData);
				break;
			}
			favoriteMenu(custData, favData, feedbackData, rankingData);
			break;
		case 0:
			// Return to customer menu
			customerMenu(custData, favData, feedbackData, rankingData);
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			favoriteMenu(custData, favData, feedbackData, rankingData);
			break;
		}
	}

	void modifyCustomerMenu(
		CustomerList& custData,
		FavouriteList& favData,
		FeedbackList& feedbackData,
		RankingList& rankingData) {
		CustomerList customerList;
		string custEmail;

		// Display modify customer menu
		cout << "1. Modify customer information\n2. Delete customer account\n0. Return to admin dashboard\n";
		int option = inputhandler.handleUserInput();
		cout << endl;

		switch (option) {
		case 1:
			// 1. Modify customer information
			cout << "Enter customer email: ";
			cin.ignore();
			getline(cin, custEmail);

			if (customerList.SearchCustomerByEmail(custData, custEmail)) {
				customerList.ModifyCustInfo(custData, custEmail);
			} else {
				cout << "Invalid Customer Email." << endl << endl;
				modifyCustomerMenu(custData, favData, feedbackData, rankingData);
				break;
			}
			modifyCustomerMenu(custData, favData, feedbackData, rankingData);
			break;
		case 2:
			// 2. Delete customer account
			cout << "Enter customer email: ";
			cin.ignore();
			getline(cin, custEmail);

			if (customerList.SearchCustomerByEmail(custData, custEmail)) {
				customerList.DeleteCust(custData, custEmail);
			} else {
				cout << "Invalid Customer Email." << endl << endl;
				modifyCustomerMenu(custData, favData, feedbackData, rankingData);
				break;
			}
			modifyCustomerMenu(custData, favData, feedbackData, rankingData);
			break;
		case 0:
			//0. Return to admin dashboard
			adminDashboard(custData, favData, feedbackData, rankingData);
			break;
		default:
			// Error
			cout << "Error! Please enter a valid option!\n";
			modifyCustomerMenu(custData, favData, feedbackData, rankingData);
			break;
		}
	}
};