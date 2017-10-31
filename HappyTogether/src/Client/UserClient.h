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
	vector<EventStruct> getEvent(string StartSite, string EndSite, string StartTime,int UserId);
	bool joinEvent(int EventID, string username);
	vector<string> getParticipants(int EventID);
	EventStruct getEventById(int EventID);
	void Logout();
private:
	int state;
	session_c* sc;
	char mIp[16];
	unsigned short mPort;
	char *buffer;
	int bufferlen;
};
#endif