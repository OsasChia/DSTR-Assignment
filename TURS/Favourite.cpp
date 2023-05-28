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

		if (current == NULL) {
			cout << "List is empty! " << endl << endl;
		} 

		while (current != NULL) {
			if (current->custEmail == custEmail) {
				cout << "Favourite ID: " << current->favID << endl;
				cout << "Customer Email: " << current->custEmail << endl;
				cout << "University ID: " << current->universityID << endl  << endl;	
			}
			current = current->nextAddress;
		}

		cout << "End of the list! " << endl << endl;
	};

	bool favouriteExists(FavouriteList& favouriteList, string custEmail) {
		if (favouriteList.head != NULL) {
			DisplayAllFavInfo(favouriteList.head, custEmail);
		} else {
			cout << "No favourite university yet." << endl << endl;
			return true;
		}
	}

	bool deleteFav(FavouriteList& favouriteList, string email, string uniID) {
		// check if list is empty
		if (favouriteList.head == NULL) {
			cout << "List is empty!" << endl;
			return false;
		}

		// check if head node needs to be deleted
		if (favouriteList.head->custEmail == email && favouriteList.head->universityID == uniID) {
			Favourite* temp = favouriteList.head;
			favouriteList.head = favouriteList.head->nextAddress;
			delete temp;
			return true;
		}

		// find node to delete
		Favourite* current = favouriteList.head;
		while (current->nextAddress != NULL) {
			if (current->nextAddress->custEmail == email && current->nextAddress->universityID == uniID) {
				Favourite* temp = current->nextAddress;
				current->nextAddress = current->nextAddress->nextAddress;
				delete temp;
				cout << endl << "Favourite deleted successfully." << endl << endl;
				return true;
			}
			current = current->nextAddress;
		}

		// node not found
		cout << "Favourite with University ID " << uniID << " not found in list." << endl;
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

	string favIdPlusOne(string favId) {
		string stringId = favId.substr(1);
		int numberId = stoi(stringId);
		return "F" + to_string(numberId + 1);
	}

	void addFavourite(FavouriteList& favouriteList, string custEmail, string universityID) {
		// Check if the combination of custEmail and universityID already exists in the list
		Favourite* current = favouriteList.head;
		while (current != nullptr) {
			if (current->custEmail == custEmail && current->universityID == universityID) {
				cout << "Favorite already exists." << endl << endl;
				cout << "Favourite ID: " << current->favID << endl;
				cout << "Customer Email: " << current->custEmail << endl;
				cout << "University ID: " << current->universityID << endl << endl;
				return; // Exit the function if the favorite already exists
			}
			current = current->nextAddress;
		}

		// Generate a new favID
		string favID = favIdPlusOne(favouriteList.tail->favID);

		// Add the new favorite to the end of the list
		favouriteList.InsertToEndList(favID, custEmail, universityID);
		cout << "Favorite saved successfully." << endl << endl;
	}


	bool SearchFavByID(FavouriteList& favouriteList, string searchQuery) {
		if (favouriteList.head == NULL) {
			cout << "No Favourite Found" << endl << endl;
		} else {
			Favourite* current = favouriteList.head;
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
	void countFavorites(FavouriteList& favouriteList) {
		Favourite* current = favouriteList.head;

		// Create a doubly linked list to store the top 10 favorites
		const int MAX_COUNTS = 10; // Top 10 favorites
		Favourite* topFavorites[MAX_COUNTS] = {nullptr};
		int counts[MAX_COUNTS] = {0}; // Initialize all counts to 0

		// Traverse the linked list and update the counts array
		while (current != nullptr) {
			string universityID = current->universityID;

			// Check if the university ID is already in the doubly linked list
			int index = -1;
			for (int i = 0; i < MAX_COUNTS; i++) {
				if (topFavorites[i] != nullptr && topFavorites[i]->universityID == universityID) {
					index = i;
					break;
				}
			}

			if (index == -1) {
				// University ID is not in the doubly linked list, check if it has a higher count than the current lowest count
				int lowestCountIndex = 0;
				for (int i = 1; i < MAX_COUNTS; i++) {
					if (counts[i] < counts[lowestCountIndex]) {
						lowestCountIndex = i;
					}
				}

				if (counts[lowestCountIndex] == 0) {
					// If the current lowest count is 0, replace it with the new university ID
					Favourite* newNode = new Favourite;
					newNode->universityID = universityID;
					topFavorites[lowestCountIndex] = newNode;
					counts[lowestCountIndex]++;
				}
			} else {
				// University ID is already in the doubly linked list, increment its count
				counts[index]++;
			}

			// Move to the next node
			current = current->nextAddress;
		}

		// Print the count for each university ID
		for (int i = 0; i < MAX_COUNTS; i++) {
			if (topFavorites[i] != nullptr) {
				cout << topFavorites[i]->universityID << ": " << counts[i] << endl;
				delete topFavorites[i]; // Free the memory allocated for the node
			}
		}
	}
};