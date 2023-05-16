#include <fstream>
#include <iostream>
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
	// Constructor
	RankingList();

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
		double ScoreScaled);

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
		double ScoreScaled);

	// additional feature
	void DisplayAllRankingInfo(); // Big O - O(n)
};

RankingList::RankingList(){};

// Methods
Ranking* RankingList::CreateNewNode(
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

void RankingList::InsertToEndList(
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
		head = newnode;
	} else // if not empty list, just bring to the end of the list.
	{
		Ranking* current = head; // to help us find the last item in the list

		while (current->nextAddress != NULL) // if not yet last node, move to next point again
		{
			current = current->nextAddress; // Big O - O(n)
		}

		// if found the last node, attach the new node after the last node
		current->nextAddress = newnode;
	}
}

// additional feature
void RankingList::DisplayAllRankingInfo() // Big O - O(n)
{
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
