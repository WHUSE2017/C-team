#ifndef __SERVICE__H__
#define __SERVICE__H__
#include "socket_packet.h"
#include "ConnectToMysql\Operate.h"
class Service
{
public:
	enum{
		failed,
		success,
	};
	Service(unsigned short port);
	~Service();
	int get_state(){return state;};
	void start_loop();
	void setSqlOperate(Operate *o){op=o;}
	Operate *getSqlOperate(){return op;};
private:
	Operate *op;
	socket_packet *sp;
	int state;
	SOCKET slisten;
	void  new_connect_handler(SOCKET);
};
#endif