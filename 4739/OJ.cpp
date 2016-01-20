
#include "OJ.h"
#include <string.h>
#include <iostream>

/*
功能:计算字符串的最小周期。
原型：
    int GetMinPeriod(char *string);

输入参数：
    char * string：字符串。

返回值：
    int 字符串最小周期。

*/

int GetMinPeriod(char *inputStr)
{
	int minPeriod = 0;
	int len = strlen(inputStr);
	for (int i = 1; i < len; ++i)
	{
		char* temp = inputStr + i;
		if (len % i == 0)
		{
			while (*temp != '\0')
			{
				if (!strncmp(inputStr, temp, i))
					temp += i;	
				else
					break;
			}
			if (*temp == '\0')
				return i;
		}
		
	}
}
