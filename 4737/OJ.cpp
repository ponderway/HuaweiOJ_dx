
#include "OJ.h"
#include<iostream>
/*
Description  
         给定一个字符串，将字符串中所有和前面重复多余的字符删除，其余字符保留，输出处理后的字符串。需要保证字符出现的先后顺序。
Prototype
         int GetResult(const char *input, char *output)
Input Param 
         input     输入的字符串
Output Param 
         output    输出的字符串
Return Value
         0         成功
         -1        失败及异常
*/
int GetResult(const char *input, char *output)
{	
	if(input == NULL || output == NULL)
		return -1;
		
	const int NUM = 1000;
	int flags[NUM] = { 0 };

	while (*input != '\0')
	{
		if (flags[*input] == 0)
		{
			flags[*input] = 1;
			*output++ = *input;
		}
		++input;
	}
	*output = '\0';
	
    return 0;
	
}
