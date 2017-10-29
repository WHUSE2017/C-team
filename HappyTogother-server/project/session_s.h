#ifndef _SESSION_S_H
#define _SESSION_S_H
#include "socket_packet.h"
typedef struct{
	int type;
	int flag;
	int datalen;
	char *data;
}request_t;

class session_s
{
public:
	enum {
		disconected,
		have_request,
	};
	session_s(socket_packet *sp);
	~session_s();
	bool login(char *username,char*pass);
	bool _register(void *p);
	int wait_request();
	request_t *get_request();
private:
	socket_packet *sp;
	bool b_login;
	request_t request;
};

#endif