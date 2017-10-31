#ifndef __SOCKET__PACKET__
#define __SOCKET__PACKET__
#include"socket_stream.h"
#define max_packet_length 65536
enum 
{
	PACKET_LOGIN,
	PACKET_GETXX,
	PACKET_SETXX,
};

#pragma pack (push,1)   /*指定1字节对齐*/ 
typedef struct {
	unsigned int type;
	unsigned int length;
	unsigned int flag;
	char data[1];
}packet_t;
#pragma pack (pop)      /*还原默认字节对齐*/  

class socket_packet
{
public:
	enum
	{
		err_stream_check,
		err_stream_state=-4099,
	};
	socket_packet(socket_stream *stream);
	~socket_packet();
	int send_packet(packet_t *packet,int length);
	int recv_packet();
	char *get_buffer();
private:
	bool check_buffer(packet_t *p);
	socket_stream *mStream;
	char *buffer;
	int bufLength;
};

#endif