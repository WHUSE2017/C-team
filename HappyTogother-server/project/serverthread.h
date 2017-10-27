#ifndef _SERVER_THREAD_
#define _SERVER_THREAD_
#include"p_debug.h"
#include "session_s.h"
#define pr_req(req) p_debug("->new request\n  type=%d, flag=%d, len=%d, data=%s\n",req->type,req->flag,req->datalen,req->data)   
typedef struct
{
	int flag;
	session_s *session;
}ServerThreadParam;

DWORD WINAPI myServerThread(LPVOID lpParam)
{
	ServerThreadParam *lp =(ServerThreadParam*)lpParam;
	session_s *s = lp->session;
	while(1)
	{
		int state = s->wait_request();
		if (state == s->disconected)
			break;
		request_t * req = s->get_request();

		p_debug("->new request\n  type=%d, flag=%d, len=%d, data=%s\n",
					req->type,req->flag,req->datalen,req->data);
	}
	return 0;
}

#endif