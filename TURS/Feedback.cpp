#include <fstream>
#include <iostream>
#include <string>
// #include "TURS.h"
using namespace std;

struct Feedback {
	string feedbackID;
	string custEmail;
	string universityID;
	string feedback;
	string reply;
	Feedback* nextAddress;
	Feedback* prevAddress;
};

class FeedbackList {
	Feedback* head = NULL;
	Feedback* tail = NULL;

	public:
	// Constructor
	FeedbackList();

	// Methods
	Feedback* CreateNewNode(string feedbackID, string custEmail, string universityID, string feedback, string reply);

	void InsertToEndList(string feedbackID, string custEmail, string universityID, string feedback, string reply);

	// additional feature
	void DisplayAllFeedbackInfo(); // Big O - O(n)

	// additional feature
	void ReplylFeedback(); // Big O - O(n)
};


FeedbackList::FeedbackList() {}

// Methods
Feedback*
FeedbackList::CreateNewNode(string feedbackID, string custEmail, string universityID, string feedback, string reply) {
	// create a empty new node first
	Feedback* newnode = new Feedback;
	newnode->feedbackID = feedbackID;
	newnode->custEmail = custEmail;
	newnode->universityID = universityID;
	newnode->feedback = feedback;
	newnode->reply = reply;
	newnode->nextAddress = NULL;

	// newnode address
	return newnode;
}

void FeedbackList::InsertToEndList(
	string feedbackID, string custEmail, string universityID, string feedback, string reply) {
	// call the create function to build a new single node first
	Feedback* newnode = CreateNewNode(feedbackID, custEmail, universityID, feedback, reply);

	// attach your node to the end of the list
	if (head == NULL) // list is the empty, always the newnode will be first node in list
	{
		head = newnode;
	} else // if not empty list, just bring to the end of the list.
	{
		Feedback* current = head; // to help us find the last item in the list

		while (current->nextAddress != NULL) // if not yet last node, move to next point again
		{
			current = current->nextAddress; // Big O - O(n)
		}

		// if found the last node, attach the new node after the last node
		current->nextAddress = newnode;
	}
}

// additional feature
void FeedbackList::DisplayAllFeedbackInfo() // Big O - O(n)
{
	Feedback* current = head;

	while (current != NULL) // means still not the end of the list
	{
		cout << "Favourtie ID: " << current->feedbackID << endl;
		cout << "Customer Email: " << current->custEmail << endl;
		cout << "University ID: " << current->universityID << endl;
		cout << "Feedback: " << current->feedback << endl;
		cout << "Reply: " << current->reply << endl << endl;
		current = current->nextAddress; // if you forgot this, will become a infinity loop
	}
	cout << "List is ended here! " << endl;
}

// additional feature
void FeedbackList::ReplylFeedback() // Big O - O(n)
{}


// int main()
//{
//	//Call object and constructor
//	FeedbackList feedbackList;
//	//Define variable
//	string feedbackID, custEmail, universityID, feedback, reply;
//	//input file
//	ifstream file("C://Users//cylin//Desktop//APU//APU2F2209SE//Semester 2//DSTR//Assignment//Feedback.csv");
//	//skip the first line
//	string str;
//	getline(file, str);
//	str.clear();
//	while (file.good())
//	{
//		getline(file, feedbackID, ',');
//		getline(file, custEmail, ',');
//		getline(file, universityID, ',');
//		getline(file, feedback, ',');
//		getline(file, reply, '\n');
//		if (feedbackID == "feedbackID")
//		{
//			continue;
//		}
//		else if (feedbackID == "")
//		{
//			break;
//		}
//
//		feedbackList.InsertToEndList(feedbackID, custEmail, universityID, feedback, reply);
//	}
//	file.close();
//
//	cout << "Final Feedback List from the CSV file as below: " << endl << string(50, '=') << endl;
//	feedbackList.DisplayAllFavInfo();
//	cout << endl << string(50, '=') << endl;
//
//
//	return 0;
// }
