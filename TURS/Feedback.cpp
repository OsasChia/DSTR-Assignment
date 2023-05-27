#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

using namespace std;

struct Feedback {
	string feedbackID;
	string custEmail;
	string universityID;
	string feedback;
	string feedbackDate;
	string reply;
	string replyDate;
	Feedback* nextAddress;
	Feedback* prevAddress;
};

class FeedbackList {
	Feedback* head = NULL;
	Feedback* tail = NULL;

	public:
	Feedback* getHead() { return this->head; }

	// Methods
	Feedback* CreateNewNode(string feedbackID, string custEmail, string universityID, string feedback, string feedbackDate, string reply, string replyDate) {
		// create a empty new node first
		Feedback* newnode = new Feedback;
		newnode->feedbackID = feedbackID;
		newnode->custEmail = custEmail;
		newnode->universityID = universityID;
		newnode->feedback = feedback;
		newnode->feedbackDate = feedbackDate;
		newnode->reply = reply;
		newnode->replyDate = replyDate;
		newnode->nextAddress = NULL;

		// newnode address
		return newnode;
	}

	void InsertToFrontList(string feedbackID, string custEmail, string universityID, string feedback, string feedbackDate, string reply, string replyDate) {
		// call the create function to build a new single node first
		Feedback* newnode = CreateNewNode(feedbackID, custEmail, universityID, feedback, feedbackDate, reply, replyDate);

		// attach your node to the end of the list
		if (head == NULL) // list is the empty, always the newnode will be first node in list
		{
			head = tail = newnode;
		} else // if not empty list, just bring to the end of the list.
		{
			newnode->nextAddress = head;
			head->prevAddress = newnode;
			head = newnode;
		}
	}

	void InsertToEndList(
		string feedbackID,
		string custEmail,
		string universityID,
		string feedback,
		string feedbackDate,
		string reply,
		string replyDate) {
		// call the create function to build a new single node first
		Feedback* newnode = CreateNewNode(feedbackID, custEmail, universityID, feedback, feedbackDate, reply, replyDate);

		// attach your node to the end of the list
		if (head == NULL) // list is the empty, always the newnode will be first node in list
		{
			head = tail = newnode;
		} else // if not empty list, just bring to the end of the list.
		{
			newnode->prevAddress = tail;
			tail->nextAddress = newnode;
			tail = newnode;
			// cout << tail->feedback;
		}
	}

	void DisplayAllFeedbackInfo(int currentPage, Feedback* temp) {
		Feedback* current = temp;
		int pageSize = 1;
		int startIndex = (currentPage - 1) * pageSize;
		int endIndex = startIndex + pageSize;
		int count = 0;
		while (current != NULL && count < endIndex) {
			if (count >= startIndex) {
				cout << "Favourtie ID: " << current->feedbackID << endl;
				cout << "Customer Email: " << current->custEmail << endl;
				cout << "University ID: " << current->universityID << endl;
				cout << "Feedback: " << current->feedback << endl;
				cout << "Feedback Date: " << current->feedbackDate << endl;
				cout << "Reply: " << current->reply << endl;
				cout << "Reply Date: " << current->replyDate << endl << endl;
			}
			current = current->nextAddress;
			count++;
		}
		if (current == NULL) {
			cout << "End of the list! " << endl << endl;
		} else {
			cout << "1. Next result" << endl;
			cout << "2. Previous result" << endl;
			cout << "3. Choose a feedback to be replied" << endl << endl;
			cout << "Choose an option:";

			int option;
			cin >> option;
			cout << endl;

			switch (option) {
			case 1:
				DisplayAllFeedbackInfo(currentPage + 1, temp);
				break;
			case 2:
				if (currentPage > 1) {
					DisplayAllFeedbackInfo(currentPage - 1, temp);
				} else {
					DisplayAllFeedbackInfo(currentPage, temp);
				}
				break;
			case 3:
				return;
			default:
				cout << "Invalid choice. Exiting..." << endl << endl;
			}
		}
	}

	bool feedbackExists(Feedback* temp) { 
		if (temp != NULL) {
			DisplayAllFeedbackInfo(1, temp);
		} else {
			cout << "No feedback yet." << endl << endl;
			return true;
		}
	}

	Feedback* Split(Feedback* head) {
		Feedback* fast = head;
		Feedback* slow = head;
		while (fast && fast->nextAddress && fast->nextAddress->nextAddress) {
			slow = slow->nextAddress;
			fast = fast->nextAddress->nextAddress;
		}
		return slow;
	}

	Feedback* MergeByReplyDate(Feedback* first, Feedback* second) {
		if (!first) return second;
		if (!second) return first;

		Feedback* result = nullptr;

		if (first->replyDate < second->replyDate) {
			result = first;
			result->nextAddress = MergeByReplyDate(first->nextAddress, second);
			result->nextAddress->prevAddress = result;
		} else {
			result = second;
			result->nextAddress = MergeByReplyDate(first, second->nextAddress);
			result->nextAddress->prevAddress = result;
		}
		return result;
	}

	Feedback* mergeSortReply(Feedback* head) {
		if (!head || !head->nextAddress) {
			return head;
		}

		Feedback* middle = Split(head);
		Feedback* nextToMiddle = middle->nextAddress;

		middle->nextAddress = nullptr;
		nextToMiddle->prevAddress = nullptr;

		Feedback* left = mergeSortReply(head);
		Feedback* right = mergeSortReply(nextToMiddle);

		return MergeByReplyDate(left, right);
	}

	Feedback* displayByReplyDate(Feedback* temp) {
		Feedback* sortedList = mergeSortReply(temp);
		temp = sortedList;
		DisplayAllFeedbackInfo(1, temp);
		return sortedList;
	}

	//void DisplayUniFeedbackInfo(string universityID) {
	//	Feedback* current = head;

	//	while (current != NULL) // means still not the end of the list
	//	{
	//		if (current->universityID == universityID) {
	//			cout << "Favourtie ID: " << current->feedbackID << endl;
	//			cout << "Customer Email: " << current->custEmail << endl;
	//			cout << "University ID: " << current->universityID << endl;
	//			cout << "Feedback: " << current->feedback << endl;
	//			cout << "Feedback Date: " << current->feedbackDate << endl;
	//			cout << "Reply: " << current->reply << endl;
	//			cout << "Reply Date: " << current->replyDate << endl << endl;
	//			current = current->nextAddress; // if you forgot this, will become a infinity loop
	//		}
	//	}
	//	cout << "List is ended here! " << endl;
	//}

	//void DisplaySingleFeedbackInfo(string feedbackID) {
	//	Feedback* current = head;

	//	while (current != NULL) // means still not the end of the list
	//	{
	//		if (current->feedbackID == feedbackID) {
	//			cout << "Favourtie ID: " << current->feedbackID << endl;
	//			cout << "Customer Email: " << current->custEmail << endl;
	//			cout << "University ID: " << current->universityID << endl;
	//			cout << "Feedback: " << current->feedback << endl;
	//			cout << "Feedback Date: " << current->feedbackDate << endl;
	//			cout << "Reply: " << current->reply << endl;
	//			cout << "Reply Date: " << current->replyDate << endl << endl;
	//			current = current->nextAddress; // if you forgot this, will become a infinity loop
	//		}
	//	}
	//	cout << "List is ended here! " << endl;
	//}

	FeedbackList importFeedback() {
		FeedbackList feedbackList;
		string file_feedbackID;
		string file_custEmail;
		string file_universityID;
		string file_feedback;
		string file_feedbackDate;
		string file_reply;
		string file_replyDate;

		ifstream file("Feedback.csv");
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
			file_feedbackID = token;

			getline(iss, token, ',');
			file_custEmail = token;

			getline(iss, token, ',');
			file_universityID = token;

			getline(iss, token, ',');
			file_feedback = token;

			getline(iss, token, ',');
			file_feedbackDate = token;

			getline(iss, token, ',');
			file_reply = token;

			getline(iss, token, ',');
			file_replyDate = token;

			if (file_feedbackID.empty()) {
				break;
			}
			feedbackList.InsertToEndList(file_feedbackID, file_custEmail, file_universityID, file_feedback, 
				file_feedbackDate, file_reply, file_replyDate);
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
		ExportFeedbackFile << "feedbackID,custEmail,universityID,feedback,feedbackDate,reply,replyDate" << endl;

		Feedback* current = head;

		while (current != NULL) {
			ExportFeedbackFile << current->feedbackID << "," << current->custEmail << "," << current->universityID << ","
												 << current->feedback << "," << current->feedbackDate << "," << current->reply << ","
												 << current->replyDate << endl;

			current = current->nextAddress;
		}
		ExportFeedbackFile.close();
	}

	void addFeedback(FeedbackList& feedbackList, string custEmail, string universityID, string feedback, string feedbackDate) {
		string feedbackID;
		int head = stoi(feedbackList.head->feedbackID);
		feedbackID = to_string(head + 1);

		feedbackList.InsertToFrontList(feedbackID, custEmail, universityID, feedback, feedbackDate, "pending", feedbackDate);
		exportFeedback(feedbackList);
		cout << "Feedback added successfully." << endl << endl;
	}

	void ReplyFeedback(FeedbackList& feedbackList, string feedbackID, string reply, string replyDate) {

		if (feedbackList.head == NULL) {
			return;
		}

		Feedback* current = feedbackList.head;

		while (current != NULL) {
			if (current->feedbackID == feedbackID) {
				current->reply = reply;
				current->replyDate = replyDate;
			}
			current = current->nextAddress;
		}

		exportFeedback(feedbackList);
		cout << "Replied successfully." << endl << endl;
	}

	bool SearchFeedbackByID(FeedbackList& feedbackListHead, string searchQuery) {
		if (feedbackListHead.head == NULL) {
			cout << "No Feedback Found" << endl << endl;
		} else {
			Feedback* current = feedbackListHead.head;
			bool found = false;

			while (current != NULL) {
				if (current->feedbackID == searchQuery) {
					cout << "Feedback ID: " << current->feedbackID << endl;
					cout << "Customer Email: " << current->custEmail << endl;
					cout << "University ID: " << current->universityID << endl;
					cout << "Feedback: " << current->feedback << endl;
					cout << "Feedback Date: " << current->feedbackDate << endl;
					cout << "Reply: " << current->reply << endl;
					cout << "Reply Date: " << current->replyDate << endl << endl;

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

	/*bool ExistFeedback(string feedbackID) {
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
	}*/
};