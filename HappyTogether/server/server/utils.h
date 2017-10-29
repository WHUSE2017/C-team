#ifndef __UTILS__H__
#define __UTILS__H__
#include <stdio.h>
#include <string.h>
 

bool invalid_char(char ch);

bool check_string(char * s);

char*  get_key_values(char *data, char **key, char **value);

int params_strcat(char *str,char *key, char* value,int maxlen);

char *Int2Cs(int number);
int Cs2Int(char* str);
#endif