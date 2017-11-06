#ifndef __USERCLIENT__H__
#define __USERCLIENT__H__
#include "session_c.h"
#include <iostream>
#include <vector>
using namespace std;
class UserClient
{
public:
	UserClient(char *ip, unsigned short port);
	bool Login(char *name,char* password);
	bool Register(struct userStruct userInfo);
	int getState(){return this->state;};
	bool reConnect();
	bool fisrtConnect();
	struct userStruct getUserInfo(char* username);
	bool addEvent(EventStruct Event);
	bool sendMessage(StationMessageStruct message);
	vector<StationMessageStruct> getStationMessage();
        vector<EventStruct> getEvent(string StartSite, string EndSite, string StartTime,string EventType);
	bool joinEvent(int EventID, string username);
	vector<string> getParticipants(int EventID);
	EventStruct getEventById(int EventID);
	void Logout();
	bool UpdateUserInfo(struct userStruct userInfo);
        bool ExitEvent(int EventID,string username);
        bool SetEventState(int EventID,int state);
        vector<EventStruct> getEventByConditions(string publisher,string participant,int state);
        bool SetSecurity(string username,string sercurity,string answer);
        string GetSecurity(string username);
        string CheckSecurity(string username,string security,string answer);
private:
	int state;
	session_c* sc;
	char mIp[16];
	unsigned short mPort;
	char *buffer;
	int bufferlen;
};
#endif
