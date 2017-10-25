#pragma once
#include<string>
using namespace std;
struct userStruct {
	string UserName;
	string PassWord;
	string StudentId;
	string Gender;
	string Image;
	string UserQQ;
	int Phone;
	string Email;
	string University;
	string LocateArea;
	string SelfTag;
	int PlayTime;
};

struct EventNameStruct {
	string EventType;
	string PlaySite;
	string Arrival;
};

struct EventDetailsStruct {
	int UserId;
	string Publisher;
	string StartSite;
	string EndSite;
	string StartTime;
	int PeersNUmber;
	int Success;
};

struct StationMessageStruct {
	string SenderName;
	string ReceiverName;
	string Message;
	string Time;
};