#include "UserClient.h"
#include "utils.h"
UserClient::UserClient(char *ip, unsigned short port)
{
	//this->sc = new session_c(new socket_packet(new socket_stream(ip,port)));
	this->sc=NULL;
	strcpy(mIp,ip);
	mPort= port;
	this->buffer = (char*)malloc(2048);
	this->bufferlen = 2048;
}

bool UserClient::fisrtConnect()
{
	if (this->sc==NULL)
		this->sc = new session_c(new socket_packet(new socket_stream(mIp,mPort)));
	return true;
}

bool UserClient::Login(char *name,char* password)
{
	this->reConnect();
	if (buffer==NULL) return false;
	memset(buffer,0,this->bufferlen);
	params_strcat(buffer,"username",name,bufferlen);
	params_strcat(buffer,"password",password,bufferlen);
	bool bret = this->sc->login(buffer);
	if (sc->getState() == sc->disconected)
		this->state =-1;
	return bret;
}

void UserClient::Logout()
{
	this->sc->~session_c();
	this->sc=NULL;
}

bool UserClient::reConnect()
{
	if(sc!=NULL && sc->getState()!=sc->disconected)
		return true;
	sc = this->sc = new session_c(new socket_packet(new socket_stream(mIp,mPort)));
}

bool UserClient::Register(struct userStruct userInfo)
{
	this->reConnect();
	if (buffer==NULL) return false;
	memset(buffer,0,this->bufferlen);
	params_strcat(buffer,"UserName",(char*)userInfo.UserName.data(),bufferlen);
	params_strcat(buffer,"PassWord",(char*)userInfo.PassWord.data(),bufferlen);
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
	return this->sc->_register(buffer);
}

void pr2_userStruct(userStruct user)
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

struct userStruct UserClient::getUserInfo(char *username)
{
	this->reConnect();
	struct userStruct  user;
	if (buffer==NULL) return user;
	memset(buffer,0,this->bufferlen);
	params_strcat(buffer,"username",username,bufferlen);
	user = this->sc->getUserInfo(buffer);
	return user;
}



bool UserClient::addEvent(EventStruct Event)
{
	this->reConnect();
	if (buffer==NULL) return false;
	memset(buffer,0,this->bufferlen);
	params_strcat(buffer,"Arrival",(char*)Event.Arrival.data(),bufferlen);
	params_strcat(buffer,"EndSite",(char*)Event.EndSite.data(),bufferlen);
	params_strcat(buffer,"EventID",Int2Cs(Event.EventID),bufferlen);
	params_strcat(buffer,"EventType",(char*)Event.EventType.data(),bufferlen);
	params_strcat(buffer,"PeersNumber",Int2Cs(Event.PeersNumber),bufferlen);
	params_strcat(buffer,"PlaySite",(char*)Event.PlaySite.data(),bufferlen);
	params_strcat(buffer,"Publisher",(char*)Event.Publisher.data(),bufferlen);
	params_strcat(buffer,"StartSite",(char*)Event.StartSite.data(),bufferlen);
	params_strcat(buffer,"StartTime",(char*)Event.StartTime.data(),bufferlen);
	params_strcat(buffer,"State",Int2Cs(Event.State),bufferlen);
	params_strcat(buffer,"UserId",Int2Cs(Event.UserId),bufferlen);

	if (this->sc->addEvent(buffer))
		return true;	
	return false;
}

vector<StationMessageStruct> UserClient::getStationMessage()
{
	this->reConnect();
	return this->sc->getStationMessage();
}

bool UserClient::sendMessage(StationMessageStruct message)
{
	this->reConnect();
	if (buffer==NULL) return false;
	memset(buffer,0,this->bufferlen);
	params_strcat(buffer,"Message",(char*)message.Message.data(),bufferlen);
	params_strcat(buffer,"ReceiverName",(char*)message.ReceiverName.data(),bufferlen);
	params_strcat(buffer,"SenderName",(char*)message.SenderName.data(),bufferlen);
	params_strcat(buffer,"Time",(char*)message.Time.data(),bufferlen);
	return this->sc->addMessage(buffer);
}

vector<EventStruct> UserClient::getEvent(string StartSite, string EndSite, string StartTime,int UserId)
{
	this->reConnect();
	vector<EventStruct> es;
	if (buffer==NULL) return es;
	memset(buffer,0,this->bufferlen);
	params_strcat(buffer,"StartSite",(char*)StartSite.data(),bufferlen);
	params_strcat(buffer,"EndSite",(char*)EndSite.data(),bufferlen);
	params_strcat(buffer,"StartTime",(char*)StartTime.data(),bufferlen);
	params_strcat(buffer,"UserId",Int2Cs(UserId),bufferlen);
	return this->sc->getEvent(buffer);
}

bool UserClient::joinEvent(int EventID, string username)
{
	this->reConnect();
	if (buffer==NULL) return false;
	memset(buffer,0,this->bufferlen);
	params_strcat(buffer,"EventID",Int2Cs(EventID),bufferlen);
	params_strcat(buffer,"username",(char*)username.data(),bufferlen);
	return this->sc->joinEvent(buffer);
}

vector<string> UserClient::getParticipants(int EventID)
{
	this->reConnect();
	vector<string> ret;
	if (buffer==NULL) return ret;
	memset(buffer,0,this->bufferlen);
	params_strcat(buffer,"EventID",Int2Cs(EventID),bufferlen);
	ret = this->sc->getParticipants(buffer);
	return ret;
}

EventStruct UserClient::getEventById(int EventID)
{
	this->reConnect();
	EventStruct ee;
	if (buffer==NULL) return ee;
	memset(buffer,0,this->bufferlen);
	params_strcat(buffer,"EventID",Int2Cs(EventID),bufferlen);
	ee =this->sc->getEventByID(buffer);
	return ee;
}