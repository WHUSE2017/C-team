#include<stdio.h>
#include"socket_stream.h"
#include "Service.h"
#include "session_c.h"
#include"p_debug.h"
int main()
{

	int k;
	scanf("%d",&k);
	if (k==0)
	{	
		Service *s=new Service(8899);
		if (s->get_state()!=s->failed)
		{
			s->start_loop();
		}
	}
	else
	{
		session_c *client=new session_c(
							new socket_packet(
							new socket_stream("127.0.0.1",8899)));
		client->login("01234567","4567890");
	}

	while(1);
	return 0;
}