#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

using namespace std;

struct Favourite {
	string favID;
	string custEmail;
	string universityID;
	Favourite* nextAddress;
	Favourite* prevAddress;
};
class FavouriteList {
	Favourite* head = NULL;
	Favourite* tail = NULL;

	public:
	Favourite* getHead() { return this->head; }

	Favourite* CreateNewNode(string favID, string custEmail, string universityID){
		Favourite* newnode = new Favourite;
		newnode->favID = favID;
		newnode->custEmail = custEmail;
		newnode->universityID = universityID;
		newnode->nextAddress = NULL;

		return newnode;
	};

	void InsertToEndList(string favID, string custEmail, string universityID){
		Favourite* newnode = CreateNewNode(favID, custEmail, universityID);

		if (head == NULL)
		{
			head = tail = newnode;
		} else {
			newnode->prevAddress = tail;
			tail->nextAddress = newnode;
			tail = newnode;
		}
	};

	void DisplayAllFavInfo(Favourite* temp, string custEmail){ 
		Favourite* current = temp;
		while ((current != NULL) && (current->custEmail == custEmail)) {
			cout << "Favourite ID: " << current->favID << endl;
			cout << "Customer Email: " << current->custEmail << endl;
			cout << "University ID: " << current->universityID << endl;			
			current = current->nextAddress;
		}
		if (current == NULL) {
			cout << "End of the list! " << endl << endl;
		} 
	};

	bool favouriteExists(Favourite* temp, string custEmail) {
		if (temp != NULL) {
			DisplayAllFavInfo(temp, custEmail);
		} else {
			cout << "No favourite university yet." << endl << endl;
			return true;
		}
	}

	bool DeleteFav(string favID) {
		// check if list is empty
		if (head == NULL) {
			cout << "List is empty!" << endl;
			return false;
		}

		// check if head node needs to be deleted
		if (head->favID == favID) {
			Favourite* temp = head;
			head = head->nextAddress;
			delete temp;
			return true;
		}

		// find node to delete
		Favourite* current = head->nextAddress;
		Favourite* prev = head;
		while (current != NULL && current->favID == favID) {
			prev->nextAddress = current->nextAddress;
			delete current;
			return true;
			prev = current;
			current = current->nextAddress;
		}

		// node not found
		cout << "Favourite ID with " << favID << " not found in list." << endl;
		return false;
	}

	FavouriteList importFavourite() {
		FavouriteList favouriteList;
		string file_favID;
		string file_custEmail;
		string file_universityID;

		ifstream file("Favourite.csv");
		// skip the first line
		string str;
		getline(file, str);
		str.clear();

		while (file.good()) {
			string rowData;
			getline(file, rowData);
			stringstream iss(rowData);
			string token;
			getline(iss, token, ',');
			file_favID = token;

			getline(iss, token, ',');
			file_custEmail = token;

			getline(iss, token, ',');
			file_universityID = token;

			if (file_favID.empty()) {
				break;
			}
			favouriteList.InsertToEndList(file_favID, file_custEmail, file_universityID);
		}
		return favouriteList;
	}

	void exportFavourite(FavouriteList favouriteList) {
		ofstream ExportFavouriteFile;
		ExportFavouriteFile.open("Favourite.csv");
		Favourite* head = favouriteList.head;
		if (head == NULL) {
			return;
		}
		ExportFavouriteFile << "favID,custEmail,universityID" << endl;

		Favourite* current = head;

		while (current != NULL) {
			ExportFavouriteFile << current->favID << "," << current->custEmail << "," << current->universityID << endl;

			current = current->nextAddress;
		}
		ExportFavouriteFile.close();
	}

	void addFavourite(FavouriteList& favouriteList, string custEmail, string universityID) {
		string favID;
		int tail = stoi(favouriteList.tail->favID);
		favID = to_string(tail + 1);

		favouriteList.InsertToEndList(favID, custEmail, universityID);
		exportFavourite(favouriteList);
		cout << "Favourite saved successfully." << endl << endl;
	}

	bool SearchFavByID(string searchQuery) {
		if (head == NULL) {
			cout << "No Favourite Found" << endl << endl;
		} else {
			Favourite* current = head;
			bool found = false;

			while (current != NULL) {
				if (current->favID == searchQuery) {
					cout << "Feedback ID: " << current->favID << endl;
					cout << "Customer Email: " << current->custEmail << endl;
					cout << "University ID: " << current->universityID << endl << endl;

					found = true;
					break;
				}

				current = current->nextAddress;
			}

			if (!found) {
				cout << "No feedback found with ID: '" << searchQuery << "'." << endl << endl;
			}
			return found;
		}
	}
};