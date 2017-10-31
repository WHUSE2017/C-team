#include "socket_stream.h"
#include "p_debug.h"
#pragma comment(lib,"ws2_32.lib")

int init_socket_flag=0;
bool init_socket()
{
	if (init_socket_flag!=0) return true;
	 WORD sockVersion = MAKEWORD(2,2);
     WSADATA wsaData;
     if(WSAStartup(sockVersion, &wsaData)!=0)
     {
         return false;
     }
	 init_socket_flag = 1;
	 return true;
}

socket_stream::socket_stream(char *ip,unsigned short port)
{
	init_socket();
	this->state = this->disconnected;
	 sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     if(sock == INVALID_SOCKET)
     {
         p_debug("invalid socket !");
         return ;
     }

     sockaddr_in serAddr;
     serAddr.sin_family = AF_INET;
     serAddr.sin_port = htons(port);
     serAddr.sin_addr.S_un.S_addr = inet_addr(ip); 
     if (connect(sock, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
     {
         p_debug("connect error !");
         closesocket(sock);
         return ;
     }
	init_cs();
	this->nAddrlen = 0;
	this->state = this->connected;
}

socket_stream::socket_stream(SOCKET s,sockaddr_in *lpremoteAddr,int nAddrlen)
{
	init_socket();
	init_cs();
	this->sock = s;
	this->state = this->connected;
	if (lpremoteAddr!=NULL)
		memcpy(&(this->remoteAddr),lpremoteAddr,sizeof(sockaddr_in));
	this->nAddrlen = nAddrlen;
	this->state = this->connected;
}


socket_stream::~socket_stream()
{
	printf("~~~~~\n");
	if (this->sock!=NULL)
		closesocket(this->sock);
	DeleteCriticalSection(&recv_cs);
	DeleteCriticalSection(&send_cs);
	if (this->nAddrlen >0)
		p_debug("SOCKET(%s:%d)断开了连接!\n",inet_ntoa(remoteAddr.sin_addr),remoteAddr.sin_port);
}

void socket_stream::init_cs()
{
	InitializeCriticalSection(&recv_cs);
	InitializeCriticalSection(&send_cs);
}


int socket_stream::recvData(char *buffer, int buflen, int flag )
{

	 EnterCriticalSection(&recv_cs); 	
	 int ret = recv(sock, buffer, buflen, flag);
	 LeaveCriticalSection(&recv_cs);
	 if (SOCKET_ERROR == ret || ret == 0)
		 this->state = this->disconnected;
	 return ret;
}

int socket_stream::sendData(char *buffer, int buflen, int flag )
{
	 EnterCriticalSection(&send_cs); 
	 int ret = send(sock, buffer, buflen, flag);
	 LeaveCriticalSection(&send_cs);
	 if (SOCKET_ERROR == ret)
		 this->state = this->disconnected;
	 return ret;
}

int socket_stream::getState()
{
	return this->state;
}