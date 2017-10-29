#include<stdio.h>
#include"socket_stream.h"
#include "Service.h"
#include"p_debug.h"
#include"utils.h"
#include "ConnectToMysql\Operate.h"
//#include "test.h"
int main()
{
	/*Operate *op=new Operate();
	EventNameStruct e;
	e.Arrival="abc";
	e.EventType="skk";
	e.PlaySite ="bbb";
	if (op->InsertIntoEventNameTable(e))
		p_debug("ok\n");
	else
		p_debug("failed\n");*/
	//sqltest();
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