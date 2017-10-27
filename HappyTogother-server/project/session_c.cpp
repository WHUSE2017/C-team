#include "session_c.h"
#include "p_debug.h"
#include <string.h>
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
	return 0;
}


bool session_c::login(char *username,char*pass)
{
	char buf[128];
	memset(buf,0,128);
	//if (strlen(username)>16 || strlen(pass)>32 || strlen(pass)<8)
		//return false;
	strcpy(buf,"name=");
	strcat(buf,username);
	strcat(buf,",password=");
	strcat(buf,pass);
	request_t req;
	req.type = 11;
	req.flag =0;
	req.data = buf;
	req.datalen = strlen(buf)+1;
	
	this->send_request(&req);
	return true;
}