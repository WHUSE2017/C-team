#include<stdio.h>
#include"socket_stream.h"
#include "Service.h"
#include"p_debug.h"
#include"utils.h"
#include "ConnectToMysql\Operate.h"
bool checkProcess(char *ip,unsigned short port)
{
	 init_socket();
	 SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     if(sock == INVALID_SOCKET)
     {
         //p_debug("invalid socket !");
         return false;
     }

     sockaddr_in serAddr;
     serAddr.sin_family = AF_INET;
     serAddr.sin_port = htons(port);
     serAddr.sin_addr.S_un.S_addr = inet_addr(ip); 
     if (connect(sock, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
     {
         //p_debug("connect error !");
         closesocket(sock);
         return false;
     }
	closesocket(sock);
	return true;
}
int main()
{
	if (checkProcess("127.0.0.1",9988))
	{
		return 0;
	}

	Operate *op=new Operate();
	Service *ser=new Service(9988);
	ser->setSqlOperate(op);
	if (ser->get_state()!=ser->failed)
	{
			ser->start_loop();
	}
	p_debug("exit");
	system("pause");
	return 0;
}