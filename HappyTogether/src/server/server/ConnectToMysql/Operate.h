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
	bool joinEvent(int EventID, string username);
	bool setEventState(int Eventid, int State);//设置活动状态
	string GetSecretSecurity(string UserName);

	bool DeleteDataParticipants(int EventID, string UserName);//删除Participants中特定数据

	vector<userStruct> LikeUserName(string username);//模糊查找用户名

	string GetPasswordFromUserTable(string username);
	userStruct GetUserDetails(string username);
	vector<EventStruct> GetEvent(string StartSite, string EndSite, string StartTime, string EventType);
	vector<EventStruct> GetEventByState(int State);//通过活动状态查询活动
	vector<EventStruct> GetEventByLike(string StartSite, string EndSite);//开始地和结束地模糊查询
	vector<string> GetParticipants(int EventId);
	
	vector<StationMessageStruct> GetMessageBySender(string SenderName);
	vector<StationMessageStruct> GetMessageByReceiver(string ReceiverName);
	EventStruct GetEventDetailById(int EventId);
public:
	MYSQL mydata;
};
