#include "session_s.h"
#include"p_debug.h"
session_s::session_s(socket_packet* sp)
{
	this->sp = sp;
	this->b_login = false;
	this->reply_buffer = NULL;
	this->reply_buffer_len = 0;
	this->op =NULL;
}

session_s::~session_s()
{
	this->sp->~socket_packet();
}

int session_s::wait_request()
{
	int ret = this->sp->recv_packet();
	if (ret>0)
		return this->have_request;
	return this->disconected;
}

request_t* session_s::get_request()
{
	packet_t *packet = (packet_t *)(this->sp->get_buffer());
	request.type = packet->type;
	request.flag = packet->flag;
	request.data = packet->data;
	request.datalen = packet->length-(sizeof(packet_t)-sizeof(char));
	return &request;
}

bool session_s::send_reply(reply_t *reply)
{
	int size = sizeof(request_t)-sizeof(char*)+reply->datalen;
	if (reply_buffer == NULL || reply_buffer_len< size)
	{
		if (reply_buffer) 
			free(reply_buffer);
		reply_buffer=(char*)malloc(size);
		reply_buffer_len = size;
	}
	packet_t *packet = (packet_t*)reply_buffer;
	packet->type = reply->type;
	packet->flag = reply->flag;
	packet->length = reply->datalen + sizeof(packet_t)-sizeof(char);
	memcpy(packet->data,reply->data,reply->datalen);
	int ret = this->sp->send_packet(packet,packet->length);
	return 0;
}

void session_s::login_success(char*name )
{
	if (strlen(name)>sizeof(this->username)+1)
		return ;
	strcpy(this->username,name); 
	this->b_login = true;
}