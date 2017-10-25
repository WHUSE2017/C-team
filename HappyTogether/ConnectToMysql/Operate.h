#pragma once
#include"SQLStruct.h"
#include<vector>


class Operate {
public:
	Operate();

	bool InsertIntoUserTable(userStruct user);
	bool InsertIntoEventNameTable(EventNameStruct Event);
	bool InsertIntoEventDetailsTable(EventDetailsStruct Event);
	bool InsertIntoStationMessageable(StationMessageStruct StationMessage);

	string GetPasswordFromUserTable(string username);
	vector<userStruct> GetUserDetails(string username);
	vector<EventDetailsStruct> GetEvent(string StartSite, string EndSite, string StartTime);
	vector<StationMessageStruct> GetMessageBySender(string SenderName);
	vector<StationMessageStruct> GetMessageByReceiver(string ReceiverName);
};
