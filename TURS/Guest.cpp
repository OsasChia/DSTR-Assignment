#include <iostream>
//#include "Customer.cpp"
//#include "Ranking.cpp"
//#include "Feedback.cpp"

class Guest {
	public:
	
	/*
	void GuestMenu() {
		// 1. Display all university information
		
		// 3. Register an account
		CustomerList customerList;

		UniversityList universityList;
		universityList.importUniversity();

		int guestOption = 0;
		// register variables
		string regisEmailTxt;
		
		// Display guest menu
		cout << "1. Display all university information\n2. Search university by name\n3. Search university by country\n4. Two pointer vs binary search (Time complexity)\n5. Return to start menu\n\nSelect your option: ";
		cin >> guestOption;
		cout << endl;
		if (guestOption == 1) {
			// 1. Display all university information
			/*auto startt = high_resolution_clock::now();
			rankingList.QuickSortAndDisplayUni(1);
			auto stopp = high_resolution_clock::now();
			auto durationn = duration_cast<microseconds>(stopp - startt);
			cout << "Time taken for Quick sort: " << durationn.count() << " microseconds." << endl << endl;

			auto start = high_resolution_clock::now();
			rankingList.MergeSortAndDisplayUniByOption(1);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken for Merge sort: " << duration.count() << " microseconds." << endl;

			int currentPage = 1; // Start with the first page
			rankingList.DisplayRankingInfo(currentPage);
				
			GuestMenu();
		} else if (guestOption == 2) {
			// 2. Search university by name
			universityList.SearchUniByName();

			GuestMenu();
		} else if (guestOption == 3) {
			// 3. Search university by country
			universityList.SearchUniByCountry();

			GuestMenu();
		} else if (guestOption == 4) {
			// 4. two pointer vs binary search
			
			auto start = high_resolution_clock::now();
			universityList.SearchUniByName();
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken for search by name: " << duration.count() << " microseconds." << endl;

			auto startt = high_resolution_clock::now();
			universityList.SearchUniByCountry();
			auto stopp = high_resolution_clock::now();
			auto durationn = duration_cast<microseconds>(stopp - startt);
			cout << "Time taken for search by country: " << durationn.count() << " microseconds." << endl << endl;
			

			auto startt = high_resolution_clock::now();
			universityList.SearchUniByName();
			auto stopp = high_resolution_clock::now();
			auto durationn = duration_cast<microseconds>(stopp - startt);
			cout << "Time taken for two pointer search by name: " << durationn.count() << " microseconds." << endl << endl;

			auto start = high_resolution_clock::now();
			rankingList.binarySearchUniByName();
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken for binary search by name: " << duration.count() << " microseconds." << endl << endl;

			GuestMenu();
		} else if (guestOption == 5) {
			// 5. Return to start menu
			startMenu();
		} else {
			// handle invalid option
			cout << "Error! Please enter a valid option!\n";
			GuestMenu();
		}
	};
	*/
};
