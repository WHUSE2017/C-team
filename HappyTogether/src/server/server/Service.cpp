#include "Service.h"
#include "serverthread.h"
#include "p_debug.h"


Service::Service(unsigned short port)
{
	 init_socket();
	 this->op=NULL;
	 slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     if(slisten  == INVALID_SOCKET)
     {
         p_debug("socket error !");
         goto error;
     }

	 //绑定IP和端口
     sockaddr_in sin;
     sin.sin_family = AF_INET;
     sin.sin_port = htons(port);
     sin.sin_addr.S_un.S_addr =  inet_addr("127.0.0.1");//0.0.0.0=INADDR_ANY; 
     if(bind( slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
     {
         p_debug("bind error !");
		 goto error;
     }
	 	   //开始监听
     if(listen( slisten, 1000) == SOCKET_ERROR)
     {
         p_debug("listen error !");
         return ;
     }
	 this->state = this->success;
	 return ;
error:
	 this->state= this->failed;
	 return ;
}

Service::~Service()
{

}

void Service::start_loop()
{


	 //循环接收数据
     SOCKET sClient;
     sockaddr_in remoteAddr;
     int nAddrlen = sizeof(remoteAddr);
     while (true)
     {
		 p_debug("等待连接...\n");
         sClient = accept(this->slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
         if(sClient == INVALID_SOCKET)
         {
             p_debug("accept error !");
             continue;
         }
		 p_debug("接受到一个连接：%s:%d\r\n", inet_ntoa(remoteAddr.sin_addr),remoteAddr.sin_port);
		 new_connect_handler(sClient);
     }
}

void Service::new_connect_handler(SOCKET sock)
{
	DWORD ThreadID;
	ServerThreadParam *param = (ServerThreadParam*)malloc(sizeof(ServerThreadParam));
	session_s *session= new session_s(new socket_packet(new socket_stream(sock)));
	session->setSqlOperate(this->getSqlOperate());
	param->session = session;
	CreateThread(NULL, 0, myServerThread, (LPVOID)(param), 0, &ThreadID);
}