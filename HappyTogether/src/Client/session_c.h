#ifndef __SESSION__H__
#define __SESSION__H__
#include "socket_packet.h"
#include "request_reply.h"
#include "ConnectToMysql\SQLStruct.h"
#include<vector>
#include <iostream>
#include <string>
using namespace std;
class session_c
{
public:
	enum {
		disconected=-1,
		have_request=1,
	};
	session_c(socket_packet *sp);
	~session_c();
	bool login(char *params);
	bool _register(char* params);
	struct userStruct getUserInfo(char *params);
	int wait_reply();
	reply_t *get_reply();
	bool SendAndCheck(request_t *req);
	int getState(){return this->state;};
	bool addEvent(char* params);
	vector<StationMessageStruct> getStationMessage();
	bool addMessage(char *params);
	vector<EventStruct> getEvent(char* params);
	bool joinEvent(char * params);
	vector<string> getParticipants(char* params);
	EventStruct getEventByID(char* params);
	bool updatauserinfo(char* params);
private:
	int send_request(request_t *req);
	int state;
	socket_packet *sp;
	bool b_login;
	reply_t reply;
	char *buffer;
	int bufferlen;
};
#endif
