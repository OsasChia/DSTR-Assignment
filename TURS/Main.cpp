#include "Guest.cpp"
#include "Feedback.cpp"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
	// import all csv files here
	bool validOption = false;
	Guest guest; // declare and initialize the guest object outside the switch statement
	CustomerList customerList;
	RankingList rankingList;

	FeedbackList feedbackList;
	bool exist = feedbackList.ExistFeedback("1");
	bool exist1 = feedbackList.ExistFeedback("31");
	if (exist && !exist1) {
		cout << "yes";
	} else {
		cout << "no";
	}


	guest.startMenu();
	
	while (!validOption) {
		//switch case
		int mainOption = 0;
		//login variables
		string loginEmailTxt;
		string passwordTxt;
		string custSession;
		//register variables
		string regisEmailTxt;
		// Display main menu
		cout<< "Choose a number for further action:\n1. View as Guest\n2. Login\n3. Register an account\nEnter your option: ";
		cin >> mainOption;
		cout << endl;
		switch (mainOption) {
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
			if (loginEmailTxt == "admin" && passwordTxt == "admin") {
				int adminOption = 0;
				cout << "Welcome to admin menu! Please enter your option for furher action:\n1. Display all customer "
								"information\n2. Display all feedback\n3. Logout\nSelect your option: ";
				cin >> adminOption;
				if (adminOption == 1) {
					//1. Display all customer information
					customerList.DisplayAllCustInfo();
					cout << "1. Back to admin menu\n2. Modify/Delete customer\nEnter your option: ";
					int viewCustOption = 0;
					if (viewCustOption == 1) {
						//1. Back to admin menu
					} else if (viewCustOption == 2) {
						//2. Modify/Delete customer
						cout << "Please enter customer Email to proceed:\nEmail: ";
						string adminTxt;
						cin >> adminTxt;
						cout << "Enter 1 to delete customer account\nEnter 2 to modify customer account\nEnter 3 to back to admin menu\nEnter your option: ";
						string adminOptionTxt;
						cin >> adminOptionTxt;
						if (adminOptionTxt == "1") {
							//delete customer account
							cout << "Are you sure you want delete this account?y if yes or n if no\nEnter your option: ";
							string deleteOption;
							if (deleteOption == "y") {
								bool deleteStatus = customerList.DeleteCust(custSession);
								customerList.DisplayAllCustInfo();
								//return to admin menu
							} else if (deleteOption == "n") {
								//return to admin menu
							} else {
								cout << "Error! Please enter a valid option!\n";
							}
						} else if (adminOptionTxt == "2") {
							//2 to modify customer account
							customerList.ModifyCustInfo(custSession);
						} else if (adminOptionTxt == "3") {
							//Enter 3 to back to admin menu
						} else {
							cout << "Error! Please enter a valid option!\n";
						}
					}
				} else if (adminOption == 2) {
					//2. Display all feedback
				} else if (adminOption == 3) {
					// 3. Logout
					cout << "Successfully Logout!\n";
					break;
				} else {
					cout << "Error! Please enter a valid option!\n";
				}
			} else {
				custSession = customerList.loginCustomer(loginEmailTxt, passwordTxt);
				cout << custSession << endl;
				if (!custSession.empty()) {
					cout << "Welcome to customer menu! Please enter your option for furher action:\n1. Display all university "
									"information\n2. Search university detail\n3. View favourtie university\n4. Logout\nSelect your "
									"option: ";

					// switch case
					int custMenu = 0;
					cin >> custMenu;

					// login menu
					if (custMenu == 1) {
						// 1. Display all university information
						rankingList.MergeSortAndDisplayUniByOption(1);
						cout << "Choose your further action:\n1. Sort university information in descending order based on academic "
										"reputation score\n2. Sort university information in descending order based on faculty/student "
										"ratio score\n3.3. Sort university information in descending order based on employer reputation "
										"score\n4. Back to customer menu\nEnter your option: ";
						int sortOption;
						cin >> sortOption;
						if (sortOption == 1) {
							// 1. Sort ArScore
							rankingList.MergeSortAndDisplayUniByOption(2);
						} else if (sortOption == 2) {
							// 2. Sort FsrScore
							rankingList.MergeSortAndDisplayUniByOption(3);
						} else if (sortOption == 3) {
							// 3. Sort ErScore
							rankingList.MergeSortAndDisplayUniByOption(4);
						} else if (sortOption == 4) {
							// 4. Back to customer menu
						} else {
							// handle invalid option
							cout << "Error! Please enter a valid option!\n";
							break;
						}
					} else if (custMenu == 2) {
						// 2. Search university detail
					} else if (custMenu == 3) {
						// 3. View favourtie university
					} else if (custMenu == 4) {
						// 4. Logout
						customerList.logoutCustomer(custSession);
					} else {
						// handle invalid option
						cout << "Error! Please enter a valid option!\n";
						break;
					}

				} else {
					break;
				}
			}
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
		default:
			// handle invalid option
			cout << "Error! Please enter a valid option!\n";
		}
	}

	*/

	return 0;
}