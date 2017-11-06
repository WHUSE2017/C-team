#pragma once
#include<string>
using namespace std;
struct userStruct {
	int UserID;
	string UserName;
	string PassWord;
	string StudentId;
	string Gender;
	string Image;
	string UserQQ;
	string Phone;
	string Email;
	string University;
	string LocateArea;
	string SelfTag;
	int PlayTime;
};

struct EventStruct {
	int EventID;
	string EventType;
	string PlaySite;
	string Arrival;
	int UserId;
	string Publisher;
	string StartSite;
	string EndSite;
	string StartTime;
	int PeersNumber;
	int State;//
};

struct StationMessageStruct {
	int MessageID;
	string SenderName;
	string ReceiverName;
	string Message;
	string Time;
};

struct ParticipantsStrcut {
	int EventID;
	string UserName;
};

struct SecretSecurityStruct {
	int SecretSecurityID;
	string UserName;
	string Security;
	string Answer;
};