#include "session_s.h"
#include"p_debug.h"
session_s::session_s(socket_packet* sp)
{
	this->sp = sp;
	this->b_login = false;
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