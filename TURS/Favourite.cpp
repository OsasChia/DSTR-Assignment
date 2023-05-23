#include <fstream>
#include <iostream>
#include <string>
// #include "TURS.h"

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
	Favourite* CreateNewNode(string favID, string custEmail, string universityID);
	void InsertToEndList(string favID, string custEmail, string universityID);
	void DisplayAllFavInfo();
	bool DeleteFav(string fav);
};

Favourite* FavouriteList::CreateNewNode(string favID, string custEmail, string universityID) {
	// create a empty new node first
	Favourite* newnode = new Favourite;
	newnode->favID = favID;
	newnode->custEmail = custEmail;
	newnode->universityID = universityID;
	newnode->nextAddress = NULL;

	// newnode address
	return newnode;
}

void FavouriteList::InsertToEndList(string favID, string custEmail, string universityID) {
	// call the create function to build a new single node first
	Favourite* newnode = CreateNewNode(favID, custEmail, universityID);

	// attach your node to the end of the list
	if (head == NULL) // list is the empty, always the newnode will be first node in list
	{
		head = newnode;
	} else // if not empty list, just bring to the end of the list.
	{
		Favourite* current = head; // to help us find the last item in the list

		while (current->nextAddress != NULL) // if not yet last node, move to next point again
		{
			current = current->nextAddress; // Big O - O(n)
		}

		// if found the last node, attach the new node after the last node
		current->nextAddress = newnode;
	}
}

// additional feature
void FavouriteList::DisplayAllFavInfo() // Big O - O(n)
{
	Favourite* current = head;

	while (current != NULL) // means still not the end of the list
	{
		cout << "Favourtie ID: " << current->favID << endl;
		cout << "Customer Email: " << current->custEmail << endl;
		cout << "University ID: " << current->universityID << endl << endl;
		current = current->nextAddress; // if you forgot this, will become a infinity loop
	}
	cout << "List is ended here! " << endl;
}

// additional feature
bool FavouriteList::DeleteFav(string fav) {
	// check if list is empty
	if (head == NULL) {
		cout << "List is empty!" << endl;
		return false;
	}

	// check if head node needs to be deleted
	if (head->favID == fav) {
		Favourite* temp = head;
		head = head->nextAddress;
		delete temp;
		return true;
	}

	// find node to delete
	Favourite* current = head->nextAddress;
	Favourite* prev = head;
	while (current != NULL) {
		if (current->favID == fav) {
			prev->nextAddress = current->nextAddress;
			delete current;
			return true;
		}
		prev = current;
		current = current->nextAddress;
	}

	// node not found
	cout << "Favourite ID with " << fav << " not found in list." << endl;
	return false;
}