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

	int getUniversityListLenght() {
		int length = 0;
		for (Ranking* ptr = head; ptr != NULL; ptr = ptr->nextAddress) {
			length++;
		}

		return length;
	}

	Ranking* getUniversityAtIndex(int index) {
		Ranking* current = head;
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

	void DisplayRankingInfo(int currentPage) {
		int pageSize = 20;
		int startIndex = (currentPage - 1) * pageSize;
		int endIndex = startIndex + pageSize;
		
		Ranking* current = head;
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
			cout << "1. Next 20 results" << endl;
			cout << "2. Previous 20 results" << endl;
			cout << "3. Exit" << endl << endl;
			cout << "Choose an option:";

			int option;
			cin >> option;
			cout << endl;

			switch (option) {
			case 1:
				DisplayRankingInfo(currentPage + 1);
				break;
			case 2:
				if (currentPage > 1) {
					DisplayRankingInfo(currentPage - 1);
				} else {
					DisplayRankingInfo(currentPage);
				}
				break;
			case 3:
				return;
			default:
				cout << "Invalid choice. Exiting..." << endl << endl;
			}
		}
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
		rankingList.DisplayRankingInfo(1);
		return sortedList;
	}

	void MergeSortForCompare(int sortOption) {
		RankingList rankingList;
		rankingList.importRanking();
		Ranking* sortedList = MergeSort(rankingList.head, sortOption);
		rankingList.head = sortedList;
		return;
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
				shouldSwap = (j->universityName >= pivot->universityName);
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

	void binarySearchUniByName(string searchQuery) {
		int firstIndex = 1;
		int lastIndex = getUniversityListLenght();
		bool found = false;

		Ranking* temp = head;
		MergeSort(temp, 1);

		while (firstIndex <= lastIndex) {
			int midIndex = (firstIndex + lastIndex) / 2;
			Ranking* mid = getUniversityAtIndex(midIndex);

			if (mid->universityName.find(searchQuery) != string::npos) {
				cout << "University ID: " << mid->universityID << endl;
				cout << "University Name: " << mid->universityName << endl;
				cout << "University Country Code: " << mid->locationCode << endl;
				cout << "University Country: " << mid->location << endl << endl;

				found = true;
			}

			int compareResult = searchQuery.compare(mid->universityName);

			if (compareResult < 0) {
				lastIndex = midIndex - 1;
			} else {
				firstIndex = midIndex + 1;
			}
		}
		if (!found) {
			cout << "No universities found with names containing '" << searchQuery << "'." << endl << endl;
		}
	}

	void binarySearchUniByRanking() {
		string searchQuery;

		cout << "Binary Search University Ranking: ";
		cin.ignore();
		getline(cin, searchQuery);
		cout << endl;

		int firstIndex = 1;
		int lastIndex = getUniversityListLenght();
		bool found = false;

		Ranking* temp = head;

		while (firstIndex <= lastIndex) {
			int midIndex = (firstIndex + lastIndex) / 2;
			Ranking* mid = getUniversityAtIndex(midIndex);

			if (stod(mid->ranking) == stod(searchQuery)) {
				cout << "University ID: " << mid->universityID << endl;
				cout << "University Name: " << mid->universityName << endl;
				cout << "University Country Code: " << mid->locationCode << endl;
				cout << "University Country: " << mid->location << endl << endl;

				found = true;
			}

			int compareResult = searchQuery.compare(mid->universityName);

			if (compareResult < 0) {
				lastIndex = midIndex - 1;
			} else {
				firstIndex = midIndex + 1;
			}
		}
		if (!found) {
			cout << "No universities found with names containing '" << searchQuery << "'." << endl << endl;
		}
	}
};
