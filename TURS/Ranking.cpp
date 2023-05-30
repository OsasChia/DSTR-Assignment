#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <cctype>

using namespace std;

struct Ranking {
	string universityID;
	string ranking;
	string universityName;
	string locationCode;
	string location;
	string ArScore;
	string ArRank;
	string ErScore;
	string ErRank;
	string FsrScore;
	string FsrRank;
	string CpfScore;
	string CpfRank;
	string IfrScore;
	string IfrRank;
	string IsrScore;
	string IsrRank;
	string IrnScore;
	string IrnRank;
	string GerScore;
	string GerRank;
	string ScoreScaled;
	Ranking* nextAddress;
	Ranking* prevAddress;
};

class RankingList {
	Ranking* head = NULL;
	Ranking* tail = NULL;

	public:
	// ============================ //
	// ===== GETTER FUNCTIONS ===== //

	Ranking* getHead() { return this->head; }

	// =================================== //
	// ===== NODE CREATION FUNCTIONS ===== //

	Ranking* CreateNewNode(
		string universityID,
		string ranking,
		string universityName,
		string locationCode,
		string location,
		string ArScore,
		string ArRank,
		string ErScore,
		string ErRank,
		string FsrScore,
		string FsrRank,
		string CpfScore,
		string CpfRank,
		string IfrScore,
		string IfrRank,
		string IsrScore,
		string IsrRank,
		string IrnScore,
		string IrnRank,
		string GerScore,
		string GerRank,
		string ScoreScaled) {
		// create a empty new node first
		Ranking* newnode = new Ranking;
		newnode->universityID = universityID;
		newnode->ranking = ranking;
		newnode->universityName = universityName;
		newnode->locationCode = locationCode;
		newnode->location = location;
		newnode->ArScore = ArScore;
		newnode->ArRank = ArRank;
		newnode->ErScore = ErScore;
		newnode->ErRank = ErRank;
		newnode->FsrScore = FsrScore;
		newnode->FsrRank = FsrRank;
		newnode->CpfScore = CpfScore;
		newnode->CpfRank = CpfRank;
		newnode->IfrScore = IfrScore;
		newnode->IfrRank = IfrRank;
		newnode->IsrScore = IsrScore;
		newnode->IsrRank = IsrRank;
		newnode->IrnScore = IrnScore;
		newnode->IrnRank = IrnRank;
		newnode->GerScore = GerScore;
		newnode->GerRank = GerRank;
		newnode->ScoreScaled = ScoreScaled;
		newnode->prevAddress = NULL;
		newnode->nextAddress = NULL;

		// newnode address
		return newnode;
	}

	void InsertToEndList(
		string universityID,
		string ranking,
		string universityName,
		string locationCode,
		string location,
		string ArScore,
		string ArRank,
		string ErScore,
		string ErRank,
		string FsrScore,
		string FsrRank,
		string CpfScore,
		string CpfRank,
		string IfrScore,
		string IfrRank,
		string IsrScore,
		string IsrRank,
		string IrnScore,
		string IrnRank,
		string GerScore,
		string GerRank,
		string ScoreScaled) {
		// call the create function to build a new single node first
		Ranking* newnode = CreateNewNode(
			universityID,
			ranking,
			universityName,
			locationCode,
			location,
			ArScore,
			ArRank,
			ErScore,
			ErRank,
			FsrScore,
			FsrRank,
			CpfScore,
			CpfRank,
			IfrScore,
			IfrRank,
			IsrScore,
			IsrRank,
			IrnScore,
			IrnRank,
			GerScore,
			GerRank,
			ScoreScaled);

		// attach your node to the end of the list
		if (head == NULL) // list is the empty, always the newnode will be first node in list
		{
			newnode->prevAddress = NULL;
			head = tail = newnode;
		} else // if not empty list, just bring to the end of the list.
		{
			newnode->prevAddress = tail;
			tail->nextAddress = newnode;
			tail = newnode;
		}
	}

	// ============================================ //
	// ===== DISPLAY FUNCTION WITH PAGINATION ===== //

	void DisplayRankingInfo(RankingList& rankingList,int currentPage) {
		int pageSize = 20;
		int startIndex = (currentPage - 1) * pageSize;
		int endIndex = startIndex + pageSize;

		Ranking* current = rankingList.head;

		int count = 0;
		while (current != NULL && count < endIndex) {
			if (count >= startIndex) {
			
				cout << "-----Uni Detail-----" << endl;
				cout << "University ID: " << current->universityID << endl;
				cout << "Ranking: " << current->ranking << endl;
				cout << "University Name: " << current->universityName << endl;
				cout << "Location Code: " << current->locationCode << endl;
				cout << "Location: " << current->location << endl;
				cout << "-----Uni Score-----" << endl;
				cout << "ArScore: " << current->ArScore << endl;
				cout << "ArRank: " << current->ArRank << endl;
				cout << "ErScore: " << current->ErScore << endl;
				cout << "ErRank: " << current->ErRank << endl;
				cout << "FsrScore: " << current->FsrScore << endl;
				cout << "FsrRank: " << current->FsrRank << endl;
				cout << "CpfScore: " << current->CpfScore << endl;
				cout << "CpfRank: " << current->CpfRank << endl;
				cout << "IfrScore: " << current->IfrScore << endl;
				cout << "IfrRank: " << current->IfrRank << endl;
				cout << "IsrScore: " << current->IsrScore << endl;
				cout << "IsrRank: " << current->IsrRank << endl;
				cout << "IrnScore: " << current->IrnScore << endl;
				cout << "IrnRank: " << current->IrnRank << endl;
				cout << "GerScore: " << current->GerScore << endl;
				cout << "GerRank: " << current->GerRank << endl;
				cout << "ScoreScaled: " << current->ScoreScaled << endl << endl;
			}
			current = current->nextAddress;
			count++;
		}
		if (current == NULL) {
			cout << "End of the list! " << endl << endl;
		} else {
			cout << "Displaying results " << startIndex + 1 << " to " << min(endIndex, count) << endl << endl;
			if (current->nextAddress != NULL) {
				cout << "1. Next 20 results" << endl;
			}
			if (currentPage > 1) {
				cout << "2. Previous 20 results" << endl;
			}
			cout << "0. Exit" << endl << endl;
			cout << "Choose an option:";

			int option;
			cin >> option;
			cout << endl;

			switch (option) {
			case 1:
				DisplayRankingInfo(rankingList,currentPage + 1);
				break;
			case 2:
				if (currentPage > 1) {
					DisplayRankingInfo(rankingList,currentPage - 1);
				} else {
					DisplayRankingInfo(rankingList,currentPage);
				}
				break;
			case 0:
				return;
			default:
				cout << "Invalid choice. Exiting..." << endl << endl;
				return;
			}
		}
	}

	// ============================== //
	// ===== FILE I/O FUNCTIONS ===== //

	RankingList importRanking() {
		RankingList allrankingList;
		string file_ranking;
		string file_universityName;
		string file_locationCode;
		string file_location;
		string file_universityID;
		string file_ArScore;
		string file_ArRank;
		string file_ErScore;
		string file_ErRank;
		string file_FsrScore;
		string file_FsrRank;
		string file_CpfScore;
		string file_CpfRank;
		string file_IfrScore;
		string file_IfrRank;
		string file_IsrScore;
		string file_IsrRank;
		string file_IrnScore;
		string file_IrnRank;
		string file_GerScore;
		string file_GerRank;
		string file_ScoreScaled;

		int IDcounter = 1;
		ifstream file("2023 QS World University Rankings.csv");

		// skip the first line
		string str;
		getline(file, str);
		str.clear();

		while (file.good()) {
			// add university ID started by U
			file_universityID = "U" + to_string(IDcounter);

			string rowData;
			getline(file, rowData);
			stringstream iss(rowData);
			string token;

			getline(iss, token, ',');
			file_ranking = token;

			getline(iss, token, ',');
			if ((token[0] == '\"')) {
				while (token[token.size() - 1] != '\"') {
					std::string temp;
					std::getline(iss, temp, ',');
					token += "," + temp;
				}
				file_universityName = trim(token.substr(1, token.size() - 2));
			} else {
				file_universityName = trim(token);
			}

			getline(iss, token, ',');
			file_locationCode = token;

			getline(iss, token, ',');
			if ((token[0] == '\"')) {
				while (token[token.size() - 1] != '\"') {
					std::string temp;
					std::getline(iss, temp, ',');
					token += "," + temp;
				}
				file_location = token.substr(1, token.size() - 2);
			} else {
				file_location = token;
			}

			getline(iss, token, ',');
			file_ArScore = token.empty() ? "0" : token;
			getline(iss, token, ',');
			file_ArRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_ErScore = token.empty() ? "0" : token;
			getline(iss, token, ',');
			file_ErRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_FsrScore = token.empty() ? "0" : token;
			getline(iss, token, ',');
			file_FsrRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_CpfScore = token.empty() ? "0" : token;
			getline(iss, token, ',');
			file_CpfRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_IfrScore = token.empty() ? "0" : token;
			getline(iss, token, ',');
			file_IfrRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_IsrScore = token.empty() ? "0" : token;
			getline(iss, token, ',');
			file_IsrRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_IrnScore = token.empty() ? "0" : token;
			getline(iss, token, ',');
			file_IrnRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_GerScore = token.empty() ? "0" : token;
			getline(iss, token, ',');
			file_GerRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_ScoreScaled = token.empty() ? "NULL" : token;

			// If the file_ranking is empty, it means we have reached the end of the file, so we break the loop
			if (file_ranking.empty()) {
				break;
			}

			// Increment the IDcounter
			IDcounter = IDcounter + 1;

			// Insert the extracted values into the RankingList
			allrankingList.InsertToEndList(
				file_universityID, 
				file_ranking,
				file_universityName,
				file_locationCode,
				file_location,
				file_ArScore,
				file_ArRank,
				file_ErScore,
				file_ErRank,
				file_FsrScore,
				file_FsrRank,
				file_CpfScore,
				file_CpfRank,
				file_IfrScore,
				file_IfrRank,
				file_IsrScore,
				file_IsrRank,
				file_IrnScore,
				file_IrnRank,
				file_GerScore,
				file_GerRank,
				file_ScoreScaled);
		}
		return allrankingList;
	}

	// ======================== //
	// ===== SORTING ALGO ===== //

	void MergeSortAndDisplayUniByOption(RankingList& rankingList,int sortOption) {
		Ranking* sortedList = MergeSort(rankingList.head, sortOption);
		rankingList.head = sortedList;
		DisplayRankingInfo(rankingList,1);
	}

	void MergeSortCompare(RankingList& rankingList,int sortOption) {
		Ranking* sortedList = MergeSort(rankingList.head, sortOption);
		rankingList.head = sortedList;
	}

	Ranking* Split(Ranking* head) {
		Ranking *fast = head, *slow = head;
		while (fast->nextAddress && fast->nextAddress->nextAddress) {
			fast = fast->nextAddress->nextAddress;
			slow = slow->nextAddress;
		}
		Ranking* temp = slow->nextAddress;
		slow->nextAddress = NULL;
		return temp;
	}

	Ranking* MergeSort(Ranking* head, int sortOption) {
		if (!head || !head->nextAddress) return head;

		// Split the list into two halves
		Ranking* second = Split(head);

		// Recursively sort the two halves
		head = MergeSort(head, sortOption);
		second = MergeSort(second, sortOption);

		// Merge the sorted halves based on the sort option
		switch (sortOption) {
		case 1:
			return MergeByName(head, second);
		case 2:
			return MergeByArScore(head, second);
		case 3:
			return MergeByFsrScore(head, second);
		case 4:
			return MergeByErScore(head, second);
		case 5:
			return MergeByRank(head, second);
		case 6:
			return MergeByCountry(head, second); 
		default:
			return MergeByName(head, second); // Default to sort by name
		}
	}

	Ranking* MergeByRank(Ranking* first, Ranking* second) {
		if (!first) return second;
		if (!second) return first;

		if (stod(first->ranking) < stod(second->ranking)) {
			first->nextAddress = MergeByRank(first->nextAddress, second);
			first->nextAddress->prevAddress = first;
			first->prevAddress = NULL;
			return first;
		} else {
			second->nextAddress = MergeByRank(first, second->nextAddress);
			second->nextAddress->prevAddress = second;
			second->prevAddress = NULL;
			return second;
		}
	}

	Ranking* MergeByName(Ranking* first, Ranking* second) {
		if (!first) return second;
		if (!second) return first;

		string upperFirst, upperSecond;
		upperFirst = first->universityName;
		upperSecond = second->universityName;

		// Convert both strings to lowercase for case-insensitive comparison
		for (auto& c: upperFirst)
			c = std::tolower(static_cast<unsigned char>(c));
		for (auto& c: upperSecond)
			c = std::tolower(static_cast<unsigned char>(c));


		if (upperFirst < upperSecond) {
			first->nextAddress = MergeByName(first->nextAddress, second);
			first->nextAddress->prevAddress = first;
			first->prevAddress = NULL;
			return first;
		} else {
			second->nextAddress = MergeByName(first, second->nextAddress);
			second->nextAddress->prevAddress = second;
			second->prevAddress = NULL;
			return second;
		}
	}

	Ranking* MergeByCountry(Ranking* first, Ranking* second) {
		if (!first) return second;
		if (!second) return first;

		string upperFirst, upperSecond;
		upperFirst = first->location;
		upperSecond = second->location;

		// Convert both strings to lowercase for case-insensitive comparison
		for (auto& c: upperFirst)
			c = std::tolower(static_cast<unsigned char>(c));
		for (auto& c: upperSecond)
			c = std::tolower(static_cast<unsigned char>(c));


		if (upperFirst < upperSecond) {
			first->nextAddress = MergeByCountry(first->nextAddress, second);
			first->nextAddress->prevAddress = first;
			first->prevAddress = NULL;
			return first;
		} else {
			second->nextAddress = MergeByCountry(first, second->nextAddress);
			second->nextAddress->prevAddress = second;
			second->prevAddress = NULL;
			return second;
		}
	}

	Ranking* MergeByArScore(Ranking* first, Ranking* second) {
		if (!first) return second;
		if (!second) return first;

		if (stod(first->ArScore) > stod(second->ArScore)) {
			first->nextAddress = MergeByArScore(first->nextAddress, second);
			first->nextAddress->prevAddress = first;
			first->prevAddress = NULL;
			return first;
		} else {
			second->nextAddress = MergeByArScore(first, second->nextAddress);
			second->nextAddress->prevAddress = second;
			second->prevAddress = NULL;
			return second;
		}
	}

	Ranking* MergeByFsrScore(Ranking* first, Ranking* second) {
		if (!first) return second;
		if (!second) return first;

		if (stod(first->FsrScore) > stod(second->FsrScore)) {
			first->nextAddress = MergeByFsrScore(first->nextAddress, second);
			first->nextAddress->prevAddress = first;
			first->prevAddress = NULL;
			return first;
		} else {
			second->nextAddress = MergeByFsrScore(first, second->nextAddress);
			second->nextAddress->prevAddress = second;
			second->prevAddress = NULL;
			return second;
		}
	}

	Ranking* MergeByErScore(Ranking* first, Ranking* second) {
		if (!first) return second;
		if (!second) return first;

		if (stod(first->ErScore) > stod(second->ErScore)) {
			first->nextAddress = MergeByErScore(first->nextAddress, second);
			first->nextAddress->prevAddress = first;
			first->prevAddress = NULL;
			return first;
		} else {
			second->nextAddress = MergeByErScore(first, second->nextAddress);
			second->nextAddress->prevAddress = second;
			second->prevAddress = NULL;
			return second;
		}
	}

	void QuickSortAndDisplayUni(RankingList& rankingList,int sortOption) {
		QuickSort(rankingList.head, rankingList.tail, sortOption);
		DisplayRankingInfo(rankingList,1);
	}

	void QuickSortCompare(RankingList& rankingList,int sortOption) {
		QuickSort(rankingList.head, rankingList.tail, sortOption);
	}

	void Swap(Ranking* a, Ranking* b) { 
		//Ranking* temp = NULL;

		Ranking* temp = CreateNewNode(
			a->universityID,
			a->ranking,
			a->universityName,
			a->locationCode,
			a->location,
			a->ArScore,
			a->ArRank,
			a->ErScore,
			a->ErRank,
			a->FsrScore,
			a->FsrRank,
			a->CpfScore,
			a->CpfRank,
			a->IfrScore,
			a->IfrRank,
			a->IsrScore,
			a->IsrRank,
			a->IrnScore,
			a->IrnRank,
			a->GerScore,
			a->GerRank,
			a->ScoreScaled);

		//a store b
		a->universityID = b->universityID;
		a->ranking = b->ranking;
		a->universityName = b->universityName;
		a->locationCode = b->locationCode;
		a->location = b->location;
		a->ArScore = b->ArScore;
		a->ArRank = b->ArRank;
		a->ErScore = b->ErScore;
		a->ErRank = b->ErRank;
		a->FsrScore = b->FsrScore;
		a->FsrRank = b->FsrRank;
		a->CpfScore = b->CpfScore;
		a->CpfRank = b->CpfRank;
		a->IfrScore = b->IfrScore;
		a->IfrRank = b->IfrRank;
		a->IsrScore = b->IsrScore;
		a->IsrRank = b->IsrRank;
		a->IrnScore = b->IrnScore;
		a->IrnRank = b->IrnRank;
		a->GerScore = b->GerScore;
		a->GerRank = b->GerRank;
		a->ScoreScaled = b->ScoreScaled;

		// b store temp
		b->universityID = temp->universityID;
		b->ranking = temp->ranking;
		b->universityName = temp->universityName;
		b->locationCode = temp->locationCode;
		b->location = temp->location;
		b->ArScore = temp->ArScore;
		b->ArRank = temp->ArRank;
		b->ErScore = temp->ErScore;
		b->ErRank = temp->ErRank;
		b->FsrScore = temp->FsrScore;
		b->FsrRank = temp->FsrRank;
		b->CpfScore = temp->CpfScore;
		b->CpfRank = temp->CpfRank;
		b->IfrScore = temp->IfrScore;
		b->IfrRank = temp->IfrRank;
		b->IsrScore = temp->IsrScore;
		b->IsrRank = temp->IsrRank;
		b->IrnScore = temp->IrnScore;
		b->IrnRank = temp->IrnRank;
		b->GerScore = temp->GerScore;
		b->GerRank = temp->GerRank;
		b->ScoreScaled = temp->ScoreScaled;

		delete temp;

	}

	void QuickSort(Ranking* head, Ranking* tail, int sortOption) {
		if (tail != NULL && head != tail && head != tail->nextAddress) {
			Ranking* p = Partition(head, tail, sortOption);
			QuickSort(head, p->prevAddress, sortOption);
			QuickSort(p->nextAddress, tail, sortOption);
		}
	}

	Ranking* Partition(Ranking* head, Ranking* tail, int sortOption) {
		Ranking* i = head->prevAddress;
		Ranking* pivot = tail;

		for (Ranking* j = head; j != tail; j = j->nextAddress) {
			bool shouldSwap = false;

			switch (sortOption) {
			case 1: // Sort by universityName
				// Convert both strings to lowercase for case-insensitive comparison
				for (auto& c: j->universityName)
					c = std::tolower(static_cast<unsigned char>(c));
				for (auto& c: pivot->universityName)
					c = std::tolower(static_cast<unsigned char>(c));
				shouldSwap = (j->universityName <= pivot->universityName);
				break;
			case 2: // Sort by ArScore
				shouldSwap = (stod(j->ArScore) >= stod(pivot->ArScore));
				break;
			case 3: // Sort by FsrScore
				shouldSwap = (stod(j->FsrScore) >= stod(pivot->FsrScore));
				break;
			case 4: // Sort by ErScore
				shouldSwap = (stod(j->ErScore) >= stod(pivot->ErScore));
				break;
			default:
				shouldSwap = (j->universityName >= pivot->universityName);
				break;
			}

			if (shouldSwap) {
				i = (i == nullptr) ? head : i->nextAddress;
				Swap(i, j);
			}
		}

		i = (i == nullptr) ? head : i->nextAddress;
		Swap(i, tail);
		return i;
	}

	// ========================== //
	// ===== SEARCHING ALGO ===== //

	void searchUniByCountry(RankingList& rankingList, string searchQuery) {
		if (rankingList.head == NULL) {
			cout << "Empty University List" << endl << endl;
		} else {
			Ranking* firstPtr = rankingList.head;
			Ranking* secondPtr = rankingList.tail;
			bool found = false;

			while (firstPtr != NULL && secondPtr != NULL && firstPtr != secondPtr && firstPtr->prevAddress != secondPtr) {
				if (firstPtr->location.find(searchQuery) != string::npos) {
					cout << "Univerisity ID: " << firstPtr->universityID << endl;
					cout << "Univerisity Name: " << firstPtr->universityName << endl;
					cout << "Univerisity Country Code: " << firstPtr->locationCode << endl;
					cout << "Univerisity Country: " << firstPtr->location << endl << endl;

					found = true;
				}

				if (secondPtr->location.find(searchQuery) != string::npos) {
					cout << "University ID: " << secondPtr->universityID << endl;
					cout << "University Name: " << secondPtr->universityName << endl;
					cout << "University Country Code: " << secondPtr->locationCode << endl;
					cout << "University Country: " << secondPtr->location << endl << endl;

					found = true;
				}

				firstPtr = firstPtr->nextAddress;
				secondPtr = secondPtr->prevAddress;
			}

			if (!found && firstPtr != NULL && firstPtr == secondPtr && firstPtr->location.find(searchQuery) != string::npos) {
				cout << "University ID: " << firstPtr->universityID << endl;
				cout << "University Name: " << firstPtr->universityName << endl;
				cout << "University Country Code: " << firstPtr->locationCode << endl;
				cout << "University Country: " << firstPtr->location << endl << endl;

				found = true;
			}

			if (!found) {
				cout << "No universities found with country containing '" << searchQuery << "'." << endl << endl;
			}
		}
	}

	void searchUniByRankingForCompare(RankingList& rankingList, string searchQuery) {
		if (rankingList.head == NULL) {
			cout << "Empty University List" << endl << endl;
		} else {
			Ranking* firstPtr = rankingList.head;
			Ranking* secondPtr = rankingList.tail;
			bool found = false;

			while (firstPtr != NULL && secondPtr != NULL && firstPtr != secondPtr && firstPtr->prevAddress != secondPtr) {
				if (stoi(firstPtr->ranking) == stoi(searchQuery)) {
					found = true;
				}

				if (stoi(secondPtr->ranking) == stoi(searchQuery)) {
					found = true;
				}

				firstPtr = firstPtr->nextAddress;
				secondPtr = secondPtr->prevAddress;
			}

			if (
				!found && firstPtr != NULL && firstPtr == secondPtr && stoi(firstPtr->ranking) == stoi(searchQuery)) {
				found = true;
			}

			if (!found) {
				cout << "No universities found with ranking '" << searchQuery << "'." << endl << endl;
			}
		}
	}

	void searchUniByName(RankingList& rankingList, string searchQuery) {
		if (rankingList.head == NULL) {
			cout << "Empty University List" << endl << endl;
		} else {
			Ranking* firstPtr = rankingList.head;
			Ranking* secondPtr = rankingList.tail;
			bool found = false;

			while (firstPtr != NULL && secondPtr != NULL && firstPtr != secondPtr && firstPtr->prevAddress != secondPtr) {
				if (firstPtr->universityName.find(searchQuery) != string::npos) {
					cout << "Univerisity ID: " << firstPtr->universityID << endl;
					cout << "Univerisity Name: " << firstPtr->universityName << endl;
					cout << "Univerisity Country Code: " << firstPtr->locationCode << endl;
					cout << "Univerisity Country: " << firstPtr->location << endl << endl;

					found = true;
				}

				if (secondPtr->universityName.find(searchQuery) != string::npos) {
					cout << "University ID: " << secondPtr->universityID << endl;
					cout << "University Name: " << secondPtr->universityName << endl;
					cout << "University Country Code: " << secondPtr->locationCode << endl;
					cout << "University Country: " << secondPtr->location << endl << endl;

					found = true;
				}

				firstPtr = firstPtr->nextAddress;
				secondPtr = secondPtr->prevAddress;
			}

			if (
				!found && firstPtr != NULL && firstPtr == secondPtr
				&& firstPtr->universityName.find(searchQuery) != string::npos) {
				cout << "University ID: " << firstPtr->universityID << endl;
				cout << "University Name: " << firstPtr->universityName << endl;
				cout << "University Country Code: " << firstPtr->locationCode << endl;
				cout << "University Country: " << firstPtr->location << endl << endl;

				found = true;
			}

			if (!found) {
				cout << "No universities found with names containing '" << searchQuery << "'." << endl << endl;
			}
		}
	}

	void binarySearchUniByRanking(RankingList& rankingList,string searchQuery) {
		int firstIndex = 1;
		int lastIndex = getUniversityListLenght(rankingList);
		bool found = false;

		MergeSortCompare(rankingList, 5);

		while (firstIndex <= lastIndex) {
			int midIndex = (firstIndex + lastIndex) / 2;
			Ranking* mid = getUniversityAtIndex(rankingList,midIndex);

			if (stoi(mid->ranking) == stoi(searchQuery)) {
				cout << "University ID: " << mid->universityID << endl;
				cout << "University Name: " << mid->universityName << endl;
				cout << "University Country Code: " << mid->locationCode << endl;
				cout << "University Country: " << mid->location << endl << endl;
				found = true;
				return;
			}

			if (stoi(mid->ranking) < stoi(searchQuery)) {
				firstIndex = midIndex + 1;
			} else {
				lastIndex = midIndex - 1;
			}
		}
		if (!found) {
			cout << "No universities found with ranking '" << searchQuery << "'." << endl << endl;
		}
	}

	void binarySearchUniByRankingForCompare(RankingList& rankingList, string searchQuery) {
		int firstIndex = 1;
		int lastIndex = getUniversityListLenght(rankingList);
		bool found = false;

		while (firstIndex <= lastIndex) {
			int midIndex = (firstIndex + lastIndex) / 2;
			Ranking* mid = getUniversityAtIndex(rankingList, midIndex);

			if (stoi(mid->ranking) == stoi(searchQuery)) {
				found = true;
				return;
			}

			if (stoi(mid->ranking) < stoi(searchQuery)) {
				firstIndex = midIndex + 1;
			} else {
				lastIndex = midIndex - 1;
			}
		}
		if (!found) {
			cout << "No universities found with ranking '" << searchQuery << "'." << endl << endl;
		}
	}

	// ============================= //
	// ===== UTILITY FUNCTIONS ===== //

	int getUniversityListLenght(RankingList& rankingList) {
		int length = 0;
		for (Ranking* ptr = rankingList.head; ptr != NULL; ptr = ptr->nextAddress) {
			length++;
		}

		return length;
	}

	Ranking* getUniversityAtIndex(RankingList& rankingList, int index) {
		Ranking* current = rankingList.head;
		int currentIndex = 1;

		while (current != NULL && currentIndex < index) {
			current = current->nextAddress;
			currentIndex++;
		}

		return current;
	}

	string trim(const string& str) {
		// Find the first non-whitespace character
		auto start = str.find_first_not_of(" \t\n\r\f\v");

		// If the string is all whitespace, return an empty string
		if (start == std::string::npos) return "";

		// Find the last non-whitespace character
		auto end = str.find_last_not_of(" \t\n\r\f\v");

		// Calculate the length of the trimmed string
		auto length = end - start + 1;

		// Return the trimmed substring
		return str.substr(start, length);
	}

	string getUniNameByID(RankingList& rankingList, string searchQuery) {
		if (rankingList.head == NULL) {
			cout << "No University Found" << endl << endl;
		} else {
			Ranking* current = rankingList.head;

			while (current != NULL) {
				if (current->universityID == searchQuery) {
					return current->universityName;
				}
				current = current->nextAddress;
			}
		}

		return "University not found.";
	}

	bool SearchUniByID(RankingList& rankingList, string searchQuery) {
		if (rankingList.head == NULL) {
			cout << "No University Found" << endl << endl;
		} else {
			Ranking* current = rankingList.head;
			bool found = false;

			while (current != NULL) {
				if (current->universityID == searchQuery) {
					cout << "University ID: " << current->universityID << endl;
					cout << "University Name: " << current->universityName << endl;
					cout << "University Country Code: " << current->locationCode << endl;
					cout << "University Country: " << current->location << endl << endl;

					found = true;
					break;
				}

				current = current->nextAddress;
			}

			if (!found) {
				cout << "No university found with ID: '" << searchQuery << "'." << endl << endl;
			}
			return found;
		}
	}

	// ======================================================== //
	// ===== BINARY SEARCH BY COUNTRY NOT PERFECT BUT IDK ===== //
	
	void searchUniByCountryForCompare(RankingList& rankingList, string searchQuery) {
		if (rankingList.head == NULL) {
			cout << "Empty University List" << endl << endl;
		} else {
			Ranking* firstPtr = rankingList.head;
			Ranking* secondPtr = rankingList.tail;
			bool found = false;

			while (firstPtr != NULL && secondPtr != NULL && firstPtr != secondPtr && firstPtr->prevAddress != secondPtr) {
				if (firstPtr->location.find(searchQuery) != string::npos) { found = true; }
				if (secondPtr->location.find(searchQuery) != string::npos) { found = true; }

				firstPtr = firstPtr->nextAddress;
				secondPtr = secondPtr->prevAddress;
			}

			if (!found && firstPtr != NULL && firstPtr == secondPtr && firstPtr->location.find(searchQuery) != string::npos) {
				found = true;
			}

			if (!found) {
				cout << "No universities found with ranking '" << searchQuery << "'." << endl << endl;
			}
		}
	}
};
