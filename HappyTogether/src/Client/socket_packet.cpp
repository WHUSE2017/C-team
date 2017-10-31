#include "socket_packet.h"
#include"p_debug.h"

socket_packet::socket_packet (socket_stream *stream)
{
	this->mStream  =  stream;
	this->buffer = NULL;
	this->bufLength = 0;
}
socket_packet::~socket_packet()
{
	this->mStream->~socket_stream();
	if(this->buffer!=NULL)
		free(this->buffer);
}

int socket_packet::send_packet(packet_t *packet,int length)
{
	int ret = this->mStream->sendData((char*)packet,length);
	return ret;
}

int socket_packet::recv_packet()
{
	int ret;
        int m;
	int size = sizeof(packet_t) - sizeof(char);
	packet_t temp;
        packet_t *packet;
	ret = this->mStream->recvData((char*)&temp,size);
	if (ret<=0)
		goto stream_err;
	if(!(this->check_buffer(&temp)))
	{
		p_debug("stream check err!\n");
		return this->err_stream_check;
	}
        packet = (packet_t*)this->buffer;
	memcpy(packet,&temp,sizeof(packet_t));
        m = this->mStream->recvData(&(packet->data[0]),packet->length - size);
	if (m<=0)
		goto stream_err;
	ret += m;
	return ret;
stream_err:
	p_debug("stream err!\n");
	return this->err_stream_state;
}

bool socket_packet::check_buffer(packet_t* p)
{
	if (p->length>max_packet_length) 
		return false;
	if (this->buffer == NULL || p->length>this->bufLength)
	{
		free(this->buffer);
		this->buffer =(char*)malloc(p->length);
		this->bufLength = p->length;
		if (this->buffer==NULL) 
			return false;
	}
	return true;
}

char* socket_packet::get_buffer()
{
	return this->buffer;
}

