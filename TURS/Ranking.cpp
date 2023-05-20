#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

using namespace std;

struct Ranking {
	string universityID;
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
		newnode->nextAddress = NULL;

		// newnode address
		return newnode;
	}

	void InsertToEndList(
		string universityID,
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
			head = tail = newnode;
		} else // if not empty list, just bring to the end of the list.
		{
			newnode->prevAddress = tail;
			tail->nextAddress = newnode;
			tail = newnode;
		}
	}

	// additional feature
	void DisplayAllRankingInfo() {
		Ranking* current = head;

		while (current != NULL) // means still not the end of the list
		{
			cout << "Univerisity ID: " << current->universityID << endl;
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
			current = current->nextAddress; // if you forgot this, will become a infinity loop
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
			int commaCount = 0;
			string remainingData;

			// add university ID started by U
			file_universityID = "U" + to_string(IDcounter);

			// Read the file_ranking value until a comma is encountered
			getline(file, file_ranking, ',');

			// Read the remaining data of the line into remainingData
			getline(file, remainingData);
			// Iterate over remainingData from right to left
			for (int i = remainingData.size() - 1; i >= 0; i--) {
				// Count the number of commas encountered
				if (remainingData[i] == ',') {
					commaCount++;

					// If we have encountered the 19th comma, extract the required values
					if (commaCount == 19) {
						// Extract the universityName substring
						file_universityName = remainingData.substr(0, i);
						remainingData.erase(0, file_universityName.size() + 1);

						// Extract the locationCode substring
						file_locationCode = remainingData.substr(0, remainingData.find(","));
						remainingData.erase(0, file_locationCode.size() + 1);

						// Extract the location substring
						file_location = remainingData.substr(0, remainingData.find(","));
						remainingData.erase(0, file_location.size() + 1);
					}
				}
			}

			string data[100];
			int count = 0;
			string temp = "";

			for (char c : remainingData) {
				if (c != ',') {
					temp += c;
				} else {
					data[count++] = temp;
					temp = "";
				}
			}
			data[count++] = temp;

			// Replacing empty strings with "0"
			for (int i = 0; i < count; i++) {
				if (data[i].empty()) {
					data[i] = "0";
				}
			}

			// Storing the values into an array
			string resultArray[20];
			for (int i = 0; i < count; i++) {
				resultArray[i] = data[i];
			}

			file_ArScore = stod(data[0]);
			file_ArRank = stod(data[1]);

			file_ErScore = stod(data[2]);
			file_ErRank = stod(data[3]);

			file_FsrScore = stod(data[4]);
			file_FsrRank = stod(data[5]);

			file_CpfScore = stod(data[6]);
			file_CpfRank = stod(data[7]);

			file_IfrScore = stod(data[8]);
			file_IfrRank = stod(data[9]);

			file_IsrScore = stod(data[10]);
			file_IsrRank = stod(data[11]);

			file_IrnScore = stod(data[12]);
			file_IrnRank = stod(data[13]);

			file_GerScore = stod(data[14]);
			file_GerRank = stod(data[15]);

			file_ScoreScaled = stod(data[16]);

			// If the file_ranking is empty, it means we have reached the end of the file, so we break the loop
			if (file_ranking.empty()) {
				break;
			}
			
			// Increment the IDcounter
			IDcounter = IDcounter + 1;

			// Insert the extracted values into the RankingList
			InsertToEndList(
				file_universityID,
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
				file_ScoreScaled
			);
		}

		rankingList.DisplayAllRankingInfo();

		return rankingList;
	}

	RankingList importRanking2() {
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

		DisplayAllRankingInfo();

		return rankingList;
	}
};

// int main()
//{
//	//Call object and constructor
//	RankingList rankingList;
//	//Define variable
//	string universityID, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank, CpfScore, CpfRank, IfrScore, IfrRank,
//IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled;
//	//input file
//	ifstream file("C://Users//cylin//Desktop//APU//APU2F2209SE//Semester 2//DSTR//Assignment//Ranking.csv");
//	//skip the first line
//	string str;
//	getline(file, str);
//	str.clear();
//	while (file.good())
//	{
//		getline(file, universityID, ',');
//		getline(file, ArScore, ',');
//		getline(file, ArRank, ',');
//		getline(file, ErScore, ',');
//		getline(file, ErRank, ',');
//		getline(file, FsrScore, ',');
//		getline(file, FsrRank, ',');
//		getline(file, CpfScore, ',');
//		getline(file, CpfRank, ',');
//		getline(file, IfrScore, ',');
//		getline(file, IfrRank, ',');
//		getline(file, IsrScore, ',');
//		getline(file, IsrRank, ',');
//		getline(file, IrnScore, ',');
//		getline(file, IrnRank, ',');
//		getline(file, GerScore, ',');
//		getline(file, GerRank, ',');
//		getline(file, ScoreScaled, '\n');
//		if (universityID == "universityID")
//		{
//			continue;
//		}
//		else if (universityID == "")
//		{
//			break;
//		}
//
//		rankingList.InsertToEndList(universityID, stod(ArScore), stod(ArRank), stod(ErScore), stod(ErRank),
//stod(FsrScore), stod(FsrRank), stod(CpfScore), stod(CpfRank), stod(IfrScore), stod(IfrRank), stod(IsrScore),
//stod(IsrRank), stod(IrnScore), stod(IrnRank), stod(GerScore), stod(GerRank), stod(ScoreScaled));
//	}
//	file.close();
//
//	cout << "Final Feedback List from the CSV file as below: " << endl << string(50, '=') << endl;
//	rankingList.DisplayAllRankingInfo();
//	cout << endl << string(50, '=') << endl;
//
//	system("pause");
//
//	return 0;
// }
