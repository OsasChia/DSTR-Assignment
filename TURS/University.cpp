#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct University {
	string universityID;
	string ranking;
	string universityName;
	string locationCode;
	string location;
	University* nextAddress;
	University* prevAddress;
};

class UniversityList {
	University* head = NULL;
	University* tail = NULL;

	public:
	// Methods
	University* CreateNewNode(string universityID, string ranking, string universityName, string locationCode, string location) {
		University* newnode = new University;
		newnode->universityID = universityID;
		newnode->ranking = ranking;
		newnode->universityName = universityName;
		newnode->locationCode = locationCode;
		newnode->location = location;
		newnode->nextAddress = NULL;

		// newnode address
		return newnode;
	};

	void InsertToEndList(string universityID, string ranking, string universityName, string locationCode, string location) {
		// call the create function to build a new single node first
		University* newNode = CreateNewNode(universityID, ranking, universityName, locationCode, location);

		// attach your node to the end of the list
		if (head == NULL) // list is the empty, always the newnode will be first node in list
		{
			head = tail = newNode;
		} else // if not empty list, just bring to the end of the list.
		{
			newNode->prevAddress = tail;
			tail->nextAddress = newNode;
			tail = newNode;
		}
	};

	void DisplayAllUniversityInfo() {
		University* current = head;
		//RankingList rankingList;
		SetConsoleOutputCP(CP_UTF8);
		while (current != NULL) {
			cout << "-------University Details-------" << endl;
			cout << "University ID: " << current->universityID << endl;
			cout << "Ranking: " << current->ranking << endl;
			cout << "University Name: " << current->universityName << endl;
			cout << "Location Code: " << current->locationCode << endl;
			cout << "Location: " << current->location << endl << endl;
			cout << "-------University Ranking-------" << endl;
			//rankingList.DisplayRankingInfo(current->universityID);
			current = current->nextAddress;
		}
		cout << "List is ended here" << endl;
	}

	UniversityList importUniversity() {
		UniversityList universityList;
		string file_universityID;
		string file_ranking;
		string file_universityName;
		string file_locationCode;
		string file_location;

		int IDcounter = 1;
		ifstream file("2023 QS World University Rankings.csv");

		// skip the first line
		string str;
		getline(file, str);
		str.clear();

		while (file.good()) {
			int commaCount = 0;
			string remainingData;

			// add university ID started by U
			file_universityID = "U" + to_string(IDcounter);

			// Read the file_ranking value until a comma is encountered
			getline(file, file_ranking, ',');

			// Read the remaining data of the line into remainingData
			getline(file, remainingData);

			// Iterate over remainingData from right to left
			for (int i = remainingData.size() - 1; i >= 0; i--) {

				// Count the number of commas encountered
				if (remainingData[i] == ',') {
					commaCount++;

					// If we have encountered the 19th comma, extract the required values
					if (commaCount == 19) {
						// Extract the universityName substring
						file_universityName = remainingData.substr(0, i);
						remainingData.erase(0, file_universityName.size() + 1);

						// Extract the locationCode substring
						file_locationCode = remainingData.substr(0, remainingData.find(","));
						remainingData.erase(0, file_locationCode.size() + 1);

						//Extract the location substring
						file_location = remainingData.substr(0, remainingData.find(","));
						remainingData.erase(0, file_location.size() + 1);

						// Break if we have scanned all required substrings
						break;
					}
				}
			}

			// If the file_ranking is empty, it means we have reached the end of the file, so we break the loop
			if (file_ranking.empty()) {
				break;
			}

			// Increment the IDcounter
			IDcounter = IDcounter + 1;

			//Insert the extracted values into the UniversityList
			InsertToEndList(file_universityID, file_ranking, file_universityName, file_locationCode, file_location);
		}

		//deal with garbage data
		University* current = head;
		while (current != NULL) {
			//U198 university should be from south korea so location is KR not SK
			if (current->universityID == "U198" && current->locationCode == "SK") {
				current->locationCode = "KR";
			}
			current = current->nextAddress;
		}
		return universityList;
	};

	void SearchUniByCountry(string searchQuery) {
		if (head == NULL) {
			cout << "Empty University List" << endl << endl;
		} else {
			University* firstPtr = head;
			University* secondPtr = tail;
			bool found = false;

			while (firstPtr != NULL && secondPtr != NULL && firstPtr != secondPtr && firstPtr->prevAddress != secondPtr) {
				if (firstPtr->location.find(searchQuery) != string::npos) {
					cout << "Univerisity ID: " << firstPtr->universityID << endl;
					cout << "Univerisity Name: " << firstPtr->universityName << endl;
					cout << "Univerisity Country Code: " << firstPtr->locationCode << endl;
					cout << "Univerisity Country: " << firstPtr->location << endl << endl;

					found = true;
				}

				if (secondPtr->location.find(searchQuery) != string::npos) {
					cout << "University ID: " << secondPtr->universityID << endl;
					cout << "University Name: " << secondPtr->universityName << endl;
					cout << "University Country Code: " << secondPtr->locationCode << endl;
					cout << "University Country: " << secondPtr->location << endl << endl;

					found = true;
				}

				firstPtr = firstPtr->nextAddress;
				secondPtr = secondPtr->prevAddress;
			}

			if (
				!found && firstPtr != NULL && firstPtr == secondPtr && firstPtr->location.find(searchQuery) != string::npos) {
				cout << "University ID: " << firstPtr->universityID << endl;
				cout << "University Name: " << firstPtr->universityName << endl;
				cout << "University Country Code: " << firstPtr->locationCode << endl;
				cout << "University Country: " << firstPtr->location << endl << endl;

				found = true;
			}

			if (!found) {
				cout << "No universities found with names containing '" << searchQuery << "'." << endl << endl;
			}
		}
	};

	void SearchUniByName(string searchQuery) { 
		if (head == NULL) {
			cout << "Empty University List" << endl << endl;
		} else {
			University* firstPtr = head;
			University* secondPtr = tail;
			bool found = false;

			while (firstPtr != NULL && secondPtr != NULL && firstPtr != secondPtr && firstPtr->prevAddress != secondPtr) {
				if (firstPtr->universityName.find(searchQuery) != string::npos) {
					cout << "Univerisity ID: " << firstPtr->universityID << endl;
					cout << "Univerisity Name: " << firstPtr->universityName << endl;
					cout << "Univerisity Country Code: " << firstPtr->locationCode << endl;
					cout << "Univerisity Country: " << firstPtr->location << endl << endl;

					found = true;
				}

				if (secondPtr->universityName.find(searchQuery) != string::npos) {
					cout << "University ID: " << secondPtr->universityID << endl;
					cout << "University Name: " << secondPtr->universityName << endl;
					cout << "University Country Code: " << secondPtr->locationCode << endl;
					cout << "University Country: " << secondPtr->location << endl << endl;

					found = true;
				}

				firstPtr = firstPtr->nextAddress;
				secondPtr = secondPtr->prevAddress;
			}

			if (
				!found && firstPtr != NULL && firstPtr == secondPtr
				&& firstPtr->universityName.find(searchQuery) != string::npos) {
				cout << "University ID: " << firstPtr->universityID << endl;
				cout << "University Name: " << firstPtr->universityName << endl;
				cout << "University Country Code: " << firstPtr->locationCode << endl;
				cout << "University Country: " << firstPtr->location << endl << endl;

				found = true;
			}

			if (!found) {
				cout << "No universities found with names containing '" << searchQuery << "'." << endl << endl;
			}
		}
	}

	University* MergeSortAndDisplayUniByOption(int sortOption) {
		UniversityList universityList;
		universityList.importUniversity();
		University* sortedList = MergeSort(universityList.head, sortOption);
		universityList.head = sortedList;
		universityList.DisplayAllUniversityInfo();
		return sortedList;
	}

	University* Split(University* head) {
		University *fast = head, *slow = head;
		while (fast->nextAddress && fast->nextAddress->nextAddress) {
			fast = fast->nextAddress->nextAddress;
			slow = slow->nextAddress;
		}
		University* temp = slow->nextAddress;
		slow->nextAddress = NULL;
		return temp;
	}

	University* MergeSort(University* head, int sortOption) {
		if (!head || !head->nextAddress) return head;

		// Split the list into two halves
		University* second = Split(head);

		// Recursively sort the two halves
		head = MergeSort(head, sortOption);
		second = MergeSort(second, sortOption);

		// Merge the sorted halves based on the sort option
		switch (sortOption) {
		case 1:
			return MergeByName(head, second);
		case 2:
			return MergeByScore(head, second);
		case 3:
			return MergeByRank(head, second);
		default:
			return MergeByName(head, second); // Default to sort by name
		}
	}

	University* MergeByName(University* first, University* second) {
		if (!first) return second;
		if (!second) return first;

		if (first->universityName < second->universityName) {
			first->nextAddress = MergeByName(first->nextAddress, second);
			first->nextAddress->prevAddress = first;
			first->prevAddress = NULL;
			return first;
		} else {
			second->nextAddress = MergeByName(first, second->nextAddress);
			second->nextAddress->prevAddress = second;
			second->prevAddress = NULL;
			return second;
		}
	}

	University* MergeByScore(University* first, University* second) {
		if (!first) return second;
		if (!second) return first;

		if (stoi(first->ranking) < stoi(second->ranking)) {
			first->nextAddress = MergeByScore(first->nextAddress, second);
			first->nextAddress->prevAddress = first;
			first->prevAddress = NULL;
			return first;
		} else {
			second->nextAddress = MergeByScore(first, second->nextAddress);
			second->nextAddress->prevAddress = second;
			second->prevAddress = NULL;
			return second;
		}
	}

	University* MergeByRank(University* first, University* second) {
		if (!first) return second;
		if (!second) return first;

		if (stoi(first->ranking) < stoi(second->ranking)) {
			first->nextAddress = MergeByRank(first->nextAddress, second);
			first->nextAddress->prevAddress = first;
			first->prevAddress = NULL;
			return first;
		} else {
			second->nextAddress = MergeByRank(first, second->nextAddress);
			second->nextAddress->prevAddress = second;
			second->prevAddress = NULL;
			return second;
		}
	}



};
