#ifndef __SESSION__H__
#define __SESSION__H__
#include "socket_packet.h"
#include "session_s.h"
typedef struct{
	int type;
	int flag;
	int datalen;
	char *data;
}reply_t;

class session_c
{
public:
	enum {
		disconected,
		have_request,
	};
	session_c(socket_packet *sp);
	~session_c();
	bool login(char *username,char*pass);
	bool _register(void *p);
	int wait_reply();
	reply_t *get_reply();
	int send_request(request_t *req);

private:
	socket_packet *sp;
	bool b_login;
	reply_t reply;
	char *buffer;
	int bufferlen;
};
#endif
