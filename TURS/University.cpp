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
			head = newNode;
		} else // if not empty list, just bring to the end of the list.
		{
			University* current = head; // to help us find the last item in the list

			while (current->nextAddress != NULL) // if not yet last node, move to next point again
			{
				current = current->nextAddress; // Big O - O(n)
			}

			// if found the last node, attach the new node after the last node
			current->nextAddress = newNode;
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

	void importUniversity() {
		string file_universityID;
		string file_ranking;
		string file_universityName;
		string file_locationCode;
		string file_location;
		string file_ignoreRanking;

		int IDcounter = 1;
		ifstream file("2023 QS World University Rankings.csv");

		// skip the first line
		string str;
		getline(file, str);
		str.clear();

		while (file.good()) {
			file_universityID = "U" + to_string(IDcounter);
			getline(file, file_ranking, ',');

			if (file.peek() == '"') {
				getline(file, file_universityName, '\"'); // Read until the closing quotation mark
				getline(file, file_universityName, ',');	// Read until the comma after the quotation mark
			} else {
				getline(file, file_universityName, ','); // Read normally until the comma
			}

			getline(file, file_locationCode, ',');
			getline(file, file_location, ',');
			getline(file, file_ignoreRanking);

			if (file_ranking == "Rank") {
				continue;
			} else if (file_ranking == "") {
				break;
			}

			IDcounter = IDcounter + 1;
			InsertToEndList(file_universityID, file_ranking, file_universityName, file_locationCode, file_location);
		}
		DisplayAllUniversityInfo();
	};


	void importUniversity2() {
		string file_universityID;
		string file_ranking;
		string file_universityName;
		string file_locationCode;
		string file_location;
		string file_ignoreRanking;

		int IDcounter = 1;
		ifstream file("2023 QS World University Rankings.csv");

		// skip the first line
		string str;
		getline(file, str);
		str.clear();

		while (file.good()) {
			int commaCount = 0;
			string remainingData;

			file_universityID = "U" + to_string(IDcounter);

			getline(file, file_ranking, ',');

			// errr ask me bah idk how to explain XDDD
			getline(file, remainingData);
			for (int i = remainingData.size() - 1; i >= 0; i--) {
				if (remainingData[i] == ',') {
					commaCount++;

					if (commaCount == 19) {
						file_universityName = remainingData.substr(0, i);
						remainingData.erase(0, file_universityName.size() + 1);

						file_locationCode = remainingData.substr(0, remainingData.find(","));
						remainingData.erase(0, file_locationCode.size() + 1);

						file_location = remainingData.substr(0, remainingData.find(","));
						remainingData.erase(0, file_location.size() + 1);

						// Break if we have scanned all required substrings
						break;
					}
				}
			}

			if (file_ranking.empty()) {
				break;
			}

			IDcounter = IDcounter + 1;
			InsertToEndList(file_universityID, file_ranking, file_universityName, file_locationCode, file_location);
		}
		DisplayAllUniversityInfo();
	};

};
