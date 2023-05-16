#include <fstream>
#include <iostream>
#include <string>

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
	University*
	CreateNewNode(string universityID, string ranking, string universityName, string locationCode, string location) {
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

	void
	InsertToEndList(string universityID, string ranking, string universityName, string locationCode, string location) {
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

		while (current != NULL) // means still not the end of the list
		{
			cout << "University ID: " << current->universityID << endl;
			cout << "Ranking: " << current->ranking << endl;
			cout << "University Name: " << current->universityName << endl;
			cout << "Location Code: " << current->locationCode << endl;
			cout << "Location: " << current->location << endl << endl;
			current = current->nextAddress; // if you forgot this, will become a infinity loop
		}
		cout << "List is ended here! " << endl;
	}; // Big O - O(n)

	void SearchUniDetail(string universityName){};

	void importUniversity() {
		string file_universityID;
		string file_ranking;
		string file_universityName;
		string file_locationCode;
		string file_location;
		int IDcounter = 0;
		ifstream file("2023 QS World University Rankings");
		// skip the first line
		string str;
		getline(file, str);
		str.clear();
		while (file.good()) {
			file_universityID = "U" + to_string(IDcounter);
			getline(file, file_ranking, ',');
			getline(file, file_universityName, ',');
			getline(file, file_locationCode, ',');
			getline(file, file_location);
			if (file_ranking == "Rank") {
				continue;
			} else if (file_ranking == "") {
				break;
			}
			InsertToEndList(file_universityID, file_ranking, file_universityName, file_locationCode, file_location);
		}
		DisplayAllUniversityInfo();
	};

};
