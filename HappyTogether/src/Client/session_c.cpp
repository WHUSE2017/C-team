#include "session_c.h"
#include "p_debug.h"
#include <string>
#include"utils.h"
#include <iostream>
using namespace std;
session_c::session_c(socket_packet* sp)
{
	this->sp = sp;
	this->b_login = false;
	this->buffer = NULL;
	this->bufferlen = 0;
}

session_c::~session_c()
{
	this->sp->~socket_packet();
}

int session_c::wait_reply()
{
	int ret = this->sp->recv_packet();
	if (ret>0)
		return this->have_request;
	this->state = this->disconected;
	return this->disconected;
}

reply_t * session_c::get_reply()
{
	packet_t *packet = (packet_t *)(this->sp->get_buffer());
	reply.type = packet->type;
	reply.flag = packet->flag;
	reply.data = packet->data;
	reply.datalen = packet->length-(sizeof(packet_t)-sizeof(char));
	return &reply;
}


int session_c::send_request(request_t* req)
{
	int size = sizeof(request_t)-sizeof(char*)+req->datalen;
	if (buffer == NULL || bufferlen< size)
	{
		if (buffer) 
			free(buffer);
		buffer=(char*)malloc(size);
		bufferlen = size;
	}
	packet_t *packet = (packet_t*)buffer;
	packet->type = req->type;
	packet->flag = req->flag;
	packet->length = req->datalen + sizeof(packet_t)-sizeof(char);
	memcpy(packet->data,req->data,req->datalen);
	int ret = this->sp->send_packet(packet,packet->length);
	return ret;
}


bool session_c::SendAndCheck(request_t *req)
{
	if (this->send_request(req)<0)
	{
		p_debug("send request error!\n");
		return false;
	}
	if (this->wait_reply() == this->disconected)
	{
		p_debug("disconnected!\n");
		return false;
	}
	return true;
}

bool session_c::login(char *params)
{

	request_t req;
	req.type = TYPE_LOGIN;
	req.flag =0;
	req.data = params;
	req.datalen = strlen(params)+1;
	
	if (!SendAndCheck(&req))
		return false;
	reply_t *reply = this->get_reply();
	if (strcmp(reply->data,"success")==0)
	{

		this->b_login= true;
		return true;
	}
	return false;
}

bool session_c::_register(char* params)
{
	request_t req;
	req.type = TYPE_REGISTER;
	req.flag =0;
	req.data = params;
	req.datalen = strlen(params)+1;
	if (!SendAndCheck(&req))
		return false;
	reply_t *reply = this->get_reply();
	if (strcmp(reply->data,"success")==0)
	{
		return true;
	}
	return false;

}

bool session_c::updatauserinfo(char* params)
{
	request_t req;
	req.type = TYPE_UPDATEUSERINFO;
	req.flag =0;
	req.data = params;
	req.datalen = strlen(params)+1;
	if (!SendAndCheck(&req))
		return false;
	reply_t *reply = this->get_reply();
	if (strcmp(reply->data,"success")==0)
	{
		return true;
	}
	return false;

}

struct userStruct session_c::getUserInfo(char* params)
{
	struct userStruct user; 
	user.UserName="";
	request_t req;
	req.type = TYPE_GETUSERINFO;
	req.flag =0;
	req.data = params;
	req.datalen = strlen(params)+1;
	if (!SendAndCheck(&req))
		return user;
	reply_t *reply = this->get_reply();
	
	if (reply->type != TYPE_GETUSERINFO )
		return user;

	char *data = reply->data;
	char *key,*value;
	
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"UserName") ==0)
			user.UserName = (value);
		else if (strcmp(key,"StudentId") == 0)
			user.StudentId = (value);
		else if (strcmp(key,"Gender") == 0)
			user.Gender = value;
		else if (strcmp(key,"UserQQ") == 0)
			user.UserQQ = value;
		else if (strcmp(key,"Phone") == 0)
			user.Phone = (value);
		else if (strcmp(key,"Email") == 0)
			user.Email = value;
		else if (strcmp(key,"University") == 0)
			user.University = value;
		else if (strcmp(key,"LocateArea") == 0)
			user.LocateArea = value;
		else if (strcmp(key,"SelfTag") == 0)
			user.SelfTag = value;
		else if (strcmp(key,"PlayTime") == 0)
			user.PlayTime = Cs2Int(value);
		else if (strcmp(key,"Image") == 0)
			user.Image = value;
		if (strlen(data)==0)
				break;
	}
	
	return user;
}


bool session_c::addEvent(char* params)
{
	request_t req;
	req.type = TYPE_ADDEVENT;
	req.flag =0;
	req.data = params;
	req.datalen = strlen(params)+1;
	if (!SendAndCheck(&req))
		return false;
	reply_t *reply = this->get_reply();
	if (strcmp(reply->data,"success")==0)
	{
		return true;
	}
	return false;
}

vector<StationMessageStruct> session_c::getStationMessage()
{
	vector<StationMessageStruct> messages;
	request_t req;
	req.type = TYPE_GETMESSAGE;
	req.flag =0;
	req.data="getmessages";
	req.datalen = strlen("getmessages");
	if (!SendAndCheck(&req))
		return messages;
	reply_t *reply = this->get_reply();
	char *data = reply->data;
	char *key,*value;
	StationMessageStruct mes ;
	int i=0;
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"NULL") == 0 && strcmp(value,"NULL")==0)
			break;
		if (strcmp(key,"END") == 0 && strcmp(value,"END")==0)
		{
			messages.push_back(mes);
			continue;
		}
		if (strcmp("Message",key)==0)
			mes.Message = value;
		if (strcmp("ReceiverName",key)==0)
			mes.ReceiverName = value;
		if (strcmp("SenderName",key)==0)
			mes.SenderName = value;
		if (strcmp("Time",key)==0)
			mes.Time = value;

		if (strlen(data)==0)
				break;
	}
	return messages;
}

bool session_c::addMessage(char* params)
{
	request_t req;
	req.type = TYPE_ADDMESSAGE;
	req.flag =0;
	req.data = params;
	req.datalen = strlen(params)+1;
	if (!SendAndCheck(&req))
		return false;
	reply_t *reply = this->get_reply();
	if (strcmp(reply->data,"success")==0)
	{
		return true;
	}
	return false;
}

vector<EventStruct> session_c::getEvent(char* params)
{
	vector<EventStruct> es;
	request_t req;
	req.type = TYPE_GETEVENT;
	req.flag =0;
	req.data = params;
	req.datalen = strlen(params)+1;
	if (!SendAndCheck(&req))
		return es;
	
	reply_t *reply = this->get_reply();
	char *data = reply->data;
	char *key,*value;
	EventStruct ee ;
	int i=0;
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"NULL") == 0 && strcmp(value,"NULL")==0)
			break;
		if (strcmp(key,"END") == 0 && strcmp(value,"END")==0)
		{
			es.push_back(ee);
			continue;
		}
		if (strcmp("Arrival",key)==0)
			ee.Arrival = value;
		else if (strcmp("EndSite",key)==0)
			ee.EndSite = value;
		else if (strcmp("EventID",key)==0)
			ee.EventID = Cs2Int(value);
		else if (strcmp("EventType",key)==0)
			ee.EventType = value;
		else if (strcmp("PeersNumber",key)==0)
			ee.PeersNumber = Cs2Int(value);
		else if (strcmp("PlaySite",key)==0)
			ee.PlaySite = value;
		else if (strcmp("Publisher",key)==0)
			ee.Publisher = value;
		else if (strcmp("StartSite",key)==0)
			ee.StartSite = value;
		else if (strcmp("StartTime",key)==0)
			ee.StartTime = value;
		else if (strcmp("State",key)==0)
			ee.State = Cs2Int(value);
		else if (strcmp("UserId",key)==0)
			ee.UserId = Cs2Int(value);

		if (strlen(data)==0)
				break;
	}
	return es;
}

bool session_c::joinEvent(char * params)
{
	request_t req;
	req.type = TYPE_JOINEVENT;
	req.flag =0;
	req.data = params;
	req.datalen = strlen(params)+1;
	if (!SendAndCheck(&req))
		return false;
	reply_t *reply = this->get_reply();
	if (strcmp(reply->data,"success")==0)
	{
		return true;
	}
	return false;
}

vector<string> session_c::getParticipants(char* params)
{
	vector<string> ret;
	request_t req;
	req.type = TYPE_GETPARTICIPANTS;
	req.flag =0;
	req.data = params;
	req.datalen = strlen(params)+1;
	if (!SendAndCheck(&req))
		return ret;
	reply_t *reply = this->get_reply();
	char *data = reply->data;
	char *key,*value;
	
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"NULL") == 0 && strcmp(value,"NULL")==0)
			break;
		if (strcmp(key,"name") == 0 )
		{
			string stemp = value;
			ret.push_back(stemp);
		}
		if (strlen(data)==0)
				break;
	}
	return ret;
}

EventStruct session_c::getEventByID(char* params)
{
	EventStruct es;
	request_t req;
	req.type = TYPE_GETEVENTDETAILBYID;
	req.flag =0;
	req.data = params;
	req.datalen = strlen(params)+1;
	if (!SendAndCheck(&req))
		return es;
	
	reply_t *reply = this->get_reply();
	char *data = reply->data;
	char *key,*value;
	EventStruct ee ;
	int i=0;
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"NULL") == 0 && strcmp(value,"NULL")==0)
			break;
		if (strcmp("Arrival",key)==0)
			ee.Arrival = value;
		else if (strcmp("EndSite",key)==0)
			ee.EndSite = value;
		else if (strcmp("EventID",key)==0)
			ee.EventID = Cs2Int(value);
		else if (strcmp("EventType",key)==0)
			ee.EventType = value;
		else if (strcmp("PeersNumber",key)==0)
			ee.PeersNumber = Cs2Int(value);
		else if (strcmp("PlaySite",key)==0)
			ee.PlaySite = value;
		else if (strcmp("Publisher",key)==0)
			ee.Publisher = value;
		else if (strcmp("StartSite",key)==0)
			ee.StartSite = value;
		else if (strcmp("StartTime",key)==0)
			ee.StartTime = value;
		else if (strcmp("State",key)==0)
			ee.State = Cs2Int(value);
		else if (strcmp("UserId",key)==0)
			ee.UserId = Cs2Int(value);

		if (strlen(data)==0)
				break;
	}
	es=ee;
	return es;
}

 bool session_c::exitEvent(char *params)
 {
     request_t req;
     req.type = TYPE_EXITEVENT;
     req.flag =0;
     req.data = params;
     req.datalen = strlen(params)+1;
     if (!SendAndCheck(&req))
             return false;
     reply_t *reply = this->get_reply();
     if (strcmp(reply->data,"success")==0)
     {
             return true;
     }
     return false;

 }

bool session_c::setEventState(char *params)
{
    request_t req;
    req.type = TYPE_SETEVENTSTATE;
    req.flag =0;
    req.data = params;
    req.datalen = strlen(params)+1;
    if (!SendAndCheck(&req))
            return false;
    reply_t *reply = this->get_reply();
    if (strcmp(reply->data,"success")==0)
    {
            return true;
    }
    return false;
}
