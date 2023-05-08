#ifndef TURS_H
#define TURS_H


//Customer 
struct Customer
{
	string custEmail;
	string custName;
	string custPassword;
	string custContactNo;
	string logoutTime;
	Customer* nextAddress;
	Customer* prevAddress;
};

class CustomerList
{
	Customer* head = NULL;
	Customer* tail = NULL;

public:
	//Constructor
	CustomerList();

	//Methods
	Customer* CreateNewNode(string custEmail, string custName, string custPassword, string custContactNo, string logoutTime);

	void InsertToEndList(string custEmail, string custName, string custPassword, string custContactNo, string logoutTime);

	void DisplayAllCustInfo(); //Big O - O(n)

	void ModifyCustInfo();

	bool DeleteCust(string email);
};


//University
struct University
{
	string universityID;
	string ranking;
	string universityName;
	string locationCode;
	string location;
	University* nextAddress;
	University* prevAddress;
};

class UniversityList
{
	University* head = NULL;
	University* tail = NULL;

public:
	//Constructor
	UniversityList();

	//Methods
	University* CreateNewNode(string universityID, string ranking, string universityName, string locationCode, string location);

	void InsertToEndList(string universityID, string ranking, string universityName, string locationCode, string location);

	void DisplayAllUniversityInfo(); //Big O - O(n)

	void SearchUniDetail(string universityName) {};

};


//Ranking
struct Ranking
{
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

class RankingList
{
	Ranking* head = NULL;
	Ranking* tail = NULL;

public:
	//Constructor
	RankingList();

	//Methods
	Ranking* CreateNewNode(string universityID, double ArScore, double ArRank, double ErScore, double ErRank, double FsrScore, double FsrRank, double CpfScore, double CpfRank, double IfrScore, double IfrRank, double IsrScore, double IsrRank, double IrnScore, double IrnRank, double GerScore, double GerRank, double ScoreScaled);

	void InsertToEndList(string universityID, double ArScore, double ArRank, double ErScore, double ErRank, double FsrScore, double FsrRank, double CpfScore, double CpfRank, double IfrScore, double IfrRank, double IsrScore, double IsrRank, double IrnScore, double IrnRank, double GerScore, double GerRank, double ScoreScaled);

	//additional feature
	void DisplayAllRankingInfo(); //Big O - O(n)
};


//Favourite
struct Favourite
{
	string favID;
	string custEmail;
	string universityID;
	Favourite* nextAddress;
	Favourite* prevAddress;
};

class FavouriteList
{
	Favourite* head = NULL;
	Favourite* tail = NULL;

public:
	//Constructor
	FavouriteList();

	//Methods
	Favourite* CreateNewNode(string favID, string custEmail, string universityID);

	void InsertToEndList(string favID, string custEmail, string universityID);

	//additional feature
	void DisplayAllFavInfo(); //Big O - O(n)

	//additional feature
	bool DeleteFav(string fav);

};


//Feedback
struct Feedback
{
	string feedbackID;
	string custEmail;
	string universityID;
	string feedback;
	string reply;
	Feedback* nextAddress;
	Feedback* prevAddress;
};

class FeedbackList
{
	Feedback* head = NULL;
	Feedback* tail = NULL;

public:
	//Constructor
	FeedbackList();

	//Methods
	Feedback* CreateNewNode(string feedbackID, string custEmail, string universityID, string feedback, string reply);

	void InsertToEndList(string feedbackID, string custEmail, string universityID, string feedback, string reply);

	//additional feature
	void DisplayAllFeedbackInfo(); //Big O - O(n)

	//additional feature
	void ReplylFeedback(); //Big O - O(n)
};


//Guest
class Guest {
public:
	Guest();
	void GuestMenu();
};
#endif