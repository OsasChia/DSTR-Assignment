#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

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
	// Methods
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

	void DisplayRankingInfo() {
		Ranking* current = head;
		while (current != NULL) {
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
			current = current->nextAddress;
		}
		cout << "List is ended here! " << endl;
	}


	RankingList importRanking() {
		RankingList rankingList;
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
				file_universityName = token.substr(1, token.size() - 2);
			} else {
				file_universityName = token;
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
			file_ArScore = token.empty() ? "NULL" : token;
			getline(iss, token, ',');
			file_ArRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_ErScore = token.empty() ? "NULL" : token;
			getline(iss, token, ',');
			file_ErRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_FsrScore = token.empty() ? "NULL" : token;
			getline(iss, token, ',');
			file_FsrRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_CpfScore = token.empty() ? "NULL" : token;
			getline(iss, token, ',');
			file_CpfRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_IfrScore = token.empty() ? "NULL" : token;
			getline(iss, token, ',');
			file_IfrRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_IsrScore = token.empty() ? "NULL" : token;
			getline(iss, token, ',');
			file_IsrRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_IrnScore = token.empty() ? "NULL" : token;
			getline(iss, token, ',');
			file_IrnRank = token.empty() ? "NULL" : token;

			getline(iss, token, ',');
			file_GerScore = token.empty() ? "NULL" : token;
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
			InsertToEndList(
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
		return rankingList;
	}

	Ranking* MergeSortAndDisplayUniByOption(int sortOption) {
		RankingList rankingList;
		rankingList.importRanking();
		Ranking* sortedList = MergeSort(rankingList.head, sortOption);
		rankingList.head = sortedList;
		//rankingList.DisplayRankingInfo();
		return sortedList;
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
		default:
			return MergeByName(head, second); // Default to sort by name
		}
	}

	Ranking* MergeByName(Ranking* first, Ranking* second) {
		if (!first) return second;
		if (!second) return first;

		if (first->universityName < second->universityName) {
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

	Ranking* MergeByArScore(Ranking* first, Ranking* second) {
		if (!first) return second;
		if (!second) return first;

		if (stod(first->ArScore) < stod(second->ArScore)) {
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

		if (stod(first->FsrScore) < stod(second->FsrScore)) {
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

		if (stod(first->ErScore) < stod(second->ErScore)) {
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

	void QuickSortAndDisplayUni(int sortOption) {
		RankingList rankingList;
		rankingList.importRanking();
		QuickSort(rankingList.head, rankingList.tail, sortOption);
		//rankingList.DisplayRankingInfo();
	}

	void Swap(Ranking* a, Ranking* b) { 
		swap(a->universityID, b->universityID);
		swap(a->ranking, b->ranking);
		swap(a->universityName, b->universityName);
		swap(a->locationCode, b->locationCode);
		swap(a->location, b->location);
		swap(a->ArScore, b->ArScore);
		swap(a->ArRank, b->ArRank);
		swap(a->ErScore, b->ErScore);
		swap(a->ErRank, b->ErRank);
		swap(a->FsrScore, b->FsrScore);
		swap(a->FsrRank, b->FsrRank);
		swap(a->CpfScore, b->CpfScore);
		swap(a->CpfRank, b->CpfRank);
		swap(a->IfrScore, b->IfrScore);
		swap(a->IfrRank, b->IfrRank);
		swap(a->IsrScore, b->IsrScore);
		swap(a->IsrRank, b->IsrRank);
		swap(a->IrnScore, b->IrnScore);
		swap(a->IrnRank, b->IrnRank);
		swap(a->GerScore, b->GerScore);
		swap(a->GerRank, b->GerRank);
		swap(a->ScoreScaled, b->ScoreScaled);

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
				shouldSwap = (j->universityName <= pivot->universityName);
				break;
			case 2: // Sort by ArScore
				shouldSwap = (stod(j->ArScore) <= stod(pivot->ArScore));
				break;
			case 3: // Sort by FsrScore
				shouldSwap = (stod(j->FsrScore) <= stod(pivot->FsrScore));
				break;
			case 4: // Sort by ErScore
				shouldSwap = (stod(j->ErScore) <= stod(pivot->ErScore));
				break;
			default:
				shouldSwap = (j->universityName <= pivot->universityName);
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
};

