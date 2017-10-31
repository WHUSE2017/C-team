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
	bool InsertIntoEventTable(EventStruct Event);
	bool InsertIntoStationMessageable(StationMessageStruct StationMessage);

	string GetPasswordFromUserTable(string username);
	userStruct GetUserDetails(string username);
	vector<EventStruct> GetEvent(string StartSite, string EndSite, string StartTime, int UserId);
	vector<EventStruct> GetEventByState(int State);
	vector<string> GetParticipants(int EventId);
	bool joinEvent(int EventID,string username);
	bool setEventState(int Eventid, int State);
	vector<StationMessageStruct> GetMessageBySender(string SenderName);
	vector<StationMessageStruct> GetMessageByReceiver(string ReceiverName);
	EventStruct GetEventDetailById(int EventId);
public:
	MYSQL mydata;
};
