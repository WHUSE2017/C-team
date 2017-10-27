#ifndef __SOCKET__STREAM__
#define __SOCKET__STREAM__
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
bool init_socket();
class socket_stream{
public:
	enum 
	{
		disconnected,
		connected,
	};
	socket_stream(char *ip,unsigned short port);
	socket_stream(SOCKET s,sockaddr_in * lpremoteAddr = NULL,int nAddrlen=0);
	~socket_stream();
	int recvData(char *buffer, int buflen, int flag =0);
	int sendData(char *buffer, int buflen, int flag =0);
	int getState();
private:
	void init_cs();
	SOCKET sock;
	int state;
	CRITICAL_SECTION send_cs;
	CRITICAL_SECTION recv_cs;
	sockaddr_in remoteAddr;
	int nAddrlen;
};

#endif