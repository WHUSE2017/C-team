#ifndef __REQUEST_REPLY_
#define __REQUEST_REPLY_
enum
{
    TYPE_LOGIN,
    TYPE_REGISTER,
    TYPE_GETUSERINFO,
    TYPE_ADDEVENT,
    TYPE_GETMESSAGE,
    TYPE_ADDMESSAGE,
    TYPE_GETEVENT,
    TYPE_JOINEVENT,
    TYPE_GETPARTICIPANTS,
    TYPE_GETEVENTDETAILBYID,
    TYPE_UPDATEUSERINFO,
    TYPE_EXITEVENT,
    TYPE_SETEVENTSTATE,
    TYPE_GETEVENTBYCONDITIONS,
    TYPE_SETSECURITY,
    TYPE_GETSECURITY,
    TYPE_CHECKSECURITY
};
typedef struct{
	int type;
	int flag;
	int datalen;
	char *data;
}request_t;

typedef struct{
	int type;
	int flag;
	int datalen;
	char *data;
}reply_t;

#endif
