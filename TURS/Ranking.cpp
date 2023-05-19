#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Ranking {
	string universityID;
	double ArScore;
	double ArRank;
	double ErScore;
	double ErRank;
	double FsrScore;
	double FsrRank;
	double CpfScore;
	double CpfRank;
	double IfrScore;
	double IfrRank;
	double IsrScore;
	double IsrRank;
	double IrnScore;
	double IrnRank;
	double GerScore;
	double GerRank;
	double ScoreScaled;
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
		double ArScore,
		double ArRank,
		double ErScore,
		double ErRank,
		double FsrScore,
		double FsrRank,
		double CpfScore,
		double CpfRank,
		double IfrScore,
		double IfrRank,
		double IsrScore,
		double IsrRank,
		double IrnScore,
		double IrnRank,
		double GerScore,
		double GerRank,
		double ScoreScaled) {
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
		double ArScore,
		double ArRank,
		double ErScore,
		double ErRank,
		double FsrScore,
		double FsrRank,
		double CpfScore,
		double CpfRank,
		double IfrScore,
		double IfrRank,
		double IsrScore,
		double IsrRank,
		double IrnScore,
		double IrnRank,
		double GerScore,
		double GerRank,
		double ScoreScaled) {
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
			cout << "ScoreScaled: " << current->ScoreScaled << endl;
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
		double file_ArScore;
		double file_ArRank;
		double file_ErScore;
		double file_ErRank;
		double file_FsrScore;
		double file_FsrRank;
		double file_CpfScore;
		double file_CpfRank;
		double file_IfrScore;
		double file_IfrRank;
		double file_IsrScore;
		double file_IsrRank;
		double file_IrnScore;
		double file_IrnRank;
		double file_GerScore;
		double file_GerRank;
		double file_ScoreScaled;

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

						// Extract the ArScore
						file_ArScore = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_ArScore.size() + 1);

						// Extract the ArRank
						file_ArRank = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_ArRank.size() + 1);

						// Extract the ErScore
						file_ErScore = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_ErScore.size() + 1);

						// Extract the ErRank
						file_ErRank = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_ErRank.size() + 1);

						// Extract the FsrScore
						file_FsrScore = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_FsrScore.size() + 1);

						// Extract the FsrRank
						file_FsrRank = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_FsrRank.size() + 1);

						// Extract the CpfScore
						file_CpfScore = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_CpfScore.size() + 1);

						// Extract the CpfRank
						file_CpfRank = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_CpfRank.size() + 1);

						// Extract the IfrScore
						file_IfrScore = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_IfrScore.size() + 1);

						// Extract the IfrRank
						file_IfrRank = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_IfrRank.size() + 1);

						// Extract the IsrScore
						file_IsrScore = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_IsrScore.size() + 1);

						// Extract the IsrRank
						file_IsrRank = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_IsrRank.size() + 1);

						// Extract the IrnScore
						file_IrnScore = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_IrnScore.size() + 1);

						// Extract the IrnRank
						file_IrnRank = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_IrnRank.size() + 1);

						// Extract the GerScore
						file_GerScore = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_GerScore.size() + 1);

						// Extract the GerRank
						file_GerRank = stod(remainingData.substr(0, remainingData.find(",")));
						remainingData.erase(0, file_GerRank.size() + 1);

						// Extract the ScoreScaled
						file_ScoreScaled = stod(remainingData);
					}


				}
			}

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

		rankingList.DisplayAllRankingInfo();

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
