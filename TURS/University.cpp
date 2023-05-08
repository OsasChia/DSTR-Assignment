#include <iostream>
#include <string>
#include <fstream>
// #include "TURS.h"

using namespace std;

struct University
{
	string universityID;
	string ranking;
	string universityName;
	string locationCode;
	string location;
	University* nextAddress;
	University* prevAddress;
};

class UniversityList
{
	University* head = NULL;
	University* tail = NULL;

public:
	//Constructor
	// UniversityList();

	//Methods
	University* CreateNewNode(string universityID, string ranking, string universityName, string locationCode, string location){
		University* newnode = new University;
		newnode->universityID = universityID;
		newnode->ranking = ranking;
		newnode->universityName = universityName;
		newnode->locationCode = locationCode;
		newnode->location = location;
		newnode->nextAddress = NULL;

		//newnode address
		return newnode;
	};

	void InsertToEndList(string universityID, string ranking, string universityName, string locationCode, string location)
	{
		//call the create function to build a new single node first
		University* newNode = CreateNewNode(universityID, ranking, universityName, locationCode, location);

		//attach your node to the end of the list
		if (head == NULL) //list is the empty, always the newnode will be first node in list
		{
			head = newNode;
		}
		else //if not empty list, just bring to the end of the list.
		{
			University* current = head; // to help us find the last item in the list

			while (current->nextAddress != NULL) //if not yet last node, move to next point again
			{
				current = current->nextAddress; //Big O - O(n)
			}

			//if found the last node, attach the new node after the last node
			current->nextAddress = newNode;
		};
	}

	void DisplayAllUniversityInfo()
	{
	University* current = head;

	while (current != NULL) //means still not the end of the list
	{
		cout << "University ID: " << current->universityID << endl;
		cout << "Ranking: " << current->ranking << endl;
		cout << "University Name: " << current->universityName << endl;
		cout << "Location Code: " << current->locationCode << endl;
		cout << "Location: " << current->location << endl << endl;
		current = current->nextAddress; //if you forgot this, will become a infinity loop
	}
	cout << "List is ended here! " << endl;
}; //Big O - O(n)

	void SearchUniDetail(string universityName) {};

};
