#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
bool invalid_char(char ch)
{
	if (ch>='0' && ch<='9') return false;
	if (ch>='a' && ch<='z') return false;
	if (ch>='A' && ch<='Z') return false;
	if (ch == '@' ) return false;
	return true;
}

bool check_string(char * s)
{
	int i;
	for (i=0;i<strlen(s);i++)
		if (invalid_char(s[i]))
			return false;
	return true;
}

char*  get_key_values(char *data, char **key, char **value)
{
	const char * split = ";";
	char *p=data,*ret =NULL;
	if (p==NULL) return NULL;	
	int i,len;
	len =strlen (p);

	for (i=0;i<len;i++)
		if (p[i]==';')
			break;
	p[i]=0;
	ret = &p[i+1];
	len = strlen(p);
	
	for (i=0;i<len;i++)
		if (p[i]=='=')
			break;
	if (p[i]!='=') 
		return NULL;
	p[i]=0;
	*key = p;
	*value =&p[i+1];
	
	return ret;
}

int params_strcat(char *str,char *key, char* value,int maxlen)
{
	int len1,len2,len3;
	len1 = strlen(str);
	len2 =strlen(key);
	len3 = strlen(value);
	if (len1+len2+len3+2>=maxlen) return -1;
	strcat(str,key);
	strcat(str,"=");
	strcat(str,value);
	strcat(str,";");
	return strlen(str);
}

char str_int2cs[25];
char *Int2Cs(int number)
{
	char *str=str_int2cs;
	memset(str,0,25);
    itoa(number,str,10);
	return str;
}

int Cs2Int(char* str)
{
	return atoi(str);
}