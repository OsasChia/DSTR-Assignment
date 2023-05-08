#include <iostream>
#include <string>
#include <fstream>
#include "TURS.h"

using namespace std;

UniversityList::UniversityList() {}

//Methods
University* UniversityList::CreateNewNode(string universityID, string ranking, string universityName, string locationCode, string location)
{
	//create a empty new node first
	University* newnode = new University;
	newnode->universityID = universityID;
	newnode->ranking = ranking;
	newnode->universityName = universityName;
	newnode->locationCode = locationCode;
	newnode->location = location;
	newnode->nextAddress = NULL;

	//newnode address
	return newnode;
}

void UniversityList::InsertToEndList(string universityID, string ranking, string universityName, string locationCode, string location)
{
	//call the create function to build a new single node first
	University* newnode = CreateNewNode(universityID, ranking, universityName, locationCode, location);

	//attach your node to the end of the list
	if (head == NULL) //list is the empty, always the newnode will be first node in list
	{
		head = newnode;
	}
	else //if not empty list, just bring to the end of the list.
	{
		University* current = head; // to help us find the last item in the list

		while (current->nextAddress != NULL) //if not yet last node, move to next point again
		{
			current = current->nextAddress; //Big O - O(n)
		}

		//if found the last node, attach the new node after the last node
		current->nextAddress = newnode;
	}

	///////////////////////////////check what to be return///////////////////////////////////////
}

void UniversityList::DisplayAllUniversityInfo() //Big O - O(n)
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
}

void UniversityList::SearchUniDetail (string universityName){}


//int main()
//{
//	//Call object and constructor
//	UniversityList universityList;
//	//Define variable
//	string universityID, ranking, universityName, locationCode, location;
//	//input file
//	ifstream file("C://Users//cylin//Desktop//APU//APU2F2209SE//Semester 2//DSTR//Assignment//University.csv");
//	//skip the first line
//	string str;
//	getline(file, str);
//	str.clear();
//	while (file.good())
//	{
//		getline(file, universityID, ',');
//		getline(file, ranking, ',');
//		getline(file, universityName, ',');
//		getline(file, locationCode, ',');
//		getline(file, location, '\n');
//		if (universityID == "universityID")
//		{
//			continue;
//		}
//		else if (universityID == "")
//		{
//			break;
//		}
//		//InsertToTheEndOfList(string universityID, string universityName, string locationCode, string location);
//		universityList.InsertToEndList(universityID, ranking, universityName, locationCode, location);
//	}
//	file.close();
//
//	cout << "Final University List from the CSV file as below: " << endl << string(50, '=') << endl;
//	universityList.DisplayAllUniversityInfo();
//	cout << endl << string(50, '=') << endl;
//
//	return 0;
//}



