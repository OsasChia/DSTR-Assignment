#include <fstream>
#include <iostream>
#include <string>
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
	// Methods
	Feedback* CreateNewNode(string feedbackID, string custEmail, string universityID, string feedback, string reply) {
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

	void InsertToEndList(string feedbackID, string custEmail, string universityID, string feedback, string reply) {
		// call the create function to build a new single node first
		Feedback* newnode = CreateNewNode(feedbackID, custEmail, universityID, feedback, reply);

		// attach your node to the end of the list
		if (head == NULL) // list is the empty, always the newnode will be first node in list
		{
			head = tail = newnode;
		} else // if not empty list, just bring to the end of the list.
		{
			newnode->prevAddress = tail;
			tail->nextAddress = newnode;
			tail = newnode;
		}
	}

	void DisplayAllPendingFeedbackInfo() {
		Feedback* current = head;

		bool existPending; 

		while (current != NULL) // means still not the end of the list
		{
			if (current->reply == "pending") {
				cout << "Favourtie ID: " << current->feedbackID << endl;
				cout << "Customer Email: " << current->custEmail << endl;
				cout << "University ID: " << current->universityID << endl;
				cout << "Feedback: " << current->feedback << endl;
				cout << "Reply: " << current->reply << endl << endl;
				current = current->nextAddress; // if you forgot this, will become a infinity loop
			}
		}
		cout << "List is ended here! " << endl;
	}

	void DisplayUniFeedbackInfo(string universityID) {
		Feedback* current = head;

		while (current != NULL) // means still not the end of the list
		{
			if (current->universityID == universityID) {
				cout << "Favourtie ID: " << current->feedbackID << endl;
				cout << "Customer Email: " << current->custEmail << endl;
				cout << "University ID: " << current->universityID << endl;
				cout << "Feedback: " << current->feedback << endl;
				cout << "Reply: " << current->reply << endl << endl;
				current = current->nextAddress; // if you forgot this, will become a infinity loop
			}
		}
		cout << "List is ended here! " << endl;
	}

	void DisplaySingleFeedbackInfo(string feedbackID) {
		Feedback* current = head;

		while (current != NULL) // means still not the end of the list
		{
			if (current->feedbackID == feedbackID) {
				cout << "Favourtie ID: " << current->feedbackID << endl;
				cout << "Customer Email: " << current->custEmail << endl;
				cout << "University ID: " << current->universityID << endl;
				cout << "Feedback: " << current->feedback << endl;
				cout << "Reply: " << current->reply << endl << endl;
				current = current->nextAddress; // if you forgot this, will become a infinity loop
			}
		}
		cout << "List is ended here! " << endl;
	}

	FeedbackList importFeedback() {
		FeedbackList feedbackList;
		string file_feedbackID;
		string file_custEmail;
		string file_universityID;
		string file_feedback;
		string file_reply;

		ifstream file("Feedback.csv");
		// skip the first line
		string str;
		getline(file, str);
		str.clear();
		while (file.good()) {
			getline(file, file_feedbackID, ',');
			getline(file, file_custEmail, ',');
			getline(file, file_universityID, ',');
			getline(file, file_feedback, ',');
			getline(file, file_reply);
			if (file_feedbackID == "feedbackID") {
				continue;
			} else if (file_feedbackID == "") {
				break;
			}
			feedbackList.InsertToEndList(file_feedbackID, file_custEmail, file_universityID, file_feedback, file_reply);
		}
		return feedbackList;
	}

	void exportFeedback(FeedbackList feedbackList) {
		ofstream ExportFeedbackFile;
		ExportFeedbackFile.open("Feedback.csv");
		Feedback* head = feedbackList.head;
		if (head == NULL) {
			return;
		}
		ExportFeedbackFile << "feedbackID,custEmail,universityID,feedback,reply" << endl;

		Feedback* current = head;

		while (current != NULL) {
			ExportFeedbackFile << current->feedbackID << "," << current->custEmail << "," << current->universityID << ","
												 << current->feedback << "," << current->reply << endl;

			current = current->nextAddress;
		}
		ExportFeedbackFile.close();
	}

	void addFeedback(string custEmail,string universityID,string feedback) {
		string feedbackID;

		FeedbackList feedbackList = importFeedback();

		int tail = stoi(feedbackList.tail->feedbackID);

		feedbackID = to_string(tail + 1);

		feedbackList.InsertToEndList(feedbackID, custEmail, universityID, feedback, "pending");
		exportFeedback(feedbackList);
	}

	void ReplyFeedback(string feedbackID, string reply) {
		FeedbackList feedbackList = importFeedback();

		if (feedbackList.head == NULL) {
			return;
		}

		Feedback* current = feedbackList.head;

		while (current != NULL) {
			if (current->feedbackID == feedbackID) {
				current->reply = reply;
			}
			current = current->nextAddress;
		}

		exportFeedback(feedbackList);
	}

	bool ExistFeedback(string feedbackID) {
		FeedbackList feedbackList = importFeedback();

		if (feedbackList.head == NULL) {
			return false;
		}

		Feedback* current = feedbackList.head;

		while (current != NULL) {
			if (current->feedbackID == feedbackID) {
				return true;
			}
			current = current->nextAddress;
		}
	}

};