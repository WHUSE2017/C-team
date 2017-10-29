#ifndef __SQL__STRUCT__H__
#define __SQL__STRUCT__H__
#pragma once
#include<string>
using namespace std;
struct userStruct {
	int UserID;
	string UserName;
	string PassWord;
	int StudentId;
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
	int State;//1,完成  2，取消  3， 进行  或者按照你自己定义
};

struct StationMessageStruct {
	int MessageID;
	string SenderName;
	string ReceiverName;
	string Message;
	string Time;
};

#endif