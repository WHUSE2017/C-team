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
	bool UpdateUserTable(userStruct User);//不能修改密码和修改游玩次数
	bool UpdatePassword(string UserName, string Password);
	bool InsertIntoSecretSecurity(SecretSecurityStruct Security);

	string GetSecretSecurity(string UserName);

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
