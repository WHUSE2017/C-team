#ifndef _SERVER_THREAD_
#define _SERVER_THREAD_
#include"p_debug.h"
#include "session_s.h"
#include"utils.h"
#include "ConnectToMysql\SQLStruct.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
void pr_userStruct(userStruct user)
{
	cout<<user.UserName<<endl;
	cout<<user.PassWord<<endl;
	cout<<user.StudentId<<endl;
	cout<<user.Gender<<endl;
	cout<<user.Image<<endl;
	cout<<user.UserQQ<<endl;
	cout<<user.Phone<<endl;
	cout<<user.Email<<endl;
}

#define pr_req(req) p_debug("->new request\n  type=%d, flag=%d, len=%d, data=%s\n",req->type,req->flag,req->datalen,req->data)   
typedef struct
{
	int flag;
	session_s *session;
}ServerThreadParam;


void service_login(session_s *ses,request_t *req)
{
	if (req->type != TYPE_LOGIN )
		return ;
	char *data = req->data;
	char *key,*value;
	char *name ,*passwd;
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"username") ==0)
			name = value;
		else if (strcmp(key,"password") == 0)
			passwd = value;
		if (strlen(data)==0)
				break;
	}
	//p_debug("->\n	%s\n	%s\n",name,passwd);
	reply_t reply;
	reply.type=TYPE_LOGIN;
	reply.flag =11;
	string  strpwd=passwd;
	string strname=name;
	if (ses->op!=NULL && ses->op->GetPasswordFromUserTable(strname)==strpwd)
	{
		reply.data="success";
		reply.datalen =strlen("success")+1;	
	}
	else
	{
		reply.data="failed";
		reply.datalen=strlen("failed")+1;
	}
	ses->send_reply(&reply);
	ses->login_success(name);
}

void service_register(session_s * ses,request_t *req)
{
		if (req->type != TYPE_REGISTER )
			return ;
		char *data = req->data;
		char *key,*value;
		char *name ,*passwd;
		struct userStruct user;
		while ( (data=get_key_values(data,&key,&value)) !=NULL )
		{
			if (strcmp(key,"Email") ==0)
				user.Email = value;
			else if (strcmp(key,"Gender") == 0)
				user.Gender = value;
			else if (strcmp(key,"LocateArea") == 0)
				user.LocateArea = value;
			else if (strcmp(key,"Image") == 0)
				user.Image = value;
			else if (strcmp(key,"PassWord") == 0)
				user.PassWord = value;
			else if (strcmp(key,"Phone") == 0)
				user.Phone = value;
			else if (strcmp(key,"PassWord") == 0)
				user.PlayTime = Cs2Int(value);
			else if (strcmp(key,"SelfTag") == 0)
				user.SelfTag = value;
			else if (strcmp(key,"StudentId") == 0)
				user.StudentId = value;
			else if (strcmp(key,"University") == 0)
				user.University = value;
			else if (strcmp(key,"UserName") == 0)
				user.UserName = value;
			else if (strcmp(key,"UserQQ") == 0)
				user.UserQQ = value;
			if (strlen(data)==0)
					break;
		}
		//pr_userStruct(user);
		reply_t reply;
		reply.type=TYPE_REGISTER;
		reply.flag =1;
		if (ses->op!=NULL && ses->op->InsertIntoUserTable(user))
		{
			reply.data="success";
			reply.datalen =strlen("success")+1;
		}
		else
		{
			reply.data="failed";
			reply.datalen=strlen("failed")+1;
		}
		ses->send_reply(&reply);
}

void service_getuserinfo(session_s * ses,request_t *req)
{
	if (req->type != TYPE_GETUSERINFO )
		return ;
	char *data = req->data;
	char *key,*value;
	char *name =NULL;
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"username") ==0)
			name = value;
		if (strlen(data)==0)
				break;
	}
	p_debug("request user info: %s\n",name);
	string str_name =name;
	string bExist=ses->op->GetPasswordFromUserTable(str_name);
	
	reply_t reply;
	int bufferlen =2048;
	char buffer[2048];
	memset(buffer,0,2048);
	reply.type=TYPE_GETUSERINFO;
	reply.flag =-1;
	struct userStruct userInfo;
	if (bExist != "")
		userInfo = ses->op->GetUserDetails(str_name);
	if (name!=NULL && bExist!="")
	{
		reply.flag = 1;	
		params_strcat(buffer,"UserName",(char*)userInfo.UserName.data(),bufferlen);
		//params_strcat(buffer,"PassWord",(char*)userInfo.PassWord.data(),bufferlen);
		params_strcat(buffer,"StudentId",(char*)userInfo.StudentId.data(),bufferlen);
		params_strcat(buffer,"Gender",(char*)userInfo.Gender.data(),bufferlen);
		params_strcat(buffer,"Image",(char*)userInfo.Image.data(),bufferlen);
		params_strcat(buffer,"UserQQ",(char*)userInfo.UserQQ.data(),bufferlen);
		params_strcat(buffer,"Phone",(char*)userInfo.Phone.data(),bufferlen);
		params_strcat(buffer,"Email",(char*)userInfo.Email.data(),bufferlen);
		params_strcat(buffer,"University",(char*)userInfo.University.data(),bufferlen);
		params_strcat(buffer,"LocateArea",(char*)userInfo.LocateArea.data(),bufferlen);
		params_strcat(buffer,"SelfTag",(char*)userInfo.SelfTag.data(),bufferlen);
		params_strcat(buffer,"PlayTime",Int2Cs(userInfo.PlayTime),bufferlen);
		//p_debug("\n\n%s\n\n",buffer);
	}
		reply.data=buffer;
		reply.datalen =strlen(buffer)+1;
		ses->send_reply(&reply);
}

void service_addevent(session_s * ses,request_t *req)
{
	if (req->type != TYPE_ADDEVENT )
		return ;
	char *data = req->data;
	char *key,*value;
	char *name =NULL;
	struct EventStruct ev;
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"Arrival") ==0)
			ev.Arrival = value;
		else if (strcmp(key,"EndSite")==0)
			ev.EndSite = value;
		else if (strcmp(key,"EventID")==0)
			ev.EventID = Cs2Int(value);
		else if (strcmp(key,"EventType")==0)
			ev.EventType= value;
		else if (strcmp(key,"PeersNumber")==0)
			ev.PeersNumber= Cs2Int(value);
		else if (strcmp(key,"PlaySite")==0)
			ev.PlaySite= value;
		else if (strcmp(key,"Publisher")==0)
			ev.Publisher= value;
		else if (strcmp(key,"StartSite")==0)
			ev.StartSite= value;
		else if (strcmp(key,"StartTime")==0)
			ev.StartTime= value;
		else if (strcmp(key,"State")==0)
			ev.State= Cs2Int(value);
		else if (strcmp(key,"UserId")==0)
			ev.UserId= Cs2Int(value);
		if (strlen(data)==0)
				break;
	}
	ev.PeersNumber =1;
	reply_t reply;
	reply.type=TYPE_ADDEVENT;
	reply.flag =1;

	if (ses->op!=NULL && ses->op->InsertIntoEventTable(ev))
	{
		reply.data="success";
		reply.datalen =strlen("success")+1;
	}
	else
	{
			reply.data="failed";
			reply.datalen=strlen("failed")+1;
	}
	ses->send_reply(&reply);
}

void setMessageParams(char*buffer,int bufferlen ,StationMessageStruct mes)
{
	params_strcat(buffer,"SenderName",(char*)mes.SenderName.data(),bufferlen);
	params_strcat(buffer,"ReceiverName",(char*)mes.ReceiverName.data(),bufferlen);
	params_strcat(buffer,"Message",(char*)mes.Message.data(),bufferlen);
	params_strcat(buffer,"Time",(char*)mes.Time.data(),bufferlen);
}

void service_getmessages(session_s * ses,request_t *req)
{
	if (req->type != TYPE_GETMESSAGE )
		return ;
	char *data = req->data;
	char *key,*value;
	char *name =NULL;
	vector<StationMessageStruct> messages;
	string str_name = ses->getusername();
	if (ses->op!=NULL && ses->IsLogin())
	{
		messages=ses->op->GetMessageByReceiver(str_name);
	}
	vector<StationMessageStruct>::iterator iter = messages.begin();
	char buffer[2048];
	int bufferlen =2048;
	memset(buffer,0,bufferlen);
	for (;iter != messages.end() ;++iter)
	 {
	      StationMessageStruct mes = *iter;  // *iter就是vector的每个元素
		  setMessageParams(buffer,bufferlen,mes);
		  params_strcat(buffer,"END","END",bufferlen);
	 }
	
	params_strcat(buffer,"NULL","NULL",bufferlen);

	reply_t reply;
	reply.type=TYPE_GETMESSAGE;
	reply.flag =1;
	reply.data=buffer;
	reply.datalen =strlen(buffer)+1;
	ses->send_reply(&reply);
}

void service_addmessage(session_s * ses,request_t *req)
{
	if (req->type != TYPE_ADDMESSAGE )
		return ;
	char *data = req->data;
	char *key,*value;
	char *name =NULL;
	struct StationMessageStruct mes;
	mes.SenderName = ses->getusername();
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"Message") ==0)
			mes.Message = value;
		else if (strcmp(key,"ReceiverName")==0)
			mes.ReceiverName = value;
	//	else if (strcmp(key,"SenderName")==0)
		//	mes.SenderName = value;
		else if (strcmp(key,"Time")==0)
			mes.Time = value;
		if (strlen(data)==0)
				break;
	}
	
	reply_t reply;
	reply.type=TYPE_GETMESSAGE;
	reply.flag =1;
	if (ses->op!=NULL && 
		ses->op->InsertIntoStationMessageable(mes) && 
		mes.ReceiverName!=mes.SenderName &&
		ses->op->GetPasswordFromUserTable(mes.ReceiverName)!="")
	{
		reply.data="success";
		reply.datalen =strlen("success")+1;
	}
	else
	{
			reply.data="failed";
			reply.datalen=strlen("failed")+1;
	}

	ses->send_reply(&reply);
}

void setEventParams(char*buffer,int bufferlen ,EventStruct ee)
{
	params_strcat(buffer,"Arrival",(char*)ee.Arrival.data(),bufferlen);
	params_strcat(buffer,"EndSite",(char*)ee.EndSite.data(),bufferlen);
	params_strcat(buffer,"EventID",Int2Cs(ee.EventID),bufferlen);
	params_strcat(buffer,"EventType",(char*)ee.EventType.data(),bufferlen);
	params_strcat(buffer,"PeersNumber",Int2Cs(ee.PeersNumber),bufferlen);
	params_strcat(buffer,"PlaySite",(char*)ee.PlaySite.data(),bufferlen);
	params_strcat(buffer,"Publisher",(char*)ee.Publisher.data(),bufferlen);
	params_strcat(buffer,"StartSite",(char*)ee.StartSite.data(),bufferlen);
	params_strcat(buffer,"StartTime",(char*)ee.StartTime.data(),bufferlen);
	params_strcat(buffer,"State",Int2Cs(ee.State),bufferlen);
	params_strcat(buffer,"Arrival",Int2Cs(ee.UserId),bufferlen);
}

void service_getevent(session_s * ses,request_t *req)
{

	if (req->type != TYPE_GETEVENT )
		return ;
	char *data = req->data;
	char *key,*value;
	char *name =NULL;
	string StartSite="NULL";
	string EndSite="NULL";
	string StartTime="NULL";
	string EventType="NULL";
	int UserId=0;
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"StartSite") ==0)
			StartSite = value;
		else if (strcmp(key,"EndSite") ==0)
			EndSite = value;
		else if (strcmp(key,"StartTime") ==0)
			StartTime = value;
		else if (strcmp(key,"EventType") ==0)
			EventType = value;
		if (strlen(data)==0)
				break;
	}
	vector<EventStruct> es=ses->op->GetEvent(StartSite, EndSite, StartTime,EventType);
	vector<EventStruct>::iterator iter = es.begin();
	char buffer[2048];
	int bufferlen =2048;
	memset(buffer,0,bufferlen);
	for (;iter != es.end() ;++iter)
	 {
	      EventStruct ee = *iter;  // *iter就是vector的每个元素
		  setEventParams(buffer,bufferlen,ee);
		  params_strcat(buffer,"END","END",bufferlen);
	 }
	params_strcat(buffer,"NULL","NULL",bufferlen);
	reply_t reply;
	reply.type=TYPE_GETMESSAGE;
	reply.flag =1;
	reply.data=buffer;
	reply.datalen =strlen(buffer)+1;
	ses->send_reply(&reply);
}
void service_joinevent(session_s * ses,request_t *req)
{
	if (req->type != TYPE_JOINEVENT )
		return ;
	char *data = req->data;
	char *key,*value;
	int EventID;
	string str_name;
	int UserId=0;
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"EventID") ==0)
			EventID = Cs2Int(value);
		else if (strcmp(key,"username") ==0)
			str_name = value;
		if (strlen(data)==0)
				break;
	}
	str_name= ses->getusername();
	reply_t reply;
	reply.type=TYPE_JOINEVENT;
	reply.flag =1;
	if (ses->op!=NULL && ses->op->joinEvent(EventID,str_name))
	{
			reply.data="success";
			reply.datalen =strlen("success")+1;
	}
	else
	{
			reply.data="failed";
			reply.datalen=strlen("failed")+1;
	}
	ses->send_reply(&reply);
}



void service_getparticipants(session_s * ses,request_t *req)
{
	if (req->type != TYPE_GETPARTICIPANTS )
		return ;
	char *data = req->data;
	char *key,*value;

	int EventID=0;
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"EventID") ==0)
		{
			EventID = Cs2Int(value);
			break;
		}
		if (strlen(data)==0)
				break;
	}
	vector<string> ps=ses->op->GetParticipants(EventID);
	vector<string>::iterator iter = ps.begin();
	char buffer[2048];
	int bufferlen =2048;
	memset(buffer,0,bufferlen);
	for (;iter != ps.end() ;++iter)
	 {
	      string str = *iter;  // *iter就是vector的每个元素
		  params_strcat(buffer,"name",(char*)str.data(),bufferlen);
	 }
	params_strcat(buffer,"NULL","NULL",bufferlen);
	p_debug("\n\n\n%s\n\n\n",buffer);
	reply_t reply;
	reply.type=TYPE_GETPARTICIPANTS;
	reply.flag =1;
	reply.data=buffer;
	reply.datalen =strlen(buffer)+1;
	ses->send_reply(&reply);
}


void service_geteventdetail(session_s * ses,request_t *req)
{
	if (req->type != TYPE_GETEVENTDETAILBYID )
		return ;
	char *data = req->data;
	char *key,*value;
	char *name =NULL;
	int EventID=0;
	while ( (data=get_key_values(data,&key,&value)) !=NULL )
	{
		if (strcmp(key,"EventID") ==0)
			EventID = Cs2Int(value);
		if (strlen(data)==0)
				break;
	}
	EventStruct ee=ses->op->GetEventDetailById(EventID);

	char buffer[2048];
	int bufferlen =2048;
	memset(buffer,0,bufferlen);
	setEventParams(buffer,bufferlen,ee);

	reply_t reply;
	reply.type=TYPE_GETEVENTDETAILBYID;
	reply.flag =1;
	reply.data=buffer;
	reply.datalen =strlen(buffer)+1;
	ses->send_reply(&reply);
}

void service_updateuserinfo(session_s * ses,request_t *req)
{
		if (req->type != TYPE_UPDATEUSERINFO )
			return ;
		char *data = req->data;
		char *key,*value;
		char *name ,*passwd;
		struct userStruct user;
		while ( (data=get_key_values(data,&key,&value)) !=NULL )
		{
			if (strcmp(key,"Email") ==0)
				user.Email = value;
			else if (strcmp(key,"Gender") == 0)
				user.Gender = value;
			else if (strcmp(key,"LocateArea") == 0)
				user.LocateArea = value;
			else if (strcmp(key,"Image") == 0)
				user.Image = value;
			else if (strcmp(key,"PassWord") == 0)
				user.PassWord = value;
			else if (strcmp(key,"Phone") == 0)
				user.Phone = value;
			else if (strcmp(key,"PassWord") == 0)
				user.PlayTime = Cs2Int(value);
			else if (strcmp(key,"SelfTag") == 0)
				user.SelfTag = value;
			else if (strcmp(key,"StudentId") == 0)
				user.StudentId = value;
			else if (strcmp(key,"University") == 0)
				user.University = value;
			else if (strcmp(key,"UserName") == 0)
				user.UserName = value;
			else if (strcmp(key,"UserQQ") == 0)
				user.UserQQ = value;
			if (strlen(data)==0)
					break;
		}
		//pr_userStruct(user);
		reply_t reply;
		reply.type=TYPE_UPDATEUSERINFO;
		reply.flag =1;
		if (ses->op!=NULL && ses->op->UpdateUserTable(user))
		{
			reply.data="success";
			reply.datalen =strlen("success")+1;
		}
		else
		{
			reply.data="failed";
			reply.datalen=strlen("failed")+1;
		}
		ses->send_reply(&reply);
}

void service_exitevent(session_s * ses,request_t *req)
{
	if (req->type != TYPE_EXITEVENT )
			return ;
		char *data = req->data;
		char *key,*value;
		string str_name;
		int EventID=0;
		while ( (data=get_key_values(data,&key,&value)) !=NULL )
		{
			if (strcmp(key,"EventID")==0)
				EventID=Cs2Int(value);
			else if (strcmp(key,"username")==0)
				str_name = value;
			if (strlen(data)==0)
					break;
		}
		//pr_userStruct(user);
		reply_t reply;
		reply.type=TYPE_EXITEVENT;
		reply.flag =1;
		if (ses->op!=NULL && ses->op->DeleteDataParticipants(EventID,str_name))
		{
			reply.data="success";
			reply.datalen =strlen("success")+1;
		}
		else
		{
			reply.data="failed";
			reply.datalen=strlen("failed")+1;
		}
		ses->send_reply(&reply);
}

void service_seteventstate(session_s * ses,request_t *req)
{
	if (req->type != TYPE_SETEVENTSTATE )
			return ;
		char *data = req->data;
		char *key,*value;
		int EventID=0,state;
		while ( (data=get_key_values(data,&key,&value)) !=NULL )
		{
			if (strcmp(key,"EventID")==0)
				EventID=Cs2Int(value);
			else if (strcmp(key,"state")==0)
				state = Cs2Int(value);
			if (strlen(data)==0)
					break;
		}
		EventStruct es = ses->op->GetEventDetailById(EventID);
		string str_name =ses->getusername();

		//pr_userStruct(user);
		reply_t reply;
		reply.type=TYPE_SETEVENTSTATE;
		reply.flag =1;
		if (es.Publisher == str_name  && ses->op->setEventState(EventID,state))
		{
			reply.data="success";
			reply.datalen =strlen("success")+1;
		}
		else
		{
			reply.data="failed";
			reply.datalen=strlen("failed")+1;
		}
		ses->send_reply(&reply);
}


void service_geteventbycondition(session_s * ses,request_t *req)
{
	if (req->type != TYPE_GETEVENTBYCONDITIONS )
			return ;
		char *data = req->data;
		char *key,*value;
		string str_publisher,str_participant;
		int state;

		while ( (data=get_key_values(data,&key,&value)) !=NULL )
		{
			if (strcmp(key,"publisher")==0)
				str_publisher=Cs2Int(value);
			else if (strcmp(key,"participant")==0)
				str_participant = value;
			else if (strcmp(key,"state"))
				state = Cs2Int(value);		
			if (strlen(data)==0)
					break;
		}
	
	vector<EventStruct> es=ses->op->getEventByCondition(str_publisher, str_participant, state);
	vector<EventStruct>::iterator iter = es.begin();
	char buffer[2048];
	int bufferlen =2048;
	memset(buffer,0,bufferlen);
	for (;iter != es.end() ;++iter)
	 {
	      EventStruct ee = *iter;  // *iter就是vector的每个元素
		  setEventParams(buffer,bufferlen,ee);
		  params_strcat(buffer,"END","END",bufferlen);
	 }
	params_strcat(buffer,"NULL","NULL",bufferlen);
	reply_t reply;
	reply.type=TYPE_GETEVENTBYCONDITIONS;
	reply.flag =1;
	reply.data=buffer;
	reply.datalen =strlen(buffer)+1;
	ses->send_reply(&reply);
}

void service_setsecurity(session_s * ses,request_t *req)
{
	if (req->type != TYPE_SETSECURITY )
			return ;
		char *data = req->data;
		char *key,*value;
		string str_name,str_security,str_answer;
		SecretSecurityStruct sec;
	
		while ( (data=get_key_values(data,&key,&value)) !=NULL )
		{
			if (strcmp(key,"security")==0)
				sec.Security = value;
			else if (strcmp(key,"username")==0)
				sec.UserName = value;
			else if (strcmp(key,"answer"))
				sec.Answer = value;
			if (strlen(data)==0)
					break;
		}
		//sec.UserName = ses->getusername();
		reply_t reply;
		reply.type=TYPE_SETSECURITY;
		reply.flag =1;
		if (ses->op!=NULL && ses->op->InsertIntoSecretSecurity(sec))
		{
			reply.data="success";
			reply.datalen =strlen("success")+1;
		}
		else
		{
			reply.data="failed";
			reply.datalen=strlen("failed")+1;
		}
		ses->send_reply(&reply);
}

void service_getsecurity(session_s * ses,request_t *req)
{
	if (req->type != TYPE_GETSECURITY )
			return ;
		char *data = req->data;
		char *key,*value;
			string str_name,str_security,str_answer;

	while ( (data=get_key_values(data,&key,&value)) !=NULL )
		{
			if (strcmp(key,"security")==0)
				str_security = value;
			else if (strcmp(key,"username")==0)
				str_name = value;
			else if (strcmp(key,"answer"))
				str_answer = value;
			if (strlen(data)==0)
					break;
		}
	
		SecretSecurityStruct sec = ses->op->GetSecretSecurity(str_name);

		char buffer[2048];
		int bufferlen = 2048;
		params_strcat(buffer,"security",(char*)sec.Security.data(),bufferlen);
		reply_t reply;
		reply.type=TYPE_GETSECURITY;
		reply.flag =1;
		reply.data = buffer;
		reply.datalen = strlen(buffer)+1;
		ses->send_reply(&reply);
}

void service_checksecurity(session_s * ses,request_t *req)
{
	if (req->type != TYPE_CHECKSECURITY )
			return ;
		char *data = req->data;
		char *key,*value;
		SecretSecurityStruct sec;
		while ( (data=get_key_values(data,&key,&value)) !=NULL )
		{
			if (strcmp(key,"security")==0)
				sec.Security = value;
			else if (strcmp(key,"username")==0)
				sec.UserName = value;
			else if (strcmp(key,"answer"))
				sec.Answer = value;
			if (strlen(data)==0)
					break;
		}
		
		SecretSecurityStruct sec2 = ses->op->GetSecretSecurity(sec.UserName);
		reply_t reply;
		reply.type=TYPE_CHECKSECURITY;
		reply.flag =1;
		if (sec.UserName == sec2.UserName &&
			sec.Security == sec2.Security &&
			sec.Answer == sec2.Answer)
		{
			reply.data="success";
			reply.datalen =strlen("success")+1;
		}
		else
		{
			reply.data="failed";
			reply.datalen=strlen("failed")+1;
		}
		ses->send_reply(&reply);
}


DWORD WINAPI myServerThread(LPVOID lpParam)
{
	ServerThreadParam *lp =(ServerThreadParam*)lpParam;
	session_s *s = lp->session;
	while(1)
	{
		int state = s->wait_request();
		if (state == s->disconected)
			break;
		request_t * req = s->get_request();

		p_debug("->new request\n  type=%d, flag=%d, len=%d, data=%s\n",
					req->type,req->flag,req->datalen,req->data);
		switch(req->type)
		{
		case (TYPE_LOGIN):
			{
				service_login(s,req);
				break;
			}
		case(TYPE_REGISTER):
			{
				service_register(s,req);
				break;
			}
		case(TYPE_GETUSERINFO):
			{
				service_getuserinfo(s,req);
				break;
			}
		case(TYPE_ADDEVENT):
			{
				service_addevent(s,req);
				break;
			}
		case(TYPE_GETMESSAGE):
			{	
				service_getmessages(s,req);
				break;
			}
		case(TYPE_ADDMESSAGE):
			{
				service_addmessage(s,req);
				break;
			}
		case(TYPE_GETEVENT):
			{
				service_getevent(s,req);
				break;
			}
		case(TYPE_JOINEVENT):
		{
			service_joinevent(s,req);
			break;
		}
		case(TYPE_GETPARTICIPANTS):
		{
			service_getparticipants(s,req);
			break;
		}
		case(TYPE_GETEVENTDETAILBYID):
			{
				service_geteventdetail(s,req);
				break;
			}
		case(TYPE_UPDATEUSERINFO):
			{
				service_updateuserinfo(s,req);
				break;
			}
		case(TYPE_EXITEVENT):
			{
				service_exitevent(s,req);
				break;
			}
		case(TYPE_SETEVENTSTATE):
			{
				service_seteventstate(s,req);
				break;
			}
		case(TYPE_GETEVENTBYCONDITIONS):
			{
				service_geteventbycondition(s,req);
				break;
			}
		case(TYPE_SETSECURITY):
			{
				service_setsecurity(s,req);
				break;
			}
		default:
			break;
		}
	}
	return 0;
}

#endif