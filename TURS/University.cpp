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

		SetConsoleOutputCP(CP_UTF8);
		while (current != NULL) // means still not the end of the list
		{
			cout << "University ID: " << current->universityID << endl;
			cout << "Ranking: " << current->ranking << endl;
			cout << "University Name: " << current->universityName << endl;
			cout << "Location Code: " << current->locationCode << endl;
			cout << "Location: " << current->location << endl << endl;
			current = current->nextAddress; // if you forgot this, will become a infinity loop
		}
		cout << "List is ended ler lahhh" << endl;
	}; // Big O - O(n)

	void SearchUniDetail(string universityName){};

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
				cout << "yes";
			}
			current = current->nextAddress;
		}
		DisplayAllUniversityInfo();
		return universityList;
	};

};
