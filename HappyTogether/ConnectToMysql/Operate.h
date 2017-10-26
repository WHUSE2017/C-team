#pragma once
#include"SQLStruct.h"
#include"stdafx.h"
#include<vector>


class Operate {
public:
	Operate();

	string IntToString(int variable);
	int StringToInt(string variable);

	bool InsertIntoUserTable(userStruct User);
	bool InsertIntoEventNameTable(EventNameStruct Event);
	bool InsertIntoEventDetailsTable(EventDetailsStruct Event);
	bool InsertIntoStationMessageable(StationMessageStruct StationMessage);

	string GetPasswordFromUserTable(string username);
	userStruct GetUserDetails(string username);
	vector<EventDetailsStruct> GetEvent(string StartSite, string EndSite, string StartTime);
	vector<StationMessageStruct> GetMessageBySender(string SenderName);
	vector<StationMessageStruct> GetMessageByReceiver(string ReceiverName);
public:
	MYSQL mydata;
};
