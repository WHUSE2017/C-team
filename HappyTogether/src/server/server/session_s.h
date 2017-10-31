#ifndef _SESSION_S_H
#define _SESSION_S_H
#include "socket_packet.h"
#include "request_reply.h"
#include "ConnectToMysql\Operate.h"
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
	bool send_reply(reply_t *reply);
	void login_success(char* name);
	bool IsLogin(){return this->b_login;}
	void setSqlOperate(Operate * o){op=o;}
	char* getusername(){return username;}
	Operate *op;
private:
	bool b_login;
	char username[128];
	socket_packet *sp;
	request_t request;
	char *reply_buffer;
	char reply_buffer_len;
	
};

#endif