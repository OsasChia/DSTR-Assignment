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
	string universityName;

	Favourite* nextAddress;
	Favourite* prevAddress;
};

struct CountNode {
	string universityID;
	string universityName;
	int count;

	CountNode* nextAddress;
};

class FavouriteList {
	Favourite* head = NULL;
	Favourite* tail = NULL;

	public:

	Favourite* CreateNewNode(string favID, string custEmail, string universityID, string universityName) {
		Favourite* newnode = new Favourite;
		newnode->favID = favID;
		newnode->custEmail = custEmail;
		newnode->universityID = universityID;
		newnode->universityName = universityName;
		newnode->nextAddress = NULL;

		return newnode;
	};

	void InsertToEndList(string favID, string custEmail, string universityID, string universityName) {
		Favourite* newnode = CreateNewNode(favID, custEmail, universityID, universityName);

		if (head == NULL)
		{
			head = tail = newnode;
		} else {
			newnode->prevAddress = tail;
			tail->nextAddress = newnode;
			tail = newnode;
		}
	};

	void DisplayAllFavInfo(Favourite* temp){ 
		Favourite* current = temp;

		if (current == NULL) {
			cout << "List is empty." << endl << endl;
			return;
		}

		while (current != NULL) {
			cout << "Favourite ID: " << current->favID << endl;
			cout << "Customer Email: " << current->custEmail << endl;
			cout << "University ID: " << current->universityID << endl;
			cout << "University Name: " << current->universityName << endl << endl;
			current = current->nextAddress;
		}
		
		cout << "End of the list! " << endl << endl;

	};

	bool favouriteExists(FavouriteList& favouriteList, string custEmail) {
		if (favouriteList.head != NULL) {
			displayFavByCustEmail(favouriteList, custEmail);
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
		cout << "Favourite with University ID " << uniID << " not found in list." << endl << endl;
		return false;
	}

	Favourite* SplitFav(Favourite* temp) {
		Favourite* fast = temp;
		Favourite* slow = temp;
		while (fast && fast->nextAddress && fast->nextAddress->nextAddress) {
			slow = slow->nextAddress;
			fast = fast->nextAddress->nextAddress;
		}
		return slow;
	}

	Favourite* MergeByFavID(Favourite* first, Favourite* second) {
		if (!first) return second;
		if (!second) return first;

		Favourite* result = nullptr;

		if (first->favID > second->favID) {
			result = first;
			result->nextAddress = MergeByFavID(first->nextAddress, second);
			result->nextAddress->prevAddress = result;
		} else if (first->favID < second->favID) {
			result = second;
			result->nextAddress = MergeByFavID(first, second->nextAddress);
			result->nextAddress->prevAddress = result;
		}
		return result;
	}

	Favourite* mergeSort(Favourite* temp, string custEmail) {
		// Filter out nodes with non-matching custEmail
		Favourite* filteredList = nullptr;
		Favourite* current = temp;
		while (current != nullptr) {
			if (current->custEmail == custEmail) {
				Favourite* newNode = new Favourite(*current);
				newNode->nextAddress = filteredList;
				if (filteredList != nullptr) {
					filteredList->prevAddress = newNode;
				}
				filteredList = newNode;
			}
			current = current->nextAddress;
		}

		// Perform merge sort on the filtered list
		if (!filteredList || !filteredList->nextAddress) {
			return filteredList;
		}

		Favourite* middle = SplitFav(filteredList);
		Favourite* nextToMiddle = middle->nextAddress;

		middle->nextAddress = nullptr;
		nextToMiddle->prevAddress = nullptr;

		Favourite* left = mergeSort(filteredList, custEmail);
		Favourite* right = mergeSort(nextToMiddle, custEmail);

		return MergeByFavID(left, right);
	}

	Favourite* displayFavByCustEmail(FavouriteList& favouriteList, string custEmail) {
		Favourite* sortedList = mergeSort(favouriteList.head, custEmail);
		DisplayAllFavInfo(sortedList);
		return favouriteList.head;
	}

	FavouriteList importFavourite() {
		FavouriteList favouriteList;
		string file_favID;
		string file_custEmail;
		string file_universityID;
		string file_universityName;

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

			getline(iss, token, ',');
			file_universityName = token;

			if (file_favID.empty()) {
				break;
			}
			favouriteList.InsertToEndList(file_favID, file_custEmail, file_universityID, file_universityName);
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
		ExportFavouriteFile << "favID,custEmail,universityID,universityName" << endl;

		Favourite* current = head;

		while (current != NULL) {
			ExportFavouriteFile << current->favID << "," << current->custEmail << "," << current->universityID << "," << current->universityName << endl;

			current = current->nextAddress;
		}
		ExportFavouriteFile.close();
	}

	string favIdPlusOne(string favId) {
		string stringId = favId.substr(1);
		int numberId = stoi(stringId);
		return "F" + to_string(numberId + 1);
	}

	void addFavourite(FavouriteList& favouriteList, string custEmail, string universityID, string universityName) {
		// Check if the combination of custEmail and universityID already exists in the list
		Favourite* current = favouriteList.head;
		while (current != nullptr) {
			if (current->custEmail == custEmail && current->universityID == universityID) {
				cout << "Favorite already exists." << endl << endl;
				cout << "Favourite ID: " << current->favID << endl;
				cout << "Customer Email: " << current->custEmail << endl;
				cout << "University ID: " << current->universityID << endl;
				cout << "University Name: " << current->universityName << endl << endl;
				return; // Exit the function if the favorite already exists
			}
			current = current->nextAddress;
		}

		// Generate a new favID
		string favID = favIdPlusOne(favouriteList.tail->favID);

		// Add the new favorite to the end of the list
		favouriteList.InsertToEndList(favID, custEmail, universityID, universityName);
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
					cout << "Favourite ID: " << current->favID << endl;
					cout << "Customer Email: " << current->custEmail << endl;
					cout << "University ID: " << current->universityID << endl;
					cout << "University Name: " << current->universityName << endl << endl;

					found = true;
					break;
				}

				current = current->nextAddress;
			}

			if (!found) {
				cout << "No favourite found with ID: '" << searchQuery << "'." << endl << endl;
			}
			return found;
		}
	}

	void countTopTenFavorites(FavouriteList& favouriteList) {
		if (favouriteList.head == NULL) {
			cout << "No favorites found." << endl;
			return;
		}

		CountNode* countHead = NULL;

		Favourite* current = favouriteList.head;
		while (current != NULL) {
			string universityID = current->universityID;
			string universityName = current->universityName;

			// Check if the university ID already exists in the count list
			CountNode* countCurrent = countHead;
			CountNode* prev = NULL;
			bool found = false;

			while (countCurrent != NULL) {
				if (countCurrent->universityID == universityID) {
					countCurrent->count++;
					found = true;
					break;
				}
				prev = countCurrent;
				countCurrent = countCurrent->nextAddress;
			}

			// If the university ID does not exist, add it to the count list
			if (!found) {
				CountNode* newNode = new CountNode;
				newNode->universityID = universityID;
				newNode->universityName = universityName;
				newNode->count = 1;
				newNode->nextAddress = NULL;

				if (countHead == NULL) {
					countHead = newNode;
				} else {
					prev->nextAddress = newNode;
				}
			}

			current = current->nextAddress;
		}

		// Sort the count list in descending order based on counts
		bool sorted = false;
		while (!sorted) {
			sorted = true;
			CountNode* current = countHead;
			CountNode* prev = NULL;

			while (current != NULL && current->nextAddress != NULL) {
				if (current->count < current->nextAddress->count) {
					sorted = false;
					CountNode* temp = current->nextAddress;
					current->nextAddress = current->nextAddress->nextAddress;
					temp->nextAddress = current;

					if (prev != NULL) {
						prev->nextAddress = temp;
					} else {
						countHead = temp;
					}
					prev = temp;
				} else {
					prev = current;
					current = current->nextAddress;
				}
			}
		}

		// Display the counts in descending order
		cout << "Top 10 Favourite Universities Most Preferred By Parents in Malaysia:" << endl;
		CountNode* temp = countHead;
		int count = 1;

		while (temp != NULL && count <= 10) {
			cout << count << ". University ID: " << temp->universityID << endl;
			cout << "University Name: " << temp->universityName << endl;
			cout << "Favourite Count: " << temp->count << endl << endl;
			temp = temp->nextAddress;
			count++;
		}

		// Clean up memory (don't forget to deallocate the memory)
		while (countHead != NULL) {
			CountNode* temp = countHead;
			countHead = countHead->nextAddress;
			delete temp;
		}

		cout << endl;
	}
};